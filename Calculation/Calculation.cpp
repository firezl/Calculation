#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"link.h"
#include "stringslink.h"
#include"analysis.h"

int main(int argc, char** argv)
{
    FILE* fpin;
    FILE* fpout = stdout;
    if (argc > 1)
    {
        if (argc == 2)
        {
            fpin = fopen(argv[1], "r");
            link* l = initlink();
            if (fpin != NULL)
            {
                while (!feof(fpin))
                {
                    char ch = fgetc(fpin);
                    if ((int)ch < 0)
                        continue;
                    appendlink(l, ch);
                }
            }
        }
        else
        {
            fpin = fopen(argv[1], "r");
            fpout = fopen(argv[2], "w");
            link* l = initlink();
            if (fpin != NULL)
            {
                while (!feof(fpin))
                {
                    char ch = fgetc(fpin);
                    if ((int)ch < 0)
                        continue;
                    appendlink(l, ch);
                }
            }
            words* w = buildwords(l);
            sentences* s = buildsentences(w);
            words* constkey = initial();
            symboltable* t = initsymboltable();
            if (analysesentence(s, constkey, t, fpout))
                printf("error!\n");
            deletelink(l);
            deletewords(w);
            deletewords(constkey);
            deletesentences(s);
            deletesymbletable(t);
        }

    }
    else
    {
        link* l = initlink();
        char ch;
        while ((ch = getchar()) != '$')
        {
            appendlink(l, ch);
        }
        words* w = buildwords(l);
        sentences* s = buildsentences(w);
        words* constkey = initial();
        symboltable* t = initsymboltable();
        if (analysesentence(s, constkey, t, fpout))
            printf("error!\n");
        deletelink(l);
        deletewords(w);
        deletewords(constkey);
        deletesentences(s);
        deletesymbletable(t);
    }

    return 0;
}