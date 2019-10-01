#include<stdio.h>
#define LEN(x) (sizeof(x)/sizeof(typeof(x[0])))
#define quickSort(x,y) (quickSortEx(x,0,y-1))

void printArray(int [], int);
void swap(int*, int*);
int partition(int [], int, int);
void quickSortEx(int [], int, int);
int binarySearch(int [], int, int);

int main(void){
	int a[] = {0,1,2,3,4,4,5,5,5,7,8};
	quickSort(a, LEN(a));
	printArray(a, LEN(a));
	printf("%d\n", binarySearch(a, LEN(a), 5));
	return 0;
}

void swap(int *x, int *y){
	int temp = *x;
	*x = *y;
	*y = temp;
}

int partition(int arr[], int front, int rear){
	int pivot = arr[rear];
	int idx = front;
	for (int i = front;i < rear;++i)
		if (arr[i] < pivot)
			swap(&arr[i], &arr[idx++]);
	swap(&arr[idx], &arr[rear]);
	return idx;
}

void quickSortEx(int arr[], int front, int rear){
	int idx;
	if (front < rear){
		idx = partition(arr, front, rear);
		quickSortEx(arr, front, idx - 1);
		quickSortEx(arr, idx + 1, rear);
	}
}

void printArray(int arr[], int size){
	for (int i = 0;i < size;++i)
		printf("%d\n", arr[i]);
}

int binarySearch(int arr[], int size, int find){
	int mid, front = 0, rear = size - 1;
	while(front < rear){
		mid = (front + rear)/2;
		if (arr[mid] < find)
			front = mid + 1;
		else
			rear = mid;
	}
	if (arr[rear] == find)
		return rear;
	else
		return - 1;
}
