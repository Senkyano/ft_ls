#!/bin/bash

# ==============================================================================
# SCRIPT DE TEST POUR PROJET LS
# ==============================================================================

# Nom de ton exécutable (Change-le si ton binaire s'appelle autrement)
MY_LS="./ft_ls"

# Couleurs pour l'affichage
GREEN='\031[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Compteurs
TESTS_RUN=0
TESTS_PASSED=0

# Vérification de l'existence de ton exécutable
if [ ! -f "$MY_LS" ]; then
    echo -e "${RED}Erreur : Exécutable '$MY_LS' introuvable !${NC}"
    echo "Assure-toi d'avoir compilé ton projet (ex: make)."
    exit 1
fi

# Préparation d'un dossier de test temporaire avec des cas tordus
TEST_DIR="./.test_sandbox"
rm -rf "$TEST_DIR"
mkdir -p "$TEST_DIR"
mkdir -p "$TEST_DIR/dossier1" "$TEST_DIR/dossier2" "$TEST_DIR/.dossier_cache"

# Création de fichiers variés (dates différentes, droits, espaces, etc.)
touch "$TEST_DIR/normal.txt"
touch "$TEST_DIR/.cache.txt"
touch "$TEST_DIR/fichier avec espaces.txt"
touch "$TEST_DIR/script$.sh"
chmod 777 "$TEST_DIR/script$.sh"
chmod 000 "$TEST_DIR/dossier2" # Test dossier sans droits

# Création d'un lien symbolique
ln -s "$TEST_DIR/normal.txt" "$TEST_DIR/lien_sym" 2>/dev/null

# Décalage de dates pour tester le -t
touch -t 202401010000 "$TEST_DIR/vieux_fichier.txt"
touch -t 202601010000 "$TEST_DIR/recent_fichier.txt"

# ------------------------------------------------------------------------------
# FONCTION DE TEST
# ------------------------------------------------------------------------------
run_test() {
    local label="$1"
    local args="$2"
    
    TESTS_RUN=$((TESTS_RUN + 1))
    
    # Fichiers temporaires pour capturer la sortie
    local out_sys="/tmp/ls_sys.out"
    local out_my="/tmp/ls_my.out"

    # Exécution des deux commandes (LC_ALL=C pour forcer le même tri de langue)
    LC_ALL=C ls $args > "$out_sys" 2>&1
    LC_ALL=C $MY_LS $args > "$out_my" 2>&1

    # Comparaison avec diff
    if diff -u "$out_sys" "$out_my" > /dev/null 2>&1; then
        echo -e "[ ${GREEN}OK${NC} ] Test $TESTS_RUN : $label ${BLUE}(ls $args)${NC}"
        TESTS_PASSED=$((TESTS_PASSED + 1))
    else
        echo -e "[ ${RED}KO${NC} ] Test $TESTS_RUN : $label ${BLUE}(ls $args)${NC}"
        echo -e "${YELLOW}--- Différence détectée (-Vrai ls  +Ton ls) ---${NC}"
        diff -u "$out_sys" "$out_my" | head -n 15
        echo "-----------------------------------------------"
    fi
}

# ------------------------------------------------------------------------------
# LISTE DES TESTS À EFFECTUER
# ------------------------------------------------------------------------------
echo -e "${BLUE}=====================================================${NC}"
echo -e "${BLUE}            DÉBUT DE LA BATTERIE DE TESTS            ${NC}"
echo -e "${BLUE}=====================================================${NC}\n"

# 1. Tests simples (Dossier courant)
run_test "Affichage basique" ""
run_test "Affichage tous les fichiers (-a)" "-a"
run_test "Format long (-l)" "-l"
run_test "Tri par temps (-t)" "-t"
run_test "Tri inversé (-r)" "-r"

# 2. Combinatoires d'options
run_test "Format long + cachés (-la)" "-la"
run_test "Format long + temps (-lt)" "-lt"
run_test "Format long + temps + reverse (-ltr)" "-ltr"
run_test "Combinatoire complète (-latr)" "-latr"

# 3. Tests sur le dossier de test spécial (Espaces, Liens, Droits)
run_test "Dossier avec espaces/liens/droits" "$TEST_DIR"
run_test "Format long sur dossier spécial (-la)" "-la $TEST_DIR"
run_test "Tri par temps sur dossier spécial (-lt)" "-lt $TEST_DIR"

# 4. Tests d'arguments ciblés
run_test "Passage d'un fichier en argument" "Makefile"
run_test "Passage de plusieurs arguments" "Makefile src/ $TEST_DIR/normal.txt"

# ------------------------------------------------------------------------------
# NETTOYAGE ET BILAN
# ------------------------------------------------------------------------------
rm -rf "$TEST_DIR"
rm -f /tmp/ls_sys.out /tmp/ls_my.out

echo -e "\n${BLUE}=====================================================${NC}"
if [ $TESTS_PASSED -eq $TESTS_RUN ]; then
    echo -e "${GREEN} RÉSULTAT : $TESTS_PASSED / $TESTS_RUN tests réussis ! Tout est parfait ! 🎉${NC}"
else
    echo -e "${RED} RÉSULTAT : $TESTS_PASSED / $TESTS_RUN tests réussis.${NC}"
fi
echo -e "${BLUE}=====================================================${NC}"