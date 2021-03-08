#include <string.h>

#include "utils.h"

size_t custom_strlen(const char* str) {
    return strlen(str);
}

int custom_pow(int base, int power) {
	if (power == 0) return 1;
	if(base == 1) return 1;
	if(base == 0) return 0;
	int p = 1;
	int temp = base;
	while(p != power) {
		if(p * 2 <= power) {
			p *= 2;
			base *= base;
		} else {
			p += 1;
			base *= temp;
		}
	}
	return base;
}
