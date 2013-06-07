#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#define LINELEN 25000

int _mergeSort(int arr[], int temp[], int left, int right);
int mergeSort(int arr[], int array_size);
int merge(int arr[], int temp[], int left, int mid, int right);

int mergeSort(int arr[], int array_size)
{
    int *temp = (int *)malloc(sizeof(int)*array_size);
    return _mergeSort(arr, temp, 0, array_size - 1);
}

  
int _mergeSort(int arr[], int temp[], int left, int right)
{
  int mid, inv_count = 0;
  if (right > left)
  {
    mid = (right + left)/2;
    inv_count  = _mergeSort(arr, temp, left, mid);
    inv_count += _mergeSort(arr, temp, mid+1, right);
  
    /*Merge the two parts*/
    inv_count += merge(arr, temp, left, mid+1, right);
  }
  return inv_count;
}
  
int merge(int arr[], int temp[], int left, int mid, int right)
{
  int i, j, k;
  int inv_count = 0;
  
  i = left; /* i is index for left subarray*/
  j = mid;  /* i is index for right subarray*/
  k = left; /* i is index for resultant merged subarray*/
  while ((i <= mid - 1) && (j <= right))
  {
    if (arr[i] <= arr[j])
    {
      temp[k++] = arr[i++];
    }
    else
    {
      temp[k++] = arr[j++];
  
      inv_count = inv_count + (mid - i);
    }
  }

  while (i <= mid - 1)
    temp[k++] = arr[i++];
  
  while (j <= right)
    temp[k++] = arr[j++];
  
  /*Copy back the merged elements to original array*/
  for (i=left; i <= right; i++)
    arr[i] = temp[i];
  
  return inv_count;
}

int getInvCount(std::vector<int> arr) {
  int inv_count = 0;
  int i, j;

  int n = arr.size();
  for(i = 0; i < n - 1; i++){
    for(j = i+1; j < n; j++){
      if(arr[i] > arr[j]){
        inv_count++;
      }
    }
  }
  return inv_count;
}

int bisection(std::vector<int> arr) {
  int inv_count = 0;
  int i, j;

  int n = arr.size();
  for(i = 0; i < n - 1; i++){
    for(j = i+1; j < n; j++){
      if(arr[i] > arr[j]){
        inv_count++;
      }
    }
  }
  return inv_count;
}
int main(int argc, char* argv[]) {

  int function_select = argc>1 ? atoi(argv[1]) : 1;

  int val;
  char *linebuff = (char*)malloc(LINELEN);
  std::vector<int> numarr;
  if (!linebuff) exit(-1);
  while (fgets(linebuff, LINELEN, stdin) != NULL) {
      numarr.clear();
      char *p = linebuff;
      char *n = p;
      while ((p = strchr(p, ',')) != NULL) {
         *p = '\0';
         val = atoi(n);
         numarr.push_back(val);
         p++;
         n = p;
      }
      val = atoi(n);
      numarr.push_back(val);
      int myanswer;
      switch (function_select) {
         case 1 : myanswer = getInvCount(numarr); break;
         case 2 : myanswer = bisection(numarr); break;
         case 3 : myanswer = mergeSort(numarr.data(), numarr.size()); break;
         default : printf("Invalid function selection\n"); break;
      }
      printf("my answer == %6d \n", myanswer);   
  }

  return 0;
}
