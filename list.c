#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "manager.h"
#include "user.h"
#include "book.h"
#include "list.h"

void list_mem()
{
    FILE* fp_user = fopen("user.txt", "rb+");
    list l_user = create_user();
    USER* q = (USER*)malloc(sizeof(USER));

    while (fread(q, sizeof(USER), 1, fp_user))  // 遍历文件user.txt
        addUser(l_user, *q);        

    free(q);
    fclose(fp_user);

    FILE* fp_book = fopen("book.txt", "rb+");
    list_book l_book = create_book();
    BOOK* p = (BOOK*)malloc(sizeof(BOOK));

    while (fread(p, sizeof(BOOK), 1, fp_book))  // 遍历文件book.txt
        addBook(l_book, *p);        

    free(p);
    fclose(fp_book);

    int choice;

    while (1)
    {
        system("clear");
        printf("\n************************************\n");
        printf("\t欢迎使用图书管理系统\n");
        printf("\n");
        printf("\t   1.管理员模式\n");
        printf("\t   2.读者模式\n");
        printf("\t   0.退出系统\n");
        printf("\n************************************\n");
        printf("\n请选择你的操作 >: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
        
        switch (choice)
        {
        case 0:
            system("clear");
            printf("\t即将退出系统...\n\t感谢使用！\n");
            sleep(1);
            system("clear");
            return;
        case 1:
            system("clear");
            if (login_manager() == 0)
            {
                sleep(1);
                break;
            }
            system("clear");
            list_manager(l_user, l_book);
            break;
        
        case 2:
            system("clear");
            list_user(l_user, l_book);
            system("clear");           
            break;
        default:
            system("clear");
            printf("输入错误，请重新输入\n");
            sleep(1);
            system("clear");
        }
    }
}

void list_manager(list u, list_book b)
{
    int choice = 0;

    while (1)
    {
        printf("\n************************************\n");
        printf("\t管理员模式\n");
        printf("\n");
        printf("    1.修改用户名和密码\n");
        printf("    2.图书管理\n");
        printf("    3.读者管理\n");
        printf("    4.查询图书借阅和归还记录\n");
        printf("    0.退出管理员模式\n");
        printf("\n************************************\n");
        printf("\n请选择你的操作 >: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
        
        switch (choice)
        {
        case 0:
            system("clear");
            printf("\t即将退出管理员模式...\n");
            sleep(1);
            system("clear");
            return;
        case 1:
            system("clear");
            change_manager_password();
            system("clear");
            break;
        case 2:
            system("clear");
            list_mem_book(b);
            break;
        case 3:
            system("clear");
            list_mem_user(u);
            break;
        case 4:
            system("clear");
            
            break;
        default:
            printf("输入错误，请重新输入\n");
        }
    }

}

void list_mem_book(list_book b)
{
    int choice;

    while (1)
    {
        printf("\n************************************\n");
        printf("\t图书管理模式\n");
        printf("\n");
        printf("\t1.添加图书信息\n");
        printf("\t2.删除图书信息\n");
        printf("\t3.修改图书信息\n");
        printf("\t4.查询图书信息\n");
        printf("\t5.显示所有图书信息\n");
        printf("\t0.退出图书管理模式\n");
        printf("\n************************************\n");
        printf("\n请选择你的操作 >: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
        
        switch (choice)
        {
        case 0:
            system("clear");
            printf("\t即将退出图书管理模式...\n");
            sleep(1);
            system("clear");
            return;
        case 1:
            system("clear");
            inputBook(b);               // 添加图书
            sleep(1);
            system("clear");
            break;
        case 2:
            system("clear");
            deleteBook(b);              // 删除图书
            sleep(1);
            system("clear");
            break;
        case 3:
            system("clear");
            modifyBook(b);              // 修改图书
            sleep(1);
            system("clear");
            break;;
        case 4:
            system("clear");
            searchBook(b);              // 查找图书
            printf("\n请按回车继续...");
            while (getchar() != '\n');
            system("clear");
            break;
        case 5:
            system("clear");
            showBook(b);                // 显示所有图书
            printf("\n请按回车继续...");
            while (getchar() != '\n');
            system("clear");
            break;            
        default:
            printf("输入错误，请重新输入\n");
            sleep(1);
            system("clear");
        }
    }

}

void list_mem_user(list u)
{
    int choice;
    system("clear");

    while (1)
    {
        printf("\n************************************\n");
        printf("\t  读者管理模式\n");
        printf("\n");
        printf("\t1.添加读者信息\n");
        printf("\t2.删除读者信息\n");
        printf("\t3.修改读者信息\n");
        printf("\t4.查询读者信息\n");
        printf("\t5.显示所有读者信息\n");
        printf("\t0.退出读者管理模式\n");
        printf("\n************************************\n");
        printf("\n请选择你的操作 >: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
        
        switch (choice)
        {
        case 0:
            system("clear");
            printf("\t即将退出读者管理模式...\n");
            sleep(1);
            system("clear");
            return;
        case 1:
            system("clear");
            inputUser(u);       // 添加读者
            sleep(1);
            system("clear");
            break;
        case 2:
            system("clear");
            deleteUser(u);      // 删除读者
            sleep(1);
            system("clear");
            break;
        case 3:
            system("clear");
            modifyUser(u);      // 修改读者信息
            sleep(1);
            system("clear");
            break;
        case 4:
            system("clear");
            list_user_sear(u);  // 查询读者信息
            break;
        case 5:
            system("clear");
            showUser(u);        // 显示所有读者信息
            printf("\n请按回车继续...");
            while (getchar() != '\n');
            system("clear");
            break;
        default:
            printf("输入错误，请重新输入\n");
        }
    }

}

void list_user(list u, list_book b)
{
    USER* in;
    in = login_user(u);

    if (in == NULL)
        return;
    
    system("clear");
    
    int choice;

    while (1)
    {
        printf("\n************************************\n");
        printf("\t读者模式\n");
        printf("    1.修改登录密码\n");
        printf("    2.查看个人信息\n");
        printf("    3.查看个人借阅和归还记录\n");
        printf("    4.借书（显示所有图书）\n");
        printf("    5.还书\n");
        printf("    0.退出读者模式\n");
        printf("\n************************************\n");
        printf("\n请选择你的操作 >: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
        
        switch (choice)
        {
        case 0:
            system("clear");
            printf("\t即将退出读者模式...\n");
            sleep(1);
            return;
        case 1:
            system("clear");
            change_user_password(u, in);
            sleep(1);
            system("clear");
            break;
        case 2:
            system("clear");
            
            break;
        case 3:
            system("clear");
            
            break;
        case 4:
            system("clear");
            showBook(b);
            
            break;
        default:
            printf("输入错误，请重新输入\n");
        }
    }

}

void list_user_sear(list u)
{
    int choice;

    while (1)
    {
        printf("\n************************************\n");
        printf("\t查询模式\n");
        printf("    1.通过身份证查询\n");
        printf("    2.通过姓名查询\n");
        printf("    3.通过手机号查询\n");
        printf("    0.退出查询模式\n");
        printf("\n************************************\n");
        printf("\n请选择你的操作 >: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
        
        switch (choice)
        {
        case 0:
            system("clear");
            printf("\t即将退出查询模式...\n");
            sleep(1);
            return;
        case 1:
            system("clear");
            searchUser_id(u);   
            printf("\n请按回车继续...");
            while (getchar() != '\n');
            system("clear");
            break;
        case 2:
            system("clear");
            searchUser_name(u);  
            printf("\n请按回车继续...");
            while (getchar() != '\n');
            system("clear");
            break;
        case 3:
            system("clear");
            searchUser_phone(u);  
            printf("\n请按回车继续...");
            while (getchar() != '\n');
            system("clear");
            break;
        default:
            printf("输入错误，请重新输入\n");
        }
    }


}