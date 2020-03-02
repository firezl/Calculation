#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"link.h"
#include "stringslink.h"

int main(int argc, char** argv)
{
    FILE* fp;
    if (argc > 1)
    {
        fp = fopen(argv[1], "r");
        link* l = initlink();
        if (fp != NULL)
        {
            while (!feof(fp))
            {
                char ch = fgetc(fp);
                if ((int)ch < 0)
                    continue;
                appendlink(l, ch);
            }
        }

        for (int i = l->length; i > 0; i--)
        {
            printf("%c", getlinkchar(l));
        }
        printf("\n");
    }
    else
    {
        link* l = initlink();
        char ch;
        while ((ch = getchar()) != '$')
        {
            appendlink(l, ch);
        }
        link* w = initlink();
        specialsymbol o = null;
        while ((w = getword(l, &o))!=NULL)
        {
            for (int i = 0; i < w->length; i++)
            {
                printf("%c", getlinkchar(w));
            }
            printf("\n");
        }
    }

    return 0;
}