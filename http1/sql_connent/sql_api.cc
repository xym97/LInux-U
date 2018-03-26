#include"sql_api.h"
#include<stdio.h>
using namespace std;
//
sqlApi::sqlApi(const std::string &_h,const int& _port,\
               const std::string &_u,const std::string &_p\
               ,const std::string &_db)
{
    host = _h;
    user = _u;
    passwd = _p;
    db = _db;
    port = _port;
    conn = mysql_init(NULL);
}

int sqlApi::connect()
{
    if(mysql_real_connect(conn, host.c_str(), user.c_str(),"", db.c_str(),\
                          port,NULL, 0)){
        cout<<"connect sucess"<<endl;
    }else{
        cout<<"connect error"<<endl;
        perror("mysql_real_connect");
    }
}

//name sex age id(auto increse) //hobby school
int sqlApi::insert(const std::string& _name, const std::string& _sex,\
           const std::string& _age, const std::string& _hobby, const std::string& _school )
{
    std::string sql = "insert into xym (name, sex, age, hoddy, school)\
                       values ('";
    sql += _name;
    sql += "','";
    sql += _sex;
    sql += "','";
    sql += _age;
    sql += "','";
    sql += _hobby;
    sql += "','";
    sql += _school;
    sql += "')";
   
    cout<<sql<<endl;
    int ret = mysql_query(conn,sql.c_str());
    if(ret != 0){
        cout<<"insert error"<<endl;
    }
}

int sqlApi::select()
{
    std::string sql = "select * from xym";
    if(mysql_query(conn, sql.c_str())){
        res = mysql_store_result(conn);
        if(res){
            int nums = mysql_num_rows(res);
            int col = mysql_num_fields(res);
            cout<<"nums: "<<nums<<"col: "<<col<<endl;
        
            MYSQL_FIELD *fd;
            for(; fd = mysql_fetch_field(res);  ){
                cout<<fd->name<<" ";
            }
            cout<<endl;

            int i = 0;
            int j = 0;
            for(; i < nums; i++){
                MYSQL_ROW row_res = mysql_fetch_row(res);
                j = 0;
                for(; j < col; j++){
                    cout<< row_res[j]<<" ";
                }
                cout<<endl;
            }
            cout<<endl;
        }
    }
}

sqlApi::~sqlApi(){
    mysql_close(conn);
}


