#include<iostream>
#include<vector>
#include<string>
#include<stdlib.h>

using namespace std;

int findthK(vector<int>& arr1, int i, vector<int>& arr2, int j,int k)
{
    if(arr1.size() > arr2.size()){
        return findthK(arr2, j, arr1, i, k);
    }
    if(arr1.size() == i){
        return arr2[j + k - 1];
    }
    if(k == 1){
        return arr1[i] < arr2[j] ? arr1[i] : arr2[j];
    }    
    int pa = 0;
    if(i + k / 2 < arr1.size()) pa = i + k / 2;
    else                        pa = arr1.size();
    int pb = j + k - pa + i;
    if(arr1[pa - 1] < arr2[pb - 1]){
        return findthK(arr1, pa, arr2, j, k - pa + i );
    }else if(arr1[pa - 1] > arr2[pb - 1]){
        return findthK(arr1, i, arr2, pb, k - pb + j);
    }    
} 

int findMidNumberFromTwoSortedArray(vector<int> arr1, vector<int> arr2)
{
    int size1 = arr1.size();
    int size2 = arr2.size();
    if(size1 < 1 || size2 < 1){
        return 0;
    }
    size_t total = size1 + size2;
    if(total & 0x1){
        return findthK(arr1, 0, arr2, 0, total / 2  +1);
    }else{
        return (findthK(arr1, 0, arr2, 0, total / 2 + 1) + \
                findthK(arr1, 0, arr2, 0, total / 2)) / 2;
    }
}



int main()
{
    int a[5] = {2,4,7,9,10};
    int b[5] = {1,3,5,6,8};
    vector<int> arr1(a, a + 5);
    vector<int> arr2(b , b + 5);
    cout << findMidNumberFromTwoSortedArray(arr1, arr2)<<endl;
    return 0;
}
         
         
