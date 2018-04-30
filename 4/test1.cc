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


//void CalSum(vector<int> &nums, int result)    
//{  
//    int len = nums.size();  
//    int bit = 1 << len;  
//    for (int i = 1; i < bit; i++)//    
//    {    
//        int sum = 0;    
//        vector<int> tmp;  
//        for (int j = 0; j < len; j++)    
//        {    
//            if ((i & 1 << j) != 0)//用i与2^j进行位与运算，若结果不为0,则表示第j位不为0,从数组中取出第j个数    
//            {    
//                sum += nums[j];    
//                tmp.push_back(nums[j]);    
//            }    
//        }    
//        if (sum == result)  
//        {  
//            for (vector<int>::iterator iter = tmp.begin(); iter != tmp.end(); iter++)  
//            {  
//                cout << *iter << " ";  
//            }  
//            cout << endl;  
//        }  
//    }    
//} 

int* searchrand(vector<int>& arr, int target)
{
    int* res = new int[2];
        res[0] = res[1] = 0;
    if(arr.size() == 0)
        return res;
    int end = arr.size() - 1;
    int start = 0;
    while(start < end){
        int mid = (start + end) / 2;
        if(arr[mid] < target){
            start = mid + 1;
        }else {
            end   = mid;
        }
    }
    if(target != arr[start])
        return res;    
    res[0] = start;
    end = arr.size() - 1;
    while(start < end){
        int mid = (start + end) / 2 + 1;
        if(arr[mid] > target){
            end = mid - 1;
        }else{
            start = mid;
        }
    }
    res[1] = end;
    return res;
}

int FindMaxSumOfSubstr(int* arr, size_t len){
    if(arr == NULL || len <= 0){
        printf("array error\n");
        return -1;
    }
    int sum = 0;
    int Save = 0x8000000;
    for(size_t i = 0; i < len ; i++){
        if(sum <= 0){
            sum = arr[i];
        }else{
            sum += arr[i];
        }
        if(sum > Save){
            Save = sum;
        }
    }
    return Save;
}

char FindfirstNotRepeatchar(char* arr, size_t len)
{
    if(arr == NULL)
        return '\0';
    vector<int> hash;
    hash.resize(256, 0);
    for(size_t i = 0; i < len; ++i){
        hash[arr[i]]++;
    }
    for(size_t i = 0; i < len; ++i){
        if( hash[arr[i]] == 1 ){
            return arr[i];
        }
    }
    return '\0'
}

int GetMaxSubArray(const vector<int>& num){
    if(num.size() == 0){
        return 0;
    }else if(num.size() == 1){
        return num[0];
    }else if(num.size() == 2){
        return num[0] > num[1] ? num[0] : num[1];
    }num
    int prev = num[0];
    int next = num[0] > num[1] ? num[0] : num[1];
    for(int i = 2; i < num.size(); ++i){
        int sum1 = prev + num[i];
        int sum2 = next > sum1 ? next : sum1;
        prev = next;
        next = sum2;
    }
    return prev > next ? prev : next;
}

int main()
{
    int a[5] = {2,4,7,9,10};
    int b[5] = {1,3,5,6,8};
    int c[10] = {1,2,3,4,5,6,7,8,9,10};
    int d[] = {1,2,2,3,3,3,3,4,5,7,7,8,9};
    vector<int> v2(d, d  +13);
    vector<int> v(c, c+10);
    vector<int> arr1(a, a + 5);
    vector<int> arr2(b , b + 5);
    int* arr = searchrand(v2, 3);
    for(int i = 0; i < 2; ++i)
        cout<< arr[i] << " ";
    cout<<endl;
    //CalSum(v , 14);
    cout << findMidNumberFromTwoSortedArray(arr1, arr2)<<endl;
    return 0;
}
         
         
