
#include "books.h"
#include <stdio.h>
#include <string.h>

void add_book(MYSQL *conn) {
  char title[255], author[255];
  int quantity;

  printf("title: ");
  fgets(title, sizeof(title), stdin);
  title[strcspn(title, "\n")] = 0;

  printf("author: ");
  fgets(author, sizeof(author), stdin);
  author[strcspn(author, "\n")] = 0;

  printf("quantity: ");
  scanf("%d", &quantity);
  getchar();

  // char query[512];
  char query[1024];
  snprintf(query, sizeof(query),
           "INSERT INTO books (title, author, quantity, available) VALUES "
           "('%s', '%s', %d, %d)",
           title, author, quantity, quantity);

  if (mysql_query(conn, query)) {
    fprintf(stderr, "add book error: %s\n", mysql_error(conn));
    return;
  }
  printf("book added successfully\n");
}

void view_books(MYSQL *conn) {
  if (mysql_query(conn,
                  "SELECT id, title, author, quantity, available FROM books")) {
    fprintf(stderr, "view books error: %s\n", mysql_error(conn));
    return;
  }

  MYSQL_RES *result = mysql_store_result(conn);
  MYSQL_ROW row;

  printf("\n%-5s %-30s %-20s %-10s %-10s\n", "ID", "Title", "Author",
         "Quantity", "Available");
  printf("%-5s %-30s %-20s %-10s %-10s\n", "---", "-----", "------", "--------",
         "---------");

  while ((row = mysql_fetch_row(result))) {
    printf("%-5s %-30s %-20s %-10s %-10s\n", row[0], row[1], row[2], row[3],
           row[4]);
  }

  mysql_free_result(result);
}

void search_book(MYSQL *conn) {
  char keyword[255];
  printf("search (title or author): ");
  fgets(keyword, sizeof(keyword), stdin);
  keyword[strcspn(keyword, "\n")] = 0;

  // char query[512];
  char query[1024];
  snprintf(query, sizeof(query),
           "SELECT id, title, author, quantity, available FROM books "
           "WHERE title LIKE '%%%s%%' OR author LIKE '%%%s%%'",
           keyword, keyword);

  if (mysql_query(conn, query)) {
    fprintf(stderr, "search error: %s\n", mysql_error(conn));
    return;
  }

  MYSQL_RES *result = mysql_store_result(conn);
  MYSQL_ROW row;

  printf("\n%-5s %-30s %-20s %-10s %-10s\n", "ID", "Title", "Author",
         "Quantity", "Available");
  while ((row = mysql_fetch_row(result))) {
    printf("%-5s %-30s %-20s %-10s %-10s\n", row[0], row[1], row[2], row[3],
           row[4]);
  }

  mysql_free_result(result);
}

void update_book(MYSQL *conn) {
  int id, quantity;
  char title[255], author[255];

  printf("book ID to update: ");
  scanf("%d", &id);
  getchar();

  printf("new title: ");
  fgets(title, sizeof(title), stdin);
  title[strcspn(title, "\n")] = 0;

  printf("new author: ");
  fgets(author, sizeof(author), stdin);
  author[strcspn(author, "\n")] = 0;

  printf("new quantity: ");
  scanf("%d", &quantity);
  getchar();

  // char query[512];
  char query[1024];
  snprintf(query, sizeof(query),
           "UPDATE books SET title='%s', author='%s', quantity=%d WHERE id=%d",
           title, author, quantity, id);

  if (mysql_query(conn, query)) {
    fprintf(stderr, "update error: %s\n", mysql_error(conn));
    return;
  }
  printf("book updated successfully\n");
}

void delete_book(MYSQL *conn) {
  int id;
  printf("book ID to delete: ");
  scanf("%d", &id);
  getchar();

  // char query[128];
  char query[1024];
  snprintf(query, sizeof(query), "DELETE FROM books WHERE id=%d", id);

  if (mysql_query(conn, query)) {
    fprintf(stderr, "delete error: %s\n", mysql_error(conn));
    return;
  }
  printf("book deleted successfully\n");
}
