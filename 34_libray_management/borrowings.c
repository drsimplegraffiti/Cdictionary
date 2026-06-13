
#include "borrowings.h"
#include <stdio.h>

void borrow_book(MYSQL *conn) {
  int book_id, member_id;

  printf("book ID: ");
  scanf("%d", &book_id);
  getchar();

  printf("member ID: ");
  scanf("%d", &member_id);
  getchar();

  // check availability
  char check[128];
  snprintf(check, sizeof(check), "SELECT available FROM books WHERE id=%d",
           book_id);

  if (mysql_query(conn, check)) {
    fprintf(stderr, "check error: %s\n", mysql_error(conn));
    return;
  }

  MYSQL_RES *result = mysql_store_result(conn);
  MYSQL_ROW row = mysql_fetch_row(result);

  if (!row || atoi(row[0]) <= 0) {
    printf("book not available\n");
    mysql_free_result(result);
    return;
  }
  mysql_free_result(result);

  // insert borrowing record
  // char query[256];
  char query[1024];
  snprintf(query, sizeof(query),
           "INSERT INTO borrowings (book_id, member_id) VALUES (%d, %d)",
           book_id, member_id);

  if (mysql_query(conn, query)) {
    fprintf(stderr, "borrow error: %s\n", mysql_error(conn));
    return;
  }

  // decrement available count
  char update[128];
  snprintf(update, sizeof(update),
           "UPDATE books SET available = available - 1 WHERE id=%d", book_id);
  mysql_query(conn, update);

  printf("book borrowed successfully\n");
}

void return_book(MYSQL *conn) {
  int borrowing_id;
  printf("borrowing ID to return: ");
  scanf("%d", &borrowing_id);
  getchar();

  // get book_id from borrowing
  char get[128];
  snprintf(get, sizeof(get),
           "SELECT book_id FROM borrowings WHERE id=%d AND return_date IS NULL",
           borrowing_id);

  if (mysql_query(conn, get)) {
    fprintf(stderr, "get error: %s\n", mysql_error(conn));
    return;
  }

  MYSQL_RES *result = mysql_store_result(conn);
  MYSQL_ROW row = mysql_fetch_row(result);

  if (!row) {
    printf("borrowing not found or already returned\n");
    mysql_free_result(result);
    return;
  }

  int book_id = atoi(row[0]);
  mysql_free_result(result);

  // set return date
  char update[256];
  snprintf(update, sizeof(update),
           "UPDATE borrowings SET return_date=CURRENT_DATE WHERE id=%d",
           borrowing_id);
  mysql_query(conn, update);

  // increment available count
  char restore[128];
  snprintf(restore, sizeof(restore),
           "UPDATE books SET available = available + 1 WHERE id=%d", book_id);
  mysql_query(conn, restore);

  printf("book returned successfully\n");
}

void view_borrowings(MYSQL *conn) {
  const char *query = "SELECT br.id, b.title, m.name, br.borrow_date, "
                      "IFNULL(br.return_date, 'not returned') "
                      "FROM borrowings br "
                      "JOIN books b ON br.book_id = b.id "
                      "JOIN members m ON br.member_id = m.id";

  if (mysql_query(conn, query)) {
    fprintf(stderr, "view borrowings error: %s\n", mysql_error(conn));
    return;
  }

  MYSQL_RES *result = mysql_store_result(conn);
  MYSQL_ROW row;

  printf("\n%-5s %-30s %-20s %-15s %-15s\n", "ID", "Book", "Member", "Borrowed",
         "Returned");
  printf("%-5s %-30s %-20s %-15s %-15s\n", "---", "----", "------", "--------",
         "--------");

  while ((row = mysql_fetch_row(result))) {
    printf("%-5s %-30s %-20s %-15s %-15s\n", row[0], row[1], row[2], row[3],
           row[4]);
  }

  mysql_free_result(result);
}
