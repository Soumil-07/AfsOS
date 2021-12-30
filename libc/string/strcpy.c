#include <string.h>

char * strcpy(char * restrict dest, const char * restrict src) {
	char * out = dest;
	for (; (*dest=*src); src++, dest++);
	return out;
}
