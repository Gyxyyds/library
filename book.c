#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "book.h"

list_book create_book(void)
{
    list_book l = (list_book)malloc(sizeof(struct _list_book));

    node_book* n = (node_book*)malloc(sizeof(node_book));

    if (NULL == n)
    {
        fprintf(stderr, "malloc error\n");
        return NULL;
    }

    n->next = NULL;

    l->head = l->tail = n;
    l->size = 0;

    return l;    
}

void inputBook(list_book l)
{
    BOOK b;
    int valid_ISBN = 0;

    while (!valid_ISBN)
    {
        printf("请输入ISBN号：");
        scanf("%s%*c", b.ISBN);

        valid_ISBN = 1;

        node_book* p = l->head->next;

        while (p != NULL)
            {
                if (strcmp(p->book.ISBN, b.ISBN) == 0)
                {
                    printf("该 ISBN 号已存在，请重新输入!\n");
                    valid_ISBN = 0;
                    break;
                }
                p = p->next;
            }
    }
    printf("\n请输入书名：");
    scanf("%s%*c", b.name);
    printf("请输入作者：");
    scanf("%s%*c", b.author);
    printf("请输入出版社：");
    scanf("%s%*c", b.publisher);
    printf("请输入数量：");
    scanf("%d%*c", &b.quantity);
    b.remaining = b.quantity;

    addBook(l, b);

    FILE* fp = fopen("book.txt", "ab");

    fwrite(&b, sizeof(BOOK), 1, fp);
    
    fclose(fp);

    printf("图书添加成功！");
}

void addBook(list_book l, BOOK newBook)     // 添加图书
{
    // 创建一个新节点
    node_book* newnode_book = (node_book*)malloc(sizeof(node_book));
    
    if (NULL == newnode_book)
    {
        fprintf(stderr, "malloc error\n");
        return;
    }

    newnode_book->book = newBook;
    newnode_book->next = NULL;
    
    // 将新节点加入到链表中
    l->tail->next = newnode_book;
    l->tail = newnode_book;
    l->size++;

}

int deleteBook(list_book l)    // 删除图书
{
    BOOK b;
    printf("请输入想删除的图书 ISBN 号：");
    scanf("%s%*c", b.ISBN);

    node_book* p = l->head, *delnode_book;

    // 遍历链表找到要删除节点的前驱节点
    while(p != NULL && strcmp(p->next->book.ISBN ,b.ISBN) != 0)
        p = p->next;

    // 如果没找到目标节点
    if(p == NULL)
    {
        printf("未找到 ISBN 号为 %s 的图书！", b.ISBN); 
        return 0;
    }
    // 如果找到了目标节点就删除它
    delnode_book = p->next;
    p->next = delnode_book->next;  // 将目标节点的前后节点连接起来
    free(delnode_book);            // 释放目标节点

    if(NULL == p->next) l->tail = p;

    l->size--;


    FILE* fp = fopen("book.txt", "wb");

    node_book* current = l->head->next;

    while (current != NULL)
    {
        fwrite(&(current->book), sizeof(BOOK), 1, fp);
        current = current->next;
    }
    
    fclose(fp);

    printf("ISBN 号为 %s 的图书已删除！", b.ISBN);

    return 1;

}

int modifyBook(list_book l)     // 修改图书信息
{
    BOOK old_b;
    int n;
    printf("请输入需要修改的图书 ISBN 号：");
    scanf("%s%*c", old_b.ISBN);

    node_book* p = l->head->next;

    while (p != NULL && strcmp(p->book.ISBN ,old_b.ISBN) != 0)
        p = p->next;

    if(p == NULL)
    {
        printf("\n未找到 ISBN 号为 %s 的图书！\n", old_b.ISBN); 
        return 0;
    }

    printf("\n请输入需要改变该图书数量：");
    scanf("%d%*c", &n);

    if (n < 0 && p->book.remaining * -1 >= n)
    {
        printf("修改后图书余量小于 0 本！\n修改失败！");
        return 0;
    }
    else 
    {
        p->book.quantity += n;
        p->book.remaining += n;
    }

    FILE* fp = fopen("book.txt", "wb");

    node_book* current = l->head->next;

    while (current != NULL)
    {
        fwrite(&(current->book), sizeof(BOOK), 1, fp);
        current = current->next;
    }
    
    fclose(fp);

    printf("\n修改成功！\n");
    
    return 1;
}

BOOK* searchBook(list_book l)       //  查询图书信息
{
    BOOK b;
    printf("请输入需要查询的图书 ISBN 号：");
    scanf("%s%*c", b.ISBN);

    node_book* p = l->head->next;

    while (p != NULL && strcmp(p->book.ISBN ,b.ISBN) != 0)
        p = p->next;

    if (p == NULL) 
    {
        printf("未找到 ISBN 号为 %s 的图书！", b.ISBN); 
        return 0;
    }

    printf("\nISBN\t图书名\t\t作者\t\t出版社\t\t总量\t余量\n");
    printf("%s\t%s\t\t%s\t\t%s\t%d\t%d\n", p->book.ISBN, p->book.name, p->book.author,
        p->book.publisher, p->book.quantity, p->book.remaining);


    return &(p->book);
}

void showBook(list_book l)      // 显示所有图书信息
{
    node_book* p = l->head->next;  // 跳过头节点

    printf("ISBN\t图书名\t\t作者\t\t出版社\t\t总量\t余量\n");

    // 遍历链表所有节点
    while(p != NULL)
    {
        
        printf("%s\t%s\t\t%s\t\t%s\t%d\t%d\n", p->book.ISBN, p->book.name, p->book.author,
        p->book.publisher, p->book.quantity, p->book.remaining);

        p = p->next;
    }

    printf("\n");
}

// void traverse(list_book l, BOOK* a, int (*visit)(BOOK*, BOOK*))
// {
//     node_book* p = l->head->next;  // 跳过头节点

//     // 遍历链表所有节点 
//     while(p != NULL)
//     {
//         if(!visit(&(p->book), a))
//             break;

//         p = p->next;
//     }    
// }

// int visit_by_book_ISBN(BOOK* b, BOOK* a)
// {
//     if (strcmp(b->ISBN, a->ISBN) == 0)
//     {
//         printf("%s\t%s\t%s\t%s\t%d\t%d\n", b->ISBN, b->name, b->author,
//         b->publisher, b->quantity, b->remaining);
//     }
//     return 0;
// }


