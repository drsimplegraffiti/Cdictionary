
#ifndef DB_H
#define DB_H

#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

#define DB_HOST     "localhost"
#define DB_USER     "root"
#define DB_PASS     "Bassguitar1"
#define DB_NAME     "library"
#define DB_PORT     3306

#ifdef _WIN32
    #define CLEAR system("cls")
#else
    #define CLEAR system("clear")
#endif

MYSQL *connect_db();
void close_db(MYSQL *conn);

#endif
