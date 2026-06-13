
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

    CLEAR; // clear on startup

    int choice;
    while (1) {
        printf("\n=== LIBRARY MANAGEMENT ===\n");
        printf("1. books\n2. members\n3. borrowings\n9. clear\n0. exit\n");
        printf("choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: books_menu(conn);      break;
            case 2: members_menu(conn);    break;
            case 3: borrowings_menu(conn); break;
            case 9: CLEAR;                 break;
            case 0:
                close_db(conn);
                printf("goodbye\n");
                return 0;
        }
    }
}

// int main() {
//     MYSQL *conn = connect_db();
//     if (!conn) return 1;
//
//     int choice;
//     while (1) {
//         printf("\n=== LIBRARY MANAGEMENT ===\n");
//         printf("1. books\n2. members\n3. borrowings\n0. exit\n");
//         printf("choice: ");
//         scanf("%d", &choice);
//         getchar();
//
//         switch (choice) {
//             case 1: books_menu(conn);     break;
//             case 2: members_menu(conn);   break;
//             case 3: borrowings_menu(conn); break;
//             case 0:
//                 close_db(conn);
//                 printf("goodbye\n");
//                 return 0;
//         }
//     }
// }
