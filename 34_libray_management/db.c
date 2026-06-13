
#include "db.h"

MYSQL *connect_db() {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init failed\n");
        return NULL;
    }

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, NULL, 0)) {
        fprintf(stderr, "connection error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    printf("connected to database\n");
    return conn;
}

void close_db(MYSQL *conn) {
    mysql_close(conn);
}
