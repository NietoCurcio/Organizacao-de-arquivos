#include <stdio.h>

int partition(int begin, int end, int* arr) {

  int pivot = arr[begin];

  int i = begin;
  int j = end + 1;

  while (i < j) {
    do
    {
      i++;
    } while (arr[i] < pivot);

    do
    {
      j--;
    } while (arr[j] > pivot);
    
    if (i < j) {

      int aux = arr[i];
      arr[i] = arr[j];
      arr[j] = aux;
    }
  }

  int aux = arr[begin];
  arr[begin] = arr[j];
  arr[j] = aux;
  return j;
}

void quickSort(int begin, int end, int* arr) {
  if (begin < end) {
    int j = partition(begin, end, arr);
    quickSort(begin, j - 1, arr);
    quickSort(j + 1, end, arr);
  }
}

void traverse(int* arr, int length) {
  for(int i = 0; i < length; i++) 
    printf("%d ", arr[i]);
  printf("\n");
}

int main(int argc, char* argv[]) {
  int arr[] = {6, 3, 5, 7, 10, 9, 22, 8, 15};

  int begin = 0;
  int length = sizeof(arr)/sizeof(*arr);
  int end = length - 1;
  
  traverse(arr, length);
  quickSort(begin, end, arr);
  traverse(arr, length);

  return 0;
}