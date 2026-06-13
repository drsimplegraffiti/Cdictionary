````md
## Library Management System in C + MySQL

---

### Install dependencies
```bash
sudo apt install libmysqlclient-dev mysql-server
sudo systemctl start mysql
```

---

### Setup database
```sql
-- run in mysql
sudo mysql -u root -p

CREATE DATABASE library;
USE library;

CREATE TABLE books (
    id INT AUTO_INCREMENT PRIMARY KEY,
    title VARCHAR(255) NOT NULL,
    author VARCHAR(255) NOT NULL,
    quantity INT DEFAULT 1,
    available INT DEFAULT 1
);

CREATE TABLE members (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    email VARCHAR(255) UNIQUE NOT NULL
);

CREATE TABLE borrowings (
    id INT AUTO_INCREMENT PRIMARY KEY,
    book_id INT,
    member_id INT,
    borrow_date DATE DEFAULT (CURRENT_DATE),
    return_date DATE,
    FOREIGN KEY (book_id) REFERENCES books(id),
    FOREIGN KEY (member_id) REFERENCES members(id)
);

-- create app user
CREATE USER 'library_user'@'localhost' IDENTIFIED BY 'password123';
GRANT ALL PRIVILEGES ON library.* TO 'library_user'@'localhost';
FLUSH PRIVILEGES;
EXIT;
```

---

### db.h
```c
#ifndef DB_H
#define DB_H

#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

#define DB_HOST     "localhost"
#define DB_USER     "library_user"
#define DB_PASS     "password123"
#define DB_NAME     "library"
#define DB_PORT     3306

MYSQL *connect_db();
void close_db(MYSQL *conn);

#endif
```

---

### db.c
```c
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
```

---

### books.h
```c
#ifndef BOOKS_H
#define BOOKS_H

#include <mysql/mysql.h>

void add_book(MYSQL *conn);
void view_books(MYSQL *conn);
void search_book(MYSQL *conn);
void update_book(MYSQL *conn);
void delete_book(MYSQL *conn);

#endif
```

---

### books.c
```c
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

    char query[512];
    snprintf(query, sizeof(query),
        "INSERT INTO books (title, author, quantity, available) VALUES ('%s', '%s', %d, %d)",
        title, author, quantity, quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "add book error: %s\n", mysql_error(conn));
        return;
    }
    printf("book added successfully\n");
}

void view_books(MYSQL *conn) {
    if (mysql_query(conn, "SELECT id, title, author, quantity, available FROM books")) {
        fprintf(stderr, "view books error: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row;

    printf("\n%-5s %-30s %-20s %-10s %-10s\n", "ID", "Title", "Author", "Quantity", "Available");
    printf("%-5s %-30s %-20s %-10s %-10s\n", "---", "-----", "------", "--------", "---------");

    while ((row = mysql_fetch_row(result))) {
        printf("%-5s %-30s %-20s %-10s %-10s\n",
            row[0], row[1], row[2], row[3], row[4]);
    }

    mysql_free_result(result);
}

void search_book(MYSQL *conn) {
    char keyword[255];
    printf("search (title or author): ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = 0;

    char query[512];
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

    printf("\n%-5s %-30s %-20s %-10s %-10s\n", "ID", "Title", "Author", "Quantity", "Available");
    while ((row = mysql_fetch_row(result))) {
        printf("%-5s %-30s %-20s %-10s %-10s\n",
            row[0], row[1], row[2], row[3], row[4]);
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

    char query[512];
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

    char query[128];
    snprintf(query, sizeof(query), "DELETE FROM books WHERE id=%d", id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "delete error: %s\n", mysql_error(conn));
        return;
    }
    printf("book deleted successfully\n");
}
```

---

### members.h
```c
#ifndef MEMBERS_H
#define MEMBERS_H

#include <mysql/mysql.h>

void add_member(MYSQL *conn);
void view_members(MYSQL *conn);
void delete_member(MYSQL *conn);

#endif
```

---

### members.c
```c
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
    email[strcspn(email, "\n")] = 0;

    char query[512];
    snprintf(query, sizeof(query),
        "INSERT INTO members (name, email) VALUES ('%s', '%s')",
        name, email);

    if (mysql_query(conn, query)) {
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

    char query[128];
    snprintf(query, sizeof(query), "DELETE FROM members WHERE id=%d", id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "delete member error: %s\n", mysql_error(conn));
        return;
    }
    printf("member deleted successfully\n");
}
```

---

### borrowings.h
```c
#ifndef BORROWINGS_H
#define BORROWINGS_H

#include <mysql/mysql.h>

void borrow_book(MYSQL *conn);
void return_book(MYSQL *conn);
void view_borrowings(MYSQL *conn);

#endif
```

---

### borrowings.c
```c
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
    snprintf(check, sizeof(check),
        "SELECT available FROM books WHERE id=%d", book_id);

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
    char query[256];
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
    const char *query =
        "SELECT br.id, b.title, m.name, br.borrow_date, "
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

    printf("\n%-5s %-30s %-20s %-15s %-15s\n",
        "ID", "Book", "Member", "Borrowed", "Returned");
    printf("%-5s %-30s %-20s %-15s %-15s\n",
        "---", "----", "------", "--------", "--------");

    while ((row = mysql_fetch_row(result))) {
        printf("%-5s %-30s %-20s %-15s %-15s\n",
            row[0], row[1], row[2], row[3], row[4]);
    }

    mysql_free_result(result);
}
```

---

### main.c
```c
#include "db.h"
#include "books.h"
#include "members.h"
#include "borrowings.h"
#include <stdio.h>

void books_menu(MYSQL *conn) {
    int choice;
    printf("\n--- BOOKS ---\n");
    printf("1. view all\n2. add\n3. search\n4. update\n5. delete\n0. back\n");
    printf("choice: ");
    scanf("%d", &choice);
    getchar();

    switch (choice) {
        case 1: view_books(conn);   break;
        case 2: add_book(conn);     break;
        case 3: search_book(conn);  break;
        case 4: update_book(conn);  break;
        case 5: delete_book(conn);  break;
    }
}

void members_menu(MYSQL *conn) {
    int choice;
    printf("\n--- MEMBERS ---\n");
    printf("1. view all\n2. add\n3. delete\n0. back\n");
    printf("choice: ");
    scanf("%d", &choice);
    getchar();

    switch (choice) {
        case 1: view_members(conn);  break;
        case 2: add_member(conn);    break;
        case 3: delete_member(conn); break;
    }
}

void borrowings_menu(MYSQL *conn) {
    int choice;
    printf("\n--- BORROWINGS ---\n");
    printf("1. view all\n2. borrow book\n3. return book\n0. back\n");
    printf("choice: ");
    scanf("%d", &choice);
    getchar();

    switch (choice) {
        case 1: view_borrowings(conn); break;
        case 2: borrow_book(conn);     break;
        case 3: return_book(conn);     break;
    }
}

int main() {
    MYSQL *conn = connect_db();
    if (!conn) return 1;

    int choice;
    while (1) {
        printf("\n=== LIBRARY MANAGEMENT ===\n");
        printf("1. books\n2. members\n3. borrowings\n0. exit\n");
        printf("choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: books_menu(conn);     break;
            case 2: members_menu(conn);   break;
            case 3: borrowings_menu(conn); break;
            case 0:
                close_db(conn);
                printf("goodbye\n");
                return 0;
        }
    }
}
```

---

### Makefile
```makefile
CC = gcc
CFLAGS = -Wall
LIBS = -lmysqlclient

TARGET = library
SRCS = main.c db.c books.c members.c borrowings.c

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)
```

---

### Compile and run
```bash
make
./library
```

---

### File structure
```
.
├── main.c
├── db.h
├── db.c
├── books.h
├── books.c
├── members.h
├── members.c
├── borrowings.h
├── borrowings.c
└── Makefile
```

---

### Features
```
books       add, view, search, update, delete
members     add, view, delete
borrowings  borrow book, return book, view all with join
```
````
