#include"link.h"

link* initlink()
{
    link* l = (link*)malloc(sizeof(link));
    l->head = NULL;
    l->length = 0;
    l->ptr = NULL;
    l->tail = NULL;
    return l;
}

int appendlink(link* l, char ch)
{
    if (l->head == NULL)
    {
        l->head = (linknode*)malloc(sizeof(linknode));
        l->head->ch = ch;
        l->head->next = NULL;
        l->tail = l->head;
        l->ptr = l->head;
        l->length += 1;
    }
    else
    {
        linknode* current = (linknode*)malloc(sizeof(linknode));
        current->next = NULL;
        current->ch = ch;
        l->tail->next = current;
        l->tail = current;
        l->ptr = l->head;
        l->length += 1;
    }

    return 0;
}

char getlinkchar(link* l)
{
    if (l->ptr == NULL)
    {
        return 0;
    }
    char ch = l->ptr->ch;
    l->ptr = l->ptr->next;
    return ch;
}

link* deletelink(link* l)
{
    l->ptr = NULL;
    l->tail = NULL;
    while (l->head != NULL)
    {
        linknode* current = l->head;
        l->head = l->head->next;
        free(current);
    }
    free(l);
    return NULL;
}