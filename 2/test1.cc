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

bool FindTwoWithSum(int* arr, int length,int k, int& num1, int& num2)
{
    bool found = false;
    if(arr == NULL || length <= 0)
        return found;
    int behind = 0;
    int ahead = length - 1;
    while(ahead > behind){
        long long cur = arr[behind] + arr[ahead];
        if(cur == k){
            num1 = arr[behind];
            num2 = arr[ahead];
            found = true;
            break;
        }else if(cur > k){
            ahead--;
        }else{
            behind++;
        }
    }
    return found;
}

void PrintQueue(int small, int big)
{
    for(int i = small; i <= big; ++i)
        cout<<i<<" ";
    cout<<endl;
}

void FindQueueSumisK(int sum)
{
    if(sum < 3)
        return;
    int small = 1;
    int big = 2;
    int mid = (1 + sum) >> 1;
    int cursum = small + big;
    while(small < mid){
        if(cursum == sum)
            PrintQueue(small, big);
        while(cursum > sum && small < mid){
            cursum -= small;
            small++;
            if(cursum == sum)
                PrintQueue(small, big);
        }
        big++;
        cursum += big;
    }
}

int compare(const void* arg1,const  void* arg2)
{
    return *(int*)arg1 - *(int*)arg2;
}

bool IsContinuous(int* arr, int length)
{
    if(arr == NULL || length < 1)
        return false;
    qsort(arr, length, sizeof(int), compare);
    int numberofZero = 0;
    int numberofGap = 0;
    for(int i = 0 ; i < length - 1 && arr[i] == 0; ++i)
        numberofZero++;
    int small = numberofZero;
    int big = small + 1;
    while(big < length){
        if(arr[small] == arr[big])
            return false;
        numberofGap += arr[big] - arr[small] - 1;
        small = big;
        big++;
    }
    return (numberofZero >= numberofGap) ? true : false;
}

void  Reverse(char* pBegin, char* pEnd)
{
    if(pBegin == NULL || pEnd == NULL)
        return;
    while(pBegin < pEnd){
        char tmp = *pBegin;
        *pBegin = *pEnd;
        *pEnd   = tmp;
        ++pBegin;
        --pEnd;
    }
}

char* Reversesentence(char* pData)
{
    if(pData == NULL)
        return NULL;
    char* pEnd = pData;
    char* pBegin = pData;
    while(*pEnd != '\0'){
        pEnd++;
    }
    pEnd--;
    Reverse(pBegin, pEnd);
    pBegin = pEnd = pData;
    while(*pBegin != '\0'){
        if(*pBegin == ' '){
            pBegin++;
            pEnd++;
        }else if(*pEnd == ' ' || *pEnd == '\0'){
            --pEnd;
            Reverse(pBegin, pEnd);
            pBegin = ++pEnd;
        }else{
            pEnd++;
        }
    }
    return pData;
}

int main()
{
    char srr[] = "I am a student";
    int brr[] = {1,2,4,7,11,15};
    int arr[] = {1,2,3,3,3,3,3,4,5,7,9};
    int crr[] = {4,0,0,6,2,1,3,9};
    cout<<GetNumberOfK(arr, sizeof(arr)/sizeof(int), 3)<<endl;
    int a = 0;
    int b = 1;
    FindTwoWithSum(brr,sizeof(brr)/sizeof(int) , 15, a, b);
    cout<< a <<" "<<b<<endl;
    FindQueueSumisK(15);
    cout<<IsContinuous(crr, sizeof(crr)/sizeof(int))<<endl;
    cout<<Reversesentence(srr)<<endl;
    return 0;
}
