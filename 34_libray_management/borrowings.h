
#ifndef BORROWINGS_H
#define BORROWINGS_H

#include <mysql/mysql.h>

void borrow_book(MYSQL *conn);
void return_book(MYSQL *conn);
void view_borrowings(MYSQL *conn);

#endif
