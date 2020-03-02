#pragma once
#ifndef LINKLIST
#define LINKLIST
#include <stdlib.h>

typedef struct _linknode
{
    char ch;
    struct _linknode* next;
} linknode;

typedef struct _link
{
    linknode* head;
    linknode* tail;
    linknode* ptr;
    int length;
} link;

link* initlink();
int appendlink(link* l, char ch);
char getlinkchar(link* l);
link* deletelink(link* l);

#endif