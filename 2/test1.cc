#include<iostream>
#include<string>
#include<stdlib.h>

using namespace std;

int GetFirstK(int* arr, int length, int k, int start, int end)
{
    if(start > end)
        return -1;
    //int midindex = (start & end) + ((start ^ end) >> 1);
    int midindex = (start + end) / 2;
    int middata = arr[midindex];
    if(middata == k){
        if(midindex > 0 && arr[midindex - 1] != k || midindex == 0)
            return midindex;
        else
            end  = midindex - 1;
    }else if(middata > k){
        end = midindex - 1;
    }else{
        start = midindex + 1;
    }
    return GetFirstK(arr, length, k ,start, end);
}


int GetLastK(int* arr, int length, int k, int start, int end)
{
    if(start > end)
        return -1;
    //int midindex = (start & end) + ((start ^ end) >> 1);
    int midindex = (start + end) /2;
    int middata = arr[midindex];
    if(middata == k){
        if(midindex < length - 1 && arr[midindex + 1] != k || midindex == length - 1)
            return midindex;
        else
            start = midindex + 1;
    }else if(middata > k){
        end = midindex - 1;
    }else{
        start = midindex + 1;
    }
    return GetLastK(arr, length, k ,start, end);
}

int GetNumberOfK(int* arr, int length, int k)
{
    int number = 0;
    if(arr != NULL && length >= 1){
        int FirstK = GetFirstK(arr, length, k , 0 , length - 1);
        int LastK = GetLastK(arr, length, k , 0, length - 1);
    
    if(FirstK >= 0 && LastK >= 0)
        number = LastK - FirstK + 1;
    }
    return number;
}


int main()
{
    int arr[] = {1,2,3,3,3,3,3,4,5,7,9};
    cout<<GetNumberOfK(arr, sizeof(arr)/sizeof(int), 3)<<endl;
    return 0;
}
