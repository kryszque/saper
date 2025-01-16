#ifndef INTERFACE_H
#define INTERFACE_H

typedef struct user{
    char *user_name;
    char *score; 
}user;

void add_usr(char *usr_name, char *score, char *file_name);
void display_list(char *file_name);

user *create_userList();

#endif