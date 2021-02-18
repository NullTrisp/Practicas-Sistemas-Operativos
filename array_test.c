#include <stdio.h>

int main() {
	int arr[10], value, pos, i;
	
	for(i = 0; i < 10; ++i) {
		printf("Value to insert to array in position %d!\n", 1 + i);
		scanf("%d", &arr[i]);
	
	}

	printf("Insert position to insert value!\n");
	scanf("%d", &pos);

	for(i = 0; i < 10; ++i) {
		if(i == pos) {
			arr[i] = value;
			break;
		}
	}

	for(i = 0; i < 10; ++i) {
		printf("%d ", arr[i]);
	}


	return 0;
}
