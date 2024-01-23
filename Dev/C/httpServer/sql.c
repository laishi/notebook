#include <mysql/mysql.h>
#include <stdio.h>

int main() {
    // 初始化 MySQL 连接
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    // 连接到 MySQL 数据库
    if (mysql_real_connect(conn, "localhost", "username", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return 1;
    }

    // 执行 SQL 查询
    if (mysql_query(conn, "SELECT * FROM your_table")) {
        fprintf(stderr, "mysql_query() failed\n");
        mysql_close(conn);
        return 1;
    }

    // 获取查询结果
    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "mysql_store_result() failed\n");
        mysql_close(conn);
        return 1;
    }

    // 输出查询结果
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        printf("%s\n", row[0]);  // 假设查询的是一列数据
    }

    // 释放结果集
    mysql_free_result(result);

    // 关闭 MySQL 连接
    mysql_close(conn);

    return 0;
}

