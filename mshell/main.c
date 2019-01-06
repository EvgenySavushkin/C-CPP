#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include "list.h"
#include "tree.h"
#include "exec.h"

#define BUFF_SIZE 10

jmp_buf begin;
list *plst;
intlist *bckgrnd;
int exit_val = 0;

void handler(int s)
{
    signal(SIGINT, handler);
}

void read_command(char **s)
{
    int size = 1;
    *s = (char *) malloc(1);
    (*s)[0] = '\0';
    char buf[BUFF_SIZE];
    while(fgets(buf, BUFF_SIZE, stdin)) {
        *s = realloc(*s, size + BUFF_SIZE - 1);
        strcpy((*s) + size - 1, buf);
        size += BUFF_SIZE - 1;
        if (strlen(*s) < size - 1 || buf[BUFF_SIZE - 2] == '\n') {
            break;
        }
    }
}

tree * build_tree(list *lst)
{
    return com_sh();
}

void exec_tree(tree* tr)
{
    exec_com_sh(tr);
}

void inv()
{
    printf("%s", "\x1b[32m");
    char s[100];
    gethostname(s, 100);
    printf("%s@%s", getenv("USER"), s);
    printf("%s", "\x1B[37m");
    getcwd(s, 100);
    printf(":%s$ ", s);
}

int main()
{
    signal(SIGINT, handler);
    bckgrnd = NULL;
    char *s = NULL;
    tree *tr = NULL;
    list *lst = NULL;
    while(1) {
        setjmp(begin);
        inv();
        clear_tree(tr);
        tr = NULL;
        free_list(&lst);
        lst = NULL;
        free(s);
        s = NULL;
        if (exit_val) {
            return 0;
        }
        read_command(&s);
        if (s == NULL || strlen(s) == 0) {
            free(s);
            printf("\n");
            exit(0);
        }
        clear_zombie(&bckgrnd);
        build_list(&lst, s);
        if (lst == NULL) {
            continue;
        }
        change_lst(lst);
        plst = lst;
        tr = build_tree(lst);
	print_struct(tr);
        exec_tree(tr);
    }
}
