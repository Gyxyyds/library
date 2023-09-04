#ifndef __USER_H__
#define __USER_H__

typedef struct User 
{
    char id[19];            // 读者身份证
    char password[33];      // 读者登录密码
    char name[50];          // 读者姓名
    char gender[10];        // 读者性别
    char phone[12];         // 读者手机号
    char address[100];      // 读者住址
} USER;

typedef struct node
{
    USER user;
    struct node *next;  
} node;

typedef struct _list
{
    node* head; // 头指针
    node* tail; // 尾指针
    int size;
} *list;


list create_user(void);
USER* login_user(list l);
void inputUser(list l);
void addUser(list l, USER newUser);
void change_user_password(list l, USER* p);
int deleteUser(list l);
int modifyUser(list l);
USER* searchUser_id(list l);
USER* searchUser_name(list l);
USER* searchUser_phone(list l);
void showUser(list l);
int validatePhoneNumber(const char* phoneNumber);
int validateIDCard(const char* idCard);

#endif