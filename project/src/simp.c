#include "simp.h"

int prime(long temp) {
	if (temp <= 1) {
		return 0;
	} else if (temp <= 3) {
		return 1;
	} else if (temp % 2 == 0 || temp % 3 == 0) {
		return 0;
	}
	for (int i = 5; i * i <= temp; i = i + 6) if (temp % i == 0) {
		return 0;
	}
	return 1;
}
