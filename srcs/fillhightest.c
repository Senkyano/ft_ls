#include "ls.h"

void	resetHightest(t_info_high *hightest) {
	hightest->max_char_sizeFile = 0;
	hightest->max_char_nameFile = 0;
	hightest->total_stblock = 0;
}