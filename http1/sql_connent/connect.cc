#include"sql_api.h"
#include <stdio.h>

int main()
{
    MYSQL *conn;
    const char *server = "localhost";
   const char *user = "root";
   const char *password = "";//“******”为你设置的密码
   const char *database = "http";
    conn = mysql_init(NULL);
    if(!mysql_real_connect(conn, server, user, NULL, database, 3306, NULL, 0))
        printf("连接失败：%s", mysql_error(conn));
    else
        printf("连接成功！");
    getchar();
    return 0;
}
