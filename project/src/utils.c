#include <string.h>

#include "utils.h"

size_t custom_strlen(const char* str) {
    return strlen(str);
}

// TODO(my_username): Stuff.

int custom_pow(int base, int power) {
	int temp = base;
	if(base == 1 || power == 0) return 1;
	if (base == 0) return 0;
	for(int i = 0; i < power - 1; i++) temp *= base;
    return temp;
}
