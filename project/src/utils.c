#include <string.h>

#include "utils.h"

size_t custom_strlen(const char* str) {
    return strlen(str);
}

int custom_pow(int base, int power) {
	if (power == 0) return 1;
	if (base == 1) return 1;
	if (base == 0) return 0;
	int result = base;
	for(int i = 1; i < power; i++) result *= base;
	return result;
}
