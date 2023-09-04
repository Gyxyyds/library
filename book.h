#ifndef __BOOK_H__
#define __BOOK_H__

typedef struct book
{
    char ISBN[20];          // 书籍 ISBN 号
    char name[100];         // 书籍名称
    char author[50];        // 书籍作者
    char publisher[50];     // 书籍出版社
    int quantity;           // 书籍数量
    int remaining;          // 书籍余量
} BOOK;

typedef struct _book
{
    BOOK book;
    struct _book *next;  
} node_book;

typedef struct _list_book
{
    node_book* head; // 头指针
    node_book* tail; // 尾指针
    int size;
} *list_book;

list_book create_book(void);

void inputBook(list_book l);
void addBook(list_book l, BOOK newBook);
int deleteBook(list_book l);
int modifyBook(list_book l);
BOOK* searchBook(list_book l);
void showBook(list_book l);

#endif