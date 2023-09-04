#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "md5.h"
#include "manager.h"

void initAdmin()
{
    FILE *fp = fopen("manager.txt", "wb");

    Manager *admin = (Manager *)malloc(sizeof(Manager));

    strcpy(admin->name, "manager");
    char password[7] = "888888";
    char res_pass[33] = "";
    md5_data(password, strlen(password), res_pass);
    strcpy(admin->password, res_pass);

    fwrite(admin, sizeof(Manager), 1, fp);

    free(admin);
    fclose(fp);
}

int login_manager()
{
    FILE *fp = fopen("manager.txt", "rb");

    char inputname[50] = "";
    char inputPassword[33] = "";
    char res_password[33] = "";
    int cnt = 3;
    char choice;

    Manager *admin = (Manager *)malloc(sizeof(Manager));

    fread(admin, sizeof(Manager), 1, fp);
    fclose(fp);

    printf("请输入管理员账号：");
    scanf("%s%*c", inputname);

    if (strcmp(inputname, admin->name) == 0)
    {
        while (cnt > 0)
        {

            printf("请输入管理员密码：");
            scanf("%s%*c", inputPassword);

            md5_data(inputPassword, strlen(inputPassword), res_password);

            if (strcmp(res_password, admin->password) == 0)
            {
                printf("\n登陆成功!\n");
                if (strcmp(admin->name, "manager") == 0)
                {
                    printf("\n该密码为初始密码!\n是否修改用户名和密码?（Y/N）:");
                    scanf("%c", &choice);

                    if (choice == 'y' || choice == 'Y')
                        change_manager_password();
                }
                return 1; // 返回 1 表示登陆成功
            }
            else
            {
                cnt--;
                printf("密码错误！还剩余 %d 次机会\n", cnt);
            }
        }
    }
    else
        printf("该管理员账号不存在！\n");

    return 0; // 返回 0 表示登录失败
}

void change_manager_password()
{
    char choice;
    char new_name[50] = "";
    char new_password[33] = "";
    char again_password[33] = "";
    char res_password[33] = "";
    int k = 0;

    FILE *fp = fopen("manager.txt", "rb+");

    Manager *admin = (Manager *)malloc(sizeof(Manager));

    fread(admin, sizeof(Manager), 1, fp);

    printf("请输入新用户名：");
    scanf("%s", new_name);
    printf("请输入新密码：");
    scanf("%s%*c", new_password);

    while (!k)
    {
        printf("\n请再次输入密码：");
        scanf("%s%*c", again_password);

        if (strcmp(new_password, again_password) == 0)
        {
            k = 1;
            md5_data(new_password, strlen(new_password), res_password);
            strcpy(admin->password, res_password);
        }
        else
            printf("\n与第一次输入的密码不一致!\n请重新输入！\n");
    }
    strcpy(admin->name, new_name);
    
    fseek(fp, 0, SEEK_SET);

    fwrite(admin, sizeof(Manager), 1, fp);

    printf("用户名和密码修改成功！\n");

    free(admin);
    fclose(fp);
}
