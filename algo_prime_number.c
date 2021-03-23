#include <stdio.h>

int main() {
	int value, aux, exit = 1, prime = 1, i;
	while(exit) {
		printf("Input a value:\n");
		scanf("%d", &value);
		if(value == -1) {
			printf("Bye :)\n");
			exit = 0;
		} else if (value == 1) {
			printf("Value is 1!\n");
		} else {
			for(i = 2; i < value; ++i) {
				if(value % i == 0) {
					printf("Value is not prime!\n");
					prime = 0; 
					break;
				}
			}
			if(prime) {
				printf("Value is prime!\n");
			}
		}
		prime = 1;

	}
}
