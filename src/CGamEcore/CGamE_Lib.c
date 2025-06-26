#include <CGamE.h>

CGE_Bool CGE_IsAlpha(char c) {
	return c >= 'a' && c <= 'Z';
}

CGE_Bool CGE_IsNumeric(char c) {
	return c >= '0' && c <= '9';
}

int CGE_Parse(const char *str) {
	int res = 0;
	for (int i = 0; str[i] != 0; ++i) {
		if (!CGE_IsNumeric(str[i])) {
			return 0;
		}
		res *= 10;
		res += str[i];
	}
	return res;
}

float CGE_Lerp(float a, float b, float t) {
	return a + (b - a) * t;
}
