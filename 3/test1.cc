#include<iostream>
#include<vector>
#include<cstring>
#include<assert.h>
#include<stdlib.h>

using namespace std;
//斐波那契数列的迭代求法
long long Fibonacin(unsigned long n)
{
    long result[2] = {0 , 1};
    if(n < 2)
        return result[n];

    long long first = 0;
    long long second = 1;
    long long ret = 0;
    for(long i = 2; i <= n; ++i){
        ret = first + second;
        first = second;
        second = ret;
    }
    return ret;
}
//一个数中的二进制数“1”有多少个
int NumOf1(int n)
{
    int count = 0;
    while(n){
        count++;
        n = (n - 1) & n;
    }
    return count;
}

int NumOfChangeBit(int a, int b)
{
    int n = a ^ b;
    int count = 0;
    while(n){
        count++;
        n = (n - 1) & n;
    }
    return count;
}

//if(!(n & (n - 1))

//实现一个数的乘方
bool g_Invalid = false;

bool equal(double num1 , double num2)
{
    if(num1 - num2 < 0.000001 && num1 - num2 > -0.000001)
        return true;
    return false;
}

double Poww(double base,int ex)
{
    if(ex == 0)//指数是0 计算值是1
        return 1.0;
    if(ex == 1)//指数是1 值是本身
        return base;
    double ret = Poww(base, ex >> 1);
    ret *= ret;
    if(ex & 0x1 == 1)// example:7 / 2 = 3; 2^3 * 2^3 * 2
        ret *= base;
    return ret;
}

double Pow(double base, int exponent)
{
    if(equal(base, 0.0 && exponent < 0)){
        g_Invalid = true;//判断0不可以有负数次方
        return 0.0;
    }
    unsigned int ex = (unsigned int)(exponent);
    if(exponent < 0){//把指数先统一成正数
         ex = (unsigned int)(-exponent);
    }
    double ret = Poww(base, ex);
    if(exponent < 0){//指数如果原本是正数则
        ret = 1.0/ret;
    }
    return ret;
}
//从一开始打印、打印到一个大数
bool Increment(char* number)
{
    bool IsOverDigits = false;
    int TakeOver = 0;//表示进位
    int len = strlen(number);
    for(int i = len - 1; i >= 0; --i){
        int nSum = number[i] - '0' + TakeOver;
        if(i == len - 1){
            ++nSum;//按照加法规则，在最低位加一
        }
        if(nSum >= 10){//这一位达到10，这时需要进位
            if(i == 0){
                IsOverDigits = true;//这里表示已经到了最大的一位了
            }else{
                nSum -= 10;
                TakeOver = 1;
                number[i] = '0' + nSum;//字符串的这一位只保存进位后这一位留下的数字。
            }
        }else{
            number[i] = '0' + nSum;//如果不存在进位的话，这一位写加上之前进一了的数字
            break;
        }
    }
    return IsOverDigits;
}

void PrintNumber(char* number)
{//该函数用来保证不打印用于保存数的子符串初始化时之前多余的0
    bool IsFrontZero = true;
    int len = strlen(number);
    for(int i = 0; i < len; ++i){
        if(IsFrontZero && number[i] != '0'){
            IsFrontZero = false;
        }
        if(!IsFrontZero){
            printf("%c", number[i]);
        }
    }
    cout<<" ";
}

void PrintGreatDigits(int n)
{
    if(n < 0)
        return;
    char* number = new char[n+1];
    memset(number, '0', n);
    number[n] = '\0';
    while(!Increment(number)){
        PrintNumber(number);
    }
    delete[] number;
    cout<<endl;
}

void PrintRecursively(char* number, int len, int index)
{
    if(index == len - 1){
        PrintNumber(number);
        return;
    }
    for(int i = 0; i < 10; ++i){
        number[index + 1] = i + '0';
        PrintRecursively(number, len, index + 1);
    }
}

void PrintGreatDigits2(int n)
{
    if(n <= 0)
        return;
    char* number = new char[n + 1];
    number[n] = '\0';
    
    for(int i = 0; i < 10; ++i){
        number[0] = i + '0';
        PrintRecursively(number, n, 0);
    }  
    delete[] number;
}

bool IsEven(int n)
{
    return (n & 0x1) == 0;
}

void Reorder(int* arr, int len, bool (*func)(int))
{
    assert(arr);
    int begin = 0;
    int end = len - 1;
    while(begin < end){
        while(begin < end && !(*func)(arr[begin]))
            ++begin;
        while(begin < end && (*func)(arr[end]))
            --end;
        if(begin < end){
            swap(arr[begin], arr[end]);
        }
    }
    for(int i = 0; i < len; ++i){
        cout<<arr[i]<< " ";
    }
    cout << endl;
}

void _Permutatain(char* pStr, char* pBegin)
{
    if(*pBegin == '\0'){
        printf("%s\n", pStr);
        return;
    }else{
        for(char* pCh = pBegin; *pCh != '\0'; ++pCh){
            char tmp = *pCh;
            *pCh = *pBegin;
            *pBegin = tmp;
            _Permutatain(pStr, pBegin + 1);
            tmp = *pCh;
            *pCh = * pBegin;
            *pBegin = tmp;
        }
    }
}

void Permutatain(char* pStr)
{
    if(pStr == NULL)
        return;
    _Permutatain(pStr, pStr);
}

bool g_InputInvalid = false;

//寻找数组中出现次数超过一半的数字

bool CheckInputInvalid(int* arr, int len)
{
    if(arr == NULL || len == 0)
        g_InputInvalid = true;
    return g_InputInvalid;
}

bool CheckMoreThenHalf(int* arr, int len, int ret)
{
    int count = 0;
    for(int i =0 ; i < len; ++i){
        if(arr[i] == ret)
            ++count;
    }
    if(count * 2 <= len){
        g_InputInvalid = true;
        return false;
    }
    return true;
}

int FindMoreThenHalf(int* arr, int len)
{
    if(CheckInputInvalid(arr, len))
        return 0;
    int count = 1;
    int num = arr[0];
    for(int i = 0; i < len - 1; ++i){
        if(count == 0){//用num保存当前得数每再遇到一次数量加一  
            num = arr[i];//没有遇到数量减一  减到0的时候num保存下一个数
            count = 1;
        } 
        if(arr[i] == num)
            count++;
        else
            count--;
    }
    if(CheckMoreThenHalf(arr, len, num))
        return num;
    return 0;
}

bool g_InvalidInput2 = false;

int FindMaxSumOfSubArray(int* arr, int len)
{
    if(arr == NULL || len <= 0){
        g_InvalidInput2 = true;
        return 0;
    }
    int Sum = 0;
    int Save = 0x80000000;//这里表示最小的int
    
    for(int i = 0; i < len; ++i){
        if(Sum <= 0){//这里的思路时保存一个当前的最大值Save 
            Sum = arr[i];//在用一个数Sum表示正在统计的字串大小如果大于Save则Save保存Sum
            //否则如果加上一个负数小于零了 则Sum从下一个数开始计算
        }else
            Sum += arr[i];
        if(Save < Sum){
            Save = Sum;
        }
    }
    return Save;
}

void Test1()
{
    int arr[] = {1,2,3,4,5,6,7,8,9,10};
    char crr[] = "abc";
    int brr[] = {3,2,3,1,4,7,5,3,3,3,6,3,3,3,3,9,0,3,3,3,3,3,3,8};
    int drr[] = {1,-2,3,10,-4,7,3,-5};
    cout<<FindMaxSumOfSubArray(drr, sizeof(drr)/sizeof(int))<<endl;
    cout<<FindMoreThenHalf(brr, sizeof(brr)/sizeof(int))<<endl;
    Permutatain(crr);
    Reorder(arr, sizeof(arr)/sizeof(int), IsEven);
    cout <<Fibonacin(6)<<endl;
    cout<< NumOf1(5)<<endl;
    cout << NumOfChangeBit(10, 13)<<endl;
    cout << Pow(3.2 , 0)<< " "<<g_Invalid<<endl;
    //PrintGreatDigits2(4);
}

int PowerWith10(int n)
{
    int ret = 1;
    for(int i = 0; i < n; ++i){
        ret *= 10;
    }
    return ret;
}

int Number(char* str)
{
    if( !str || *str == '\0' || *str > '9' || *str < 0)
        return 0;
    int frist = *str - '0';
    unsigned int len = static_cast<unsigned int>(strlen(str));
    if(len == 1 && frist == 0)
        return 0;
    if(len == 1 && frist > 0)
        return 1;
    int numoffristdigit = 0;
    int numofalldigits = 0;
    if(frist == 1)
        numoffristdigit = atoi(str + 1) + 1;
    else if(frist > 1)
        numoffristdigit = PowerWith10(len - 1);

    numofalldigits = frist * (len - 1)* PowerWith10(len - 2);
    int numofRecursive = Number(str + 1);

    return numofRecursive + numoffristdigit + numofalldigits;
}

int NumOf1Between1ToN(int n)
{
    if(n <= 0)
        return 0;
    char str[50];
    sprintf(str, "%d", n);
    return Number(str);
}

char FindFristOccurNum(char* arr, size_t len)
{
    vector<int> hash;
    hash.resize(256, 0);
    for(int i = 0 ; i < len; ++i){
        hash[arr[i]]++;
    }
    for(int i = 0; i < len; ++i){
        if(hash[arr[i]] == 1){
            return arr[i];
        }
    }
    return '\0';
}
//计算数组中的逆序对  采用归并排序的思想
//每一层的归并计算当前层的逆序对。
int _InversePair(int* arr, int* tmp, int begin, int end)
{
    if(begin == end)
    {
        tmp[begin] = arr[begin];
        return 0;
    } 
    int length = (end - begin) / 2;
    //int mid = (begin & end) + ((begin ^ end) >> 1);
    //int mid = (begin + end)/2;
    int leftcount = _InversePair(arr, tmp, begin, /*mid*/ begin + length);
    int rightcount = _InversePair(arr, tmp, /*mid*/begin + length + 1, end);

    //int i = mid;
    int i = begin + length;
    int j = end;
    int indexTmp = end;
    int count = 0;
    while(i >= begin && j >= /*mid*/begin + length + 1){
        if(arr[i] > arr[j]){
            tmp[indexTmp--] = arr[i--];
            //count += j - mid;
            count += j - begin - length;
        }else{
            tmp[indexTmp--] = arr[j--];
        }
    }
    for(; i >= begin;--i){
        tmp[indexTmp--] = arr[i];
    }
    for(; j >= /*mid*/ begin + length + 1; --j){
        tmp[indexTmp--] = arr[j];
    }
    return leftcount + rightcount + count;
}

int InversePair(int* arr, size_t len)
{
    if(arr== NULL || len <= 0)
        return 0;
    
    int* tmp = new int[len];
    memset(tmp, 0 , sizeof(int)*len);
    //for(int i = 0; i < len ; ++i)
    //    tmp[i] = arr[i];
    int count = _InversePair(arr, tmp, 0, len - 1);
    delete[] tmp;
    return count;
}

////////////////////////////

int FindBitIndex(int num)
{
    int index = 0;
    while((num & 1) == 0 && (index < 8 * sizeof(int))){
        num = num >> 1;
        ++index;
    }
    return index;
}

bool IsBit1(int index, int num)
{
    return (num >> index) & 1;
}

void FindTwoNumAppearOnce(int* arr, size_t len, int& num1, int& num2)
{
    if(arr == NULL || len < 2)
        return;
    int twoWith = 0;
    for(int i = 0; i < len ;++i)
        twoWith ^= arr[i];
    int bitIndex = FindBitIndex(twoWith);
    num1 = num2 = 0;
    for(int i = 0 ; i < len ; ++i){
        if(IsBit1(bitIndex,arr[i])){
            num1 ^= arr[i];
        }else{
            num2 ^= arr[i];
        }
    }
}
////////////////////////////

void Test2()
{
    int a = 50;
    int arr[] = {7,5,6,4};
    int brr[] = {2,4,3,6,3,2,5,5};
    int b = 0;
    int c = 0;
    FindTwoNumAppearOnce(brr, sizeof(brr)/sizeof(brr[0]), b, c);
    cout<< b << " "<< c << endl;
    cout<<InversePair(arr, 4)<<endl;
    char str[] = "abaccdhbtiftf";
    cout<<FindFristOccurNum(str, strlen(str))<<endl;
    cout<<NumOf1Between1ToN(a)<<endl;
   // cout << numberOf1Between1AndN_Recursive(12) << endl;
}

int main()
{
    Test2();
    //Test1();
    return 0;
}

