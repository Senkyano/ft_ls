#include "rithylib.h"

#include <stdlib.h>

size_t	strlenSelf(char *str) {
	size_t	x = 0;

	if (!str)
		return (x);

	while (str[x])
		x++;
	return (x);
}
