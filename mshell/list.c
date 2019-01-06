#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "list.h"

#define SIZE 5

void print_list(list *l) 
{
    if (l == NULL) {
        return;
    }
    list *cur;
    cur = l;
    while (cur != NULL) {
        printf("%s\n", cur -> word);
        cur = cur -> next;
    }
}

void free_list(list **l)
{
    if (*l == NULL) {
        return;
    }
    list *cur, *tmp;
    cur = *l;
    *l = NULL;
    tmp = cur -> next;
    while(cur != NULL) {
        free(cur -> word);
        free(cur);
        cur = tmp;
        if (tmp != NULL) {
            tmp = cur -> next;
        }
    }
}

int is_special(char c)
{
    if (c == ';' || c == '<' || c == '(' || c == ')') {
        return 1;
    }
    if (c == '>' || c == '&' || c == '|') {
        return 2;
    }
    return 0;
}

void parsing_error(char *s1, char *s2) 
{
    fprintf(stderr, "%s", "\x1b[31m");
    fprintf(stderr, "shell: parsing error: ");
    fprintf(stderr, "%s", "\x1b[0m");
    fprintf(stderr, "%s", s1);
    if (s2 != NULL) {
        fprintf(stderr, " '%s'", s2);
    }
    fprintf(stderr, "\n");
    longjmp(begin, 1);
}

vertex start(char c, int *i, int *w, list **cur, int *size, list **l)
{
    if (c == EOF || c == '\n') {
        return END;
    }
    if (c == ' ' || c == '\t') {
        (*i)++;
        return START;
    }
    if (*l == NULL) {
        *l = (list *)malloc(sizeof(list));
        *cur = *l;
    }
    else {
        (*cur) -> next = (list *)malloc(sizeof(list));
        *cur = (*cur) -> next;
    }
    (*cur) -> next = NULL;
    (*cur) -> word = (char *) malloc(SIZE * sizeof(char));
    *w = 0;
    *size = SIZE;
    if (c == '"') {
        (*i)++;
        return BRCK;
    }
    if (is_special(c)) {
        return SPEC;
    }
    return W;
}

vertex word(char c, int *i, int *w, list **cur, int *size)
{
    if ((*w) >= (*size)) {
        (*cur) -> word = realloc((*cur) -> word, (*size) + SIZE);
        *size += SIZE;
    }
    (*cur) -> word[*w] = '\0';
    if (c == EOF || c == '\n') {
        return END;
    }
    if (c == ' ' || c == '\t') {
        (*i)++;
        return START;
    }
    if (is_special(c)) {
        return START;
    }
    (*cur) -> word[*w] = c;
    (*w)++;
    (*i)++;
    return W;
}

vertex bracket(char c, int *i, int *w, list **cur, int *size)
{
    if ((*w) >= (*size)) {
        (*cur) -> word = realloc((*cur) -> word, (*size) + SIZE);
        *size += SIZE;
    }
    (*cur) -> word[*w] = '\0';
    if (c == '"') {
        (*i)++;
        return START;
    }
    if (c == EOF || c == '\n') {
        parsing_error("unexpected character", "\"");
        return END;
    }
    (*cur) -> word[*w] = c;
    (*w)++;
    (*i)++;
    return BRCK;
}

vertex spec(char c, int *i, int *w, list **cur)
{
    (*cur) -> word[*w] = '\0';
    if (c == EOF || c == '\n') {
        return END;
    }
    if (c == ' ' || c == '\t') {
        (*i)++;
        return START;
    }
    if (*w >= 2 || (*w == 1 && c != (*cur) -> word[0])) {
        return START;
    }
    if (is_special(c) == 1) {
        (*cur) -> word[0] = c;
        (*cur) -> word[1] = '\0';
        (*i)++;
        return START;
    }
    if (is_special(c)) {
        (*cur) -> word[*w] = c;
        (*w)++;
        (*i)++;
        return SPEC;
    }
    return START;
}

void build_list(list **l, char *s)
{
    vertex v = START;
    int i, w, size;
    list *cur = NULL;
    i = 0;
    while (v != END) {
        switch (v) {
            case START:
                v = start(s[i], &i, &w, &cur, &size, l);
                break;
            case W:
                v = word(s[i], &i, &w, &cur, &size);
                break;
            case BRCK:
                v = bracket(s[i], &i, &w, &cur, &size);
                break;
            case SPEC:
                v = spec(s[i], &i, &w, &cur);
                break;
            case END:
            default:
                break;
        }
    }
}

void change_lst(list *l) 
{
    char *s;
    while (l != NULL) {
        if (l -> word[0] == '$') {
            if ((s = getenv(l -> word + 1)) != NULL) {
                l ->word = realloc(l -> word, strlen(s));
                strcpy(l -> word, s);
            }
        }
        l = l -> next;
    }
}
