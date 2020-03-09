#pragma once
#ifndef ANALYSIS
#define ANALYSIS
#include"symbols.h"
#include<stdio.h>

int analysesentence(sentences*, words*, symboltable*, FILE*);
int execute(operatortype, symbol**, symboltable*, FILE*);
words* initial();
operatortype wordtype(link*, words*);
#endif // !ANALYSIS
