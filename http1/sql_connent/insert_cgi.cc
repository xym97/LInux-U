#include"sql_api.h"

using namespace std;

int main()
{
    //cout << "hello insert"<<endl;    
    cout<< "client version"<< mysql_get_client_info()<<endl;   
    sqlApi mydb("127.0.0.1", 3306);
    mydb.connect();
    mydb.insert("xyiming", "man", "18", "coding","sust");
    mydb.select();
    return 0;
}


