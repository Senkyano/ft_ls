# ft_ls

> Une réimplémentation en C de la commande Unix standard `ls(1)`, réalisée dans le cadre du cursus de l'école 42.

---

## 📌 Présentation

**ft_ls** est un projet système de l'école 42 visant à reproduire le comportement de la commande `ls`. Il permet de lister les fichiers et répertoires présents sur le système, d'extraire leurs métadonnées via les appels système Unix (`stat`, `lstat`, `opendir`, etc.) et de formater l'affichage selon diverses options.

Ce projet met l'accent sur :
- La manipulation approfondie du système de fichiers Unix et des inodes.
- La gestion dynamique de structures de données (listes chaînées triées à l'insertion).
- La gestion rigoureuse de la mémoire sans fuite (`valgrind`-clean).
- La gestion des spécificités terminales (largeur via `ioctl`, détection de redirection avec `isatty`, gestion des locales).

---

## 🚀 Fonctionnalités & Options

Le binaire gère les options obligatoires du sujet 42, combinables entre elles :

| Option | Nom long | Description |
| :---: | :--- | :--- |
| `-a` | *all* | Affiche tous les fichiers, y compris les fichiers cachés (commençant par un `.`). |
| `-l` | *long format* | Affiche les détails sous forme de liste : droits, liens, propriétaire, groupe, taille, date et nom. |
| `-R` | *recursive* | Liste récursivement les sous-répertoires rencontrés. |
| `-r` | *reverse* | Inverse l'ordre du tri (alphabétique ou temporel). |
| `-t` | *sort by time* | Trie les éléments selon la date de dernière modification (du plus récent au plus ancien). |

### Fonctionnalités supplémentaires
- **Support des combinaisons d'options** : `./ft_ls -latr`, `./ft_ls -l -a`, etc.
- **Détection de redirection (`isatty`)** : Formatage adapté si la sortie standard est un terminal ou un tube / fichier.
- **Détection de la taille du terminal** : Utilisation de `ioctl(..., TIOCGWINSZ)` pour adapter l'affichage.
- **Gestion des caractères spéciaux** : Entourage par des apostrophes `'...'` pour les noms contenant des espaces ou caractères spéciaux (comme le `ls` moderne).
- **Gestion fine des erreurs** : Messages conformes et codes de retour appropriés (`ENOENT`, `EACCES`, options invalides).

---

## 🏗️ Architecture du projet

```
ft_ls/
├── Makefile            # Compilation du projet et de la bibliothèque rithylib
├── include/
│   ├── color.h         # Définitions des codes couleurs ANSI
│   └── ls.h            # Structures principales (t_info_ls, t_info_inode), prototypes et macros
├── srcs/
│   ├── main.c          # Point d'entrée, détection tty / ioctl, coordination
│   ├── parsing.c       # Parsing des flags CLI et insertion triée
│   ├── exploringfile.c # Parcours des dossiers (opendir / readdir / lstat)
│   ├── printinfols.c   # Formatage de l'affichage (mode simple et format long -l)
│   └── fillhightest.c  # Calcul des dimensions / alignements des colonnes
├── rithylib/           # Librairie C personnalisée
│   ├── include/
│   │   └── rithylib.h  # Prototypes de rithylib (fprintfSelf, chaînes, listes)
│   ├── srcs/           # Implémentations utilitaires
│   └── Makefile        # Compilation de rithylib.a
├── test_ls.sh          # Suite de tests automatisée comparant ft_ls et /bin/ls
└── README.md
```

### Structure de données principale

Chaque fichier ou répertoire est représenté par une structure `t_info_inode` stockant l'ensemble de ses attributs :
```c
typedef struct s_info_inode {
    char                *nameFile;           // Nom du fichier
    char                *fullpath;           // Chemin complet
    int                 attrFile;           // Attributs / types (fichier, dossier, lien...)
    nlink_t             nblink;             // Nombre de liens physiques
    time_t              last_modification;  // Date de modification (mtime)
    uid_t               userId;             // UID du propriétaire
    gid_t               grId;               // GID du groupe
    off_t               sizeFile;           // Taille en octets
    mode_t              st_mode;            // Permissions et type d'inode
    int                 depth;              // Profondeur (pour l'exploration -R)
    struct s_info_inode *nextFile;          // Pointeur vers l'élément suivant
} t_info_inode;
```

---

## 🛠️ Compilation

Le projet se compile avec `gcc` et les flags `-Wall -Wextra -Werror` :

```bash
# Compilation du binaire ft_ls et de la bibliothèque interne rithylib
make

# Suppression des fichiers objets (.o)
make clean

# Suppression des objets et des exécutables / archives
make fclean

# Recompilation complète
make re
```

---

## 💻 Utilisation

```bash
./ft_ls [-alRrt] [fichier / dossier ...]
```

### Exemples

Lister le dossier courant :
```bash
./ft_ls
```

Affichage détaillé avec fichiers cachés :
```bash
./ft_ls -la
```

Tri par date inversé en format long :
```bash
./ft_ls -ltr /var/log
```

Parcours récursif d'une arborescence :
```bash
./ft_ls -R srcs/
```

Lister plusieurs cibles distinctes :
```bash
./ft_ls -l Makefile srcs/
```

---

## 🧪 Tests

Un script de test `test_ls.sh` est inclus à la racine du projet. Il permet de confronter la sortie de `ft_ls` avec celle du `ls` système sur un environnement de test (`.test_sandbox`) contenant divers cas limites (fichiers avec espaces, permissions `000`, liens symboliques, timestamps personnalisés, etc.).

Pour lancer la suite de tests :
```bash
chmod +x test_ls.sh
./test_ls.sh
```
