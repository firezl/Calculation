#pragma once
#ifndef SYMBOL
#define SYMBOL

#include "stringslink.h"
#define MAX_SYMBOL_SIZE 10

typedef enum
{
    integer,
    floatnumber,
} symboltype;


typedef enum
{
    _plus,
    _sub,
    _times,
    _divide,
    _equals,
    _left,
    _right,
    _integer,
    _floatnum,
    _write,
    _other

}operatortype;

typedef struct _symbol
{
    link* name;
    symboltype type;
    double floatvalue;
    int intvalue;
    struct _symbol* next;

} symbol;

typedef struct _symboltable
{
    symbol* head;
    symbol* ptr;
    symbol* tail;
    int length;
}symboltable;

typedef struct _operators
{
    operatortype o;
    struct _operators* next;
}operators;

symboltable* initsymboltable();
int appendsymboltable(symboltable*, link*, symboltype, double, int);
symboltable* deletesymbletable(symboltable*);
symbol* getsymbol(symboltable*);
symbol* inquiresymbol(symboltable*, link*);
int isnumber(link*);
int stoint(link*);
double stofloat(link*);

operators* pushoperator(operators*, operatortype);
operators* popoperator(operators*, operatortype*);

symbol* pushsymbol(symbol*, link*);
symbol* popsymbol(symbol*, link**);
#endif