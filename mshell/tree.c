#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "tree.h"

#define SIZE 5

void err_file()
{
    if (plst == NULL) {
        error("file name expected", NULL);
    }
    if (is_oper(plst -> word)) {
        error("unexpected operation ", plst -> word);
    }
}

void in_file(tree *t) 
{
    err_file();
    while (t != NULL) {
        t -> infile = plst -> word;
        t = t -> next;
    }
}

void out_file(tree *t) 
{
    err_file();
    while (t != NULL) {
        t -> outfile = plst -> word;
        t = t -> next;
    }
}

void out_append(tree *t) 
{
    err_file();
    while (t != NULL) {
        t -> outfile = plst -> word;
        t -> append = 1;
        t = t -> next;
    }
}

void error(char *s1, char *s2)
{
    fprintf(stderr, "%s", "\x1b[31m");
    fprintf(stderr, "shell: syntax error: ");
    fprintf(stderr, "%s", "\x1b[0m");
    fprintf(stderr, "%s", s1);
    if (s2 != NULL) {
        fprintf(stderr, " '%s'", s2);
    }
    fprintf(stderr, "\n");
    longjmp(begin, 1);
}

int is_oper()
{
    char *s = plst -> word;
    return is_next() || is_inout() || !strcmp(s, "(") || !strcmp(s, ")") || !strcmp(s, "|");
}

int is_next()
{
    char *s = plst -> word;
    return !strcmp(s, "&") || !strcmp(s, "&&") || !strcmp(s, ";") || !strcmp(s, "||");
}

int is_inout()
{
    char *s = plst -> word;
    return !strcmp(s, ">") || !strcmp(s, "<") || !strcmp(s, ">>");
}

void background_sub(tree *t)
{
    if (t == NULL) {
        return;
    }
    //background(t -> next);
    //background(t -> psubcmd);
    //background(t -> pipe);
}

void background(tree *t)
{
    while (t != NULL) {
        //background_sub(t);
        t -> backgrnd = 1;
        t = t -> pipe;
    }
}

void init_com(tree *t)
{
    t -> argv = NULL;
    t -> infile = NULL;
    t -> outfile = NULL;
    t -> backgrnd = 0;
    t -> type = NXT;
    t -> append = 0;
    t -> psubcmd = NULL;
    t -> pipe = NULL;
    t -> next = NULL;
}

tree *com_sh()
{
    tree *t;
    t = com_list();
    if (plst != NULL) {
        error("unexpected operation", NULL);
    }
    return t;
}

tree *com_list()
{
    tree *t1, *t2, *t;
    t = t1 = conv();
    while (plst != NULL &&  is_next()) {
        char *s = plst -> word;
        if (!strcmp(s, "&")) {
            background(t1);
        }
        if ((plst -> next == NULL || !strcmp(plst -> next -> word, ")")) 
            && (!strcmp(s, "&") || !strcmp(s, ";"))) {
            plst = plst -> next;
            break;
        }
        if (!strcmp(s, "&&")) {
            t1 -> type = AND;
        }
        else if (!strcmp(s, "||")) {
            t1 -> type = OR;
        }
        plst = plst -> next;
        t2 = conv();
        t1 -> next = t2;
        t1 = t2;
    }
    t1 -> type = NXT;
    t1 -> next = NULL;
    return t;
}

tree *conv()
{
    tree *t1, *t2, *t;
    t = t1 = command();
    while (plst != NULL && !strcmp(plst -> word, "|")) {
        plst = plst -> next;
        t2 = command();
        t1 -> pipe = t2;
        t1 = t2;
    }
    return t;
}

tree *command()
{
    tree *t;
    list *tmp;
    tmp = plst;
    t = simple_com();
    if (!strcmp(tmp -> word, "(")) {
        plst = plst -> next;
        t -> psubcmd = com_list();
        if (plst == NULL || strcmp(plst -> word, ")")) {
            error("')' expected", NULL);
        }
        plst = plst -> next;
    }
    if (plst != NULL && !strcmp(plst -> word, "<")) {
        plst = plst -> next;
        in_file(t);
        plst = plst -> next;
    }
    if (plst != NULL && !strcmp(plst -> word, ">")) {
        plst = plst -> next;
        out_file(t);
        plst = plst -> next;
    }
    else if (plst != NULL && !strcmp(plst -> word, ">>")) {
        plst = plst -> next;
        out_append(t);
        plst = plst -> next;
    }
    return t;
}

tree *simple_com()
{
    tree *t;
    char **argv;
    int i = 0, size = 0;
    if (plst == NULL) {
        error("filename expected", NULL);
    }
    if (is_oper(plst -> word) && strcmp(plst -> word, "(")) {
        error("unexpected operation", plst -> word);
    }
    t = (tree *) malloc(sizeof(tree));
    argv = (char **) malloc(SIZE * sizeof(char *));
    size = SIZE;
    while (plst != NULL && !is_oper()) {
        argv[i] = plst -> word;
        plst = plst -> next;
        i++;
        if (i >= size) {
            argv = realloc(argv, (size + SIZE) * sizeof(char *));
            size += SIZE;
        }
    }
    argv[i] = NULL;
    init_com(t);
    t -> argv = argv;
    if (plst != NULL && !strcmp(plst -> word, "<")) {
        plst = plst -> next;
        in_file(t);
        plst = plst -> next;
    }
    if (plst != NULL && !strcmp(plst -> word, ">")) {
        plst = plst -> next;
        out_file(t);
        plst = plst -> next;
    }
    else if (plst != NULL && !strcmp(plst -> word, ">>")) {
        plst = plst -> next;
        out_append(t);
        plst = plst -> next;
    }
    return t;
}

void print_struct(tree *t)
{
    if (t == NULL) {
        return;
    }
    int i = 0;
    printf("\nargv:       ");
    while (t -> argv[i] != NULL) {
        printf("%s ", t -> argv[i]);
        i++;
    }
    printf("\ninfile:     %s\noutfile:    %s", t -> infile, t -> outfile);
    printf("\nappend:     %d", t -> append);
    printf("\nbackground: %d", t -> backgrnd);
    printf("\ntype:       ");
    switch (t -> type) {
        case NXT:
            printf("next");
            break;
        case AND:
            printf("and");
            break;
        case OR:
            printf("or");
    }
    printf("\n");
    if (t -> psubcmd != NULL) { 
        printf("\nSubcommand: called from %s\n", t -> argv[0]);
        print_struct(t -> psubcmd);
    }
    if (t -> pipe != NULL) {
        printf("\nPipe: called from %s\n", t -> argv[0]);
        print_struct(t -> pipe);
    }
    if (t -> next != NULL) { 
        printf("\nCommand: called from %s\n", t -> argv[0]);
        print_struct(t -> next);
    }
    printf("\n");
}

void clear_tree(tree *t)
{
    if (t == NULL) {
        return;
    }
    clear_tree(t -> next);
    clear_tree(t -> pipe);
    clear_tree(t -> psubcmd);
    free(t -> argv);
    free(t);
}
