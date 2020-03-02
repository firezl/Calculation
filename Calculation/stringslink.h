#pragma once
#ifndef STRINGLINK
#define STRINGLINK

#include "link.h"
#include "symbols.h"
#include <string.h>
#include <stdio.h>

typedef struct _wordnode
{
	link* l;
	struct _wordnode* next;
}wordnode;

typedef struct _words
{
	wordnode* head;
	wordnode* tail;
	wordnode* ptr;
	int length;
}words;

typedef struct _sentencenode
{
	words* w;
	int line;
	struct _sentencenode* next;
}sentencenode;

typedef struct _sentences
{
	sentencenode* head;
	sentencenode* tail;
	sentencenode* ptr;
	int length;
}sentences;

link* getoneword(link*, specialsymbol*);
link* createspecialword(specialsymbol);

words* initwords();
int appendwords(words*, link*);
link* getword(words*);
words* deletewords(words*);
words* buildwords(link*);

sentences* initsentences();
int appendsentences(sentences*, words*, int);
words* getsentence(sentences*);
sentences* deletesentences(sentences*);
sentences* buildsentences(words*);

int printlink(link*);
int printwords(words*);
int printsentences(sentences*);

#endif