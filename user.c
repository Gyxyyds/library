#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include <unistd.h>
#include "md5.h"
#include "user.h"

list create_user(void)          // 创建读者信息链表
{
    list l = (list)malloc(sizeof(struct _list));

    node* n = (node*)malloc(sizeof(node));

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

USER* login_user(list l)            // 读者登录函数
{
    char inputid[50] = "";
    char old_password[33] = "";
    char old_res_password[33] = "";
    char inputPassword[33] = "";
    char res_password[33] = "";
    int cnt = 3;
    char choice;

    node *p = (node*)malloc(sizeof(node));

    p = l->head->next;

    printf("请输入读者账号：");
    scanf("%s%*c", inputid);

    while (p != NULL && strcmp(p->user.id, inputid) != 0)
        p = p->next;

    if(p == NULL) 
    {
        printf("未找到身份证号为 %s 的读者！", inputid);
        sleep(1);
        system("clear");
        return NULL;
    }

    while (cnt > 0)
    {

        printf("请输入读者密码：");
        scanf("%s%*c", inputPassword);

        md5_data(inputPassword, strlen(inputPassword), res_password);

        if (strcmp(res_password, p->user.password) == 0)
        {
            printf("\n登陆成功!\n");

            strncpy(old_password, inputid + 12, 6);
    
            md5_data(old_password, strlen(old_password), old_res_password);
            if (strcmp(p->user.password, old_res_password) == 0)
            {
                printf("\n该密码为初始密码!\n是否修改密码?（Y/N）:");
                scanf("%c", &choice);

                if (choice == 'y' || choice == 'Y')
                    change_user_password(l, &p->user);
            }
            
            return &p->user;
        }
        else
        {
            cnt--;
            printf("密码错误！还剩余 %d 次机会\n", cnt);
        }
    }

    return NULL;
}

void change_user_password(list l, USER* p)      // 修改读者密码
{
    char new_password[33] = "";
    char again_password[33] = "";
    char res_password[33] = "";
    int k = 0;

    printf("请输入新密码：");
    scanf("%s%*c", new_password);

    while (!k)
    {
        printf("\n请再次输入：");
        scanf("%s%*c", again_password);

        if (strcmp(new_password, again_password) == 0)
        {
            k = 1;
            md5_data(new_password, strlen(new_password), res_password);
            strcpy(p->password, res_password);
        }
        else
            printf("\n与第一次输入的密码不一致!\n请重新输入！\n");
    }

    FILE *fp = fopen("user.txt", "wb");

    node *current = l->head->next;

    while (current != NULL)
    {
        fwrite(&(current->user), sizeof(USER), 1, fp);
        current = current->next;
    }

    fclose(fp);

    printf("读者密码修改成功！\n");
}


void inputUser(list l)              // 添加新读者
{
    USER u;
    int valid = 0;
    int valid_id = 0;

    while (!valid_id)
    {
        printf("请输入身份证号：");
        scanf("%s%*c", u.id);
        if (validateIDCard(u.id))
        {
            valid_id = 1;
            node* p = l->head->next;
            while (p != NULL)
            {
                if (strcmp(p->user.id, u.id) == 0)
                {
                    printf("该身份证号已存在，请重新输入!\n");
                    valid_id = 0;
                    break;
                }
                p = p->next;
            }
            
        }
        else printf("输入的身份证号不合法，请重新输入\n");   
            
    }

    printf("\n请输入姓名：");
    scanf("%s%*c", u.name);
    printf("请输入性别：");
    scanf("%s%*c", u.gender);

    while (!valid)
    {
        printf("请输入手机号：");
        scanf("%s%*c", u.phone);
        if (validatePhoneNumber(u.phone))
            valid = 1;
        else printf("输入的手机号不合法，请重新输入\n");
    }
    
    printf("请输入住址：");
    scanf("%s%*c", u.address);

    char res_passwoord[33] = "";
    strncpy(res_passwoord, u.id + 12, 6);
    
    md5_data(res_passwoord, strlen(res_passwoord), u.password);


    addUser(l, u);

    FILE* fp = fopen("user.txt", "ab");

    fwrite(&u, sizeof(USER), 1, fp);
    
    fclose(fp);

    printf("读者添加成功！");
}

void addUser(list l, USER newUser)     // 添加新节点函数
{
    // 创建一个新节点
    node* newNode = (node*)malloc(sizeof(node));
    
    if (NULL == newNode)
    {
        fprintf(stderr, "malloc error\n");
        return;
    }

    newNode->user = newUser;
    newNode->next = NULL;
    
    // 将新节点加入到链表中
    l->tail->next = newNode;
    l->tail = newNode;
    l->size++;

}


int deleteUser(list l)              // 删除读者
{
    USER u;
    printf("请输入想删除的读者身份证号：");
    scanf("%s%*c", u.id);
    node* p = l->head, *delNode;

    // 遍历链表找到要删除节点的前驱节点
    while(p != NULL && strcmp(p->next->user.id , u.id) != 0)
        p = p->next;

    // 如果没找到目标节点
    if(p == NULL) 
    {
        printf("未找到身份证号为 %s 的读者！", u.id); 
        return 0;
    }

    // 如果找到了目标节点就删除它
    delNode = p->next;
    p->next = delNode->next;        // 将目标节点的前后节点连接起来
    free(delNode);                  // 释放目标节点

    if(NULL == p->next) l->tail = p;

    l->size--;

    FILE* fp = fopen("user.txt", "wb");

    node* current = l->head->next;

    while (current != NULL)
    {
        fwrite(&(current->user), sizeof(USER), 1, fp);
        current = current->next;
    }
    
    fclose(fp);

    printf("身份证号为 %s 的读者已删除！", u.id);

    return 1;

}

int modifyUser(list l)              // 修改读者信息
{
    USER old_u;
    USER new_u;
    int valid = 0;
    int valid_id = 0;

    while (!valid_id)
    {
        printf("请输入需要修改的读者身份证号：");
        scanf("%s%*c", old_u.id);
        if (validateIDCard(old_u.id))
            valid_id = 1;
        else printf("输入的身份证号不合法，请重新输入\n");    
    }

    node* p = l->head->next;

    while (p != NULL && strcmp(p->user.id, old_u.id) != 0)
        p = p->next;

    if(p == NULL)
    {
        printf("\n未找到身份证号为 %s 的读者！\n", old_u.id); 
        return 0;
    }

    old_u = p->user;

    while (!valid)
    {
        printf("手机号修改为：");
        scanf("%s%*c", new_u.phone);
        if (validatePhoneNumber(new_u.phone))
            valid = 1;
        else printf("输入的手机号不合法，请重新输入\n");
    }
    strcpy(old_u.phone, new_u.phone);

    printf("地址修改为：");
    scanf("%s%*c", new_u.address);
    strcpy(old_u.address, new_u.address);

    p->user = old_u;

    FILE* fp = fopen("user.txt", "wb");

    node* current = l->head->next;

    while (current != NULL)
    {
        fwrite(&(current->user), sizeof(USER), 1, fp);
        current = current->next;
    }
    
    fclose(fp);

    printf("\n修改成功！\n");
    
    return 1;
}

USER* searchUser_id(list l)         // 通过身份证号查询读者信息
{
    USER u;
    printf("请输入需要查询的读者身份证号：");
    scanf("%s%*c", u.id);

    node* p = l->head->next;

    while (p != NULL && strcmp(p->user.id, u.id) != 0)
        p = p->next;

    if (p == NULL) 
    {
        printf("\n未找到身份证号为 %s 的读者！\n", u.id); 
        return 0;
    }

    printf("\n身份证号\t\t姓名\t性别\t电话号\t\t住址\n");
    printf("%s\t%s\t%s\t%s\t%s\n", p->user.id, p->user.name, p->user.gender,
    p->user.phone, p->user.address);

    return &(p->user);
}

USER* searchUser_name(list l)         // 通过姓名查询读者信息
{
    USER u;
    printf("请输入需要查询的读者姓名：");
    scanf("%s%*c", u.name);

    node* p = l->head->next;

    while (p != NULL && strcmp(p->user.name, u.name) != 0)
        p = p->next;

    if (p == NULL) 
    {
        printf("\n未找到姓名为 %s 的读者！\n", u.name); 
        return 0;
    }

    printf("\n身份证号\t\t姓名\t性别\t电话号\t\t住址\n");
    printf("%s\t%s\t%s\t%s\t%s\n", p->user.id, p->user.name, p->user.gender,
    p->user.phone, p->user.address);

    return &(p->user);
}

USER* searchUser_phone(list l)         // 通过手机号查询读者信息
{
    USER u;
    printf("请输入需要查询的读者手机号：");
    scanf("%s%*c", u.phone);

    node* p = l->head->next;

    while (p != NULL && strcmp(p->user.phone, u.phone) != 0)
        p = p->next;

    if (p == NULL) 
    {
        printf("\n未找到手机号为 %s 的读者！\n", u.name); 
        return 0;
    }

    printf("\n身份证号\t\t姓名\t性别\t电话号\t\t住址\n");
    printf("%s\t%s\t%s\t%s\t%s\n", p->user.id, p->user.name, p->user.gender,
    p->user.phone, p->user.address);

    return &(p->user);
}

void showUser(list l)           // 显示所有图书信息
{
    node* p = l->head->next;    // 跳过头节点

    printf("身份证号\t\t姓名\t性别\t电话号\t\t住址\n");

    // 遍历链表所有节点
    while(p != NULL)
    {
        
        printf("%s\t%s\t%s\t%s\t%s\n", p->user.id, p->user.name, p->user.gender,
        p->user.phone, p->user.address);

        p = p->next;
    }

    printf("\n");
}

int validatePhoneNumber(const char* phoneNumber)        // 手机号合法性验证
{
    int len = strlen(phoneNumber);

    // 手机号必须是11位数字
    if (len != 11) {
        return 0;
    }

    // 手机号必须由数字组成
    for (int i = 0; i < len; i++) 
    {
        if (!isdigit(phoneNumber[i])) 
            return 0;
    }

    // 手机号通常以1开头
    if (phoneNumber[0] != '1') 
        return 0;

    if (phoneNumber[1] < '3' || phoneNumber[1] > '9') 
        return 0;

    // 手机号其他数字限定在0-9之间
    for (int i = 2; i < len; i++) 
    {
        if (phoneNumber[i] < '0' || phoneNumber[i] > '9') 
            return 0;
    }

    return 1; // 合法的手机号
}

int validateIDCard(const char* idCard)      // 身份证号合法性验证
{
    int len = strlen(idCard);

    // 身份证号码必须为18位
    if (len != 18) 
        return 0;

    // 前17位必须为数字
    for (int i = 0; i < 17; i++)
    {
        if (!isdigit(idCard[i])) 
            return 0;
    }

    return 1;

    // // 校验位校验
    // int weights[] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
    // char checkDigits[] = "10X98765432";
    // int sum = 0;
    // for (int i = 0; i < 17; i++) {
    //     sum += (idCard[i] - '0') * weights[i];
    // }
    // int remainder = sum % 11;
    // char expectedCheckDigit = checkDigits[remainder];

    // // 检查校验位
    // if (idCard[17] == expectedCheckDigit) {
    //     return 1; // 合法的身份证号码
    // } else {
    //     return 0; // 非法的身份证号码
    // }
}