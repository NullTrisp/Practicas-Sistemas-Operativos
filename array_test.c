#include <stdio.h>

int main() {

	int value, pos, i, arrSize;

	printf("Insert array size: \n");
	scanf("%d", &arrSize);

	int arr[arrSize];
	
	for(i = 0; i < arrSize; ++i) {
		printf("Value to insert to array in position %d!\n", 1 + i);
		scanf("%d", &arr[i]);
	
	}

	printf("Insert position to insert value!\n");
	scanf("%d", &pos);
	printf("Insert value!\n");
	scanf("%d", &value);

	for(i = 0; i < arrSize; ++i) {
		if(i == (pos - 1)) {
			arr[i] = value;
			break;
		}
	}

	for(i = 0; i < arrSize; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;
}
