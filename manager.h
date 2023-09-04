#ifndef __MANAGER_H__
#define __MANAGER_H__


typedef struct manager
{
    char name[50];
    char password[33];
} Manager;

void initAdmin();
int login_manager();
void change_manager_password();

#endif


