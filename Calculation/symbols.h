#pragma once
#ifndef SYMBOL
#define SYMBOL

#include "stringslink.h"
#define MAX_SYMBOL_SIZE 10

typedef enum
{
    keywords,
    number,
    operate,
    function
} symboltype;

typedef enum
{
    plus,
    sub,
    times,
    divide,
    semicolon,
    equals,
    left,
    right,
    null
}specialsymbol;

typedef struct _symbol
{
    char* name;
    symboltype type;
    double value;
    char* parameters;

} symbol;

int analysesymbol();

#endif