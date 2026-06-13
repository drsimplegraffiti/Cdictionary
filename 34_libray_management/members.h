
#ifndef MEMBERS_H
#define MEMBERS_H

#include <mysql/mysql.h>

void add_member(MYSQL *conn);
void view_members(MYSQL *conn);
void delete_member(MYSQL *conn);

#endif
