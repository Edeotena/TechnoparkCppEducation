#include "simp.h"

int prime(long temp) {
	if(temp <= 1) return 0;
	int i = 2;
	while(i * i <= temp) {
		if(temp % i == 0) return 0;
		i++;
	}
	return 1;
}
