
#ifndef BOOKS_H
#define BOOKS_H

#include <mysql/mysql.h>

void add_book(MYSQL *conn);
void view_books(MYSQL *conn);
void search_book(MYSQL *conn);
void update_book(MYSQL *conn);
void delete_book(MYSQL *conn);

#endif
