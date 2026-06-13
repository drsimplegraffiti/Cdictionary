
#include "members.h"
#include <stdio.h>
#include <string.h>

void add_member(MYSQL *conn) {
  char name[255], email[255];

  printf("name: ");
  fgets(name, sizeof(name), stdin);
  name[strcspn(name, "\n")] = 0;

  printf("email: ");
  fgets(email, sizeof(email), stdin);
  // strcspn — find index of first matching character in a string
  // strcspn returns index of \n
  email[strcspn(email, "\n")] = 0;

  char query[1024];
  // snprintf — write formatted string into a buffer with size limit
  snprintf(query, sizeof(query),
           "INSERT INTO members (name, email) VALUES ('%s', '%s')", name,
           email);

  if (mysql_query(conn, query)) {
    // fprintf — write formatted string to a FILE stream
    fprintf(stderr, "add member error: %s\n", mysql_error(conn));
    return;
  }
  printf("member added successfully\n");
}

void view_members(MYSQL *conn) {
  if (mysql_query(conn, "SELECT id, name, email FROM members")) {
    fprintf(stderr, "view members error: %s\n", mysql_error(conn));
    return;
  }

  MYSQL_RES *result = mysql_store_result(conn);
  MYSQL_ROW row;

  printf("\n%-5s %-30s %-30s\n", "ID", "Name", "Email");
  printf("%-5s %-30s %-30s\n", "---", "----", "-----");

  while ((row = mysql_fetch_row(result))) {
    printf("%-5s %-30s %-30s\n", row[0], row[1], row[2]);
  }

  mysql_free_result(result);
}

void delete_member(MYSQL *conn) {
  int id;
  printf("member ID to delete: ");
  scanf("%d", &id);
  getchar();

  // char query[128];
  char query[1024];
  snprintf(query, sizeof(query), "DELETE FROM members WHERE id=%d", id);

  if (mysql_query(conn, query)) {
    fprintf(stderr, "delete member error: %s\n", mysql_error(conn));
    return;
  }
  printf("member deleted successfully\n");
}
