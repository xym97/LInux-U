#include<stdio.h>
#include<string.h>
#include<vector>


using namespace std;

char* Deletestring(char* src, char* dst)
{
    vector<bool> hash;
    hash.resize(256, 0);
    char* pdst = dst;
    while(*pdst != '\0'){
        hash[*pdst] = 1;
        pdst++;
    }
    char* cur = src;
    char* pnew = src;
    
    while(*cur != '\0'){
        if(hash[*cur] == 1){
            cur++;
        }else{
            *pnew = *cur;
            pnew++;
            cur++;
        }
    }
    *pnew = '\0';
    return src;
}

int main()
{
    char src[] =  "Thay are my child";
    char dst[] = "amh";
    printf("%s\n",Deletestring(src, dst));
    return 0;
}


