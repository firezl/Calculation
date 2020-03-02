#include"stringslink.h"

link* getoneword(link* l,specialsymbol* o)
{
	if (l->ptr == NULL)
	{
		return NULL;
	}
	link* words = initlink();
	char ch=' ';
	*o = null;
	while ((ch == ' ') || (ch == '\n'))
	{
		ch = getlinkchar(l);
	}
	while ((ch != ' ') && (ch != '\n') && (ch != '\0'))
	{
		switch (ch)
		{
		case '+': {*o = plus; return words; }break;
		case '-': {*o = sub; return words; }break;
		case'*': {*o = times; return words; }break;
		case '/': {*o = divide; return words; }break;
		case '=': {*o = equals; return words; }break;
		case';': {*o = semicolon; return words; }break;
		case'(': {*o = left; return words; }break;
		case')': {*o = right; return words; }break;
		default: {appendlink(words, ch); ch = getlinkchar(l); }break;
		}
	}
	return words;
}

link* createspecialword(specialsymbol o)
{
	link* l = initlink();
	switch (o)
	{
	case plus:appendlink(l, '+'); break;
	case sub: appendlink(l, '-'); break;
	case times:appendlink(l, '*'); break;
	case divide:appendlink(l, '/'); break;
	case semicolon:appendlink(l, ';'); break;
	case equals:appendlink(l, '='); break;
	case left:appendlink(l, '('); break;
	case right:appendlink(l, ')'); break;
	default:
		break;
	}
	return l;
}



words* initwords()
{
	words* w = (words*)malloc(sizeof(words));
	w->head = NULL;
	w->length = 0;
	w->ptr = NULL;
	w->tail = NULL;
	return w;
}


int appendwords(words* w, link* l)
{
	if (w->head == NULL)
	{
		w->head = (wordnode*)malloc(sizeof(wordnode));
		w->head->l = l;
		w->head->next = NULL;
		w->length += 1;
		w->ptr = w->head;
		w->tail = w->head;
	}
	else
	{
		wordnode* current = (wordnode*)malloc(sizeof(wordnode));
		current->next = NULL;
		current->l = l;
		w->tail->next = current;
		w->tail = current;
		w->length += 1;
	}
	return 0;
}

link* getword(words* w)
{
	if (w->ptr == NULL)
	{
		return NULL;
	}
	link* l = w->ptr->l;
	w->ptr = w->ptr->next;
	return l;
}

words* deletewords(words* w)
{
	w->ptr = NULL;
	w->tail = NULL;
	while (w->head != NULL)
	{
		wordnode* current = w->head;
		w->head = w->head->next;
		free(current);
	}
	free(w);
	return NULL;
}

words* buildwords(link* l)
{
	specialsymbol o;
	words* w = initwords();
	while (l->ptr != NULL)
	{
		o = null;
		link* word = getoneword(l, &o);
		if (word->head != NULL)
		{
			if (o == null)
			{
				appendwords(w, word);
			}
			else
			{
				appendwords(w, word);
				appendwords(w, createspecialword(o));
			}
		}
		else
		{
			if (o != null)
			{
				appendwords(w, createspecialword(o));
			}
		}
	}
	return w;
}

sentences* initsentences()
{
	sentences* s = (sentences*)malloc(sizeof(sentences));
	s->head = NULL;
	s->length = 0;
	s->ptr = NULL;
	s->tail = NULL;
	return s;
}

int appendsentences(sentences* s, words* w, int line)
{
	if (s->head == NULL)
	{
		s->head = (sentencenode*)malloc(sizeof(sentencenode));
		s->head->w = w;
		s->head->next = NULL;
		s->head->line = line;
		s->tail = s->head;
		s->ptr = s->head;
		s->length += 1;
	}
	else
	{
		sentencenode* current = (sentencenode*)malloc(sizeof(sentencenode));
		current->next = NULL;
		current->line = line;
		current->w = w;
		s->tail->next = current;
		s->tail = current;
		s->length += 1;
	}
	return 0;
}

words* getsentence(sentences*s)
{
	if (s->ptr == NULL)
	{
		return NULL;
	}
	words* w = s->ptr->w;
	s->ptr = s->ptr->next;
	return w;
}

sentences* deletesentences(sentences* s)
{
	s->ptr = NULL;
	s->length = 0;
	s->tail = NULL;
	while (s->head != NULL)
	{
		sentencenode* current = s->head;
		s->head = s->head->next;
		free(current);
	}
	free(s);
	return NULL;
}

sentences* buildsentences(words* w)
{

	return nullptr;
}

int printlink(link* l)
{
	for (int i = 0; i < l->length; i++)
	{
		printf("%c", getlinkchar(l));
	}
	printf("\n");
	l->ptr = l->head;
	return 0;
}

int printwords(words* w)
{
	for (int i = 0; i < w->length; i++)
	{
		printlink(getword(w));
	}
	printf("\n");
	w->ptr = w->head;
	return 0;
}

int printsentences(sentences* s)
{
	for (int i = 0; i < s->length; i++)
	{
		printwords(getsentence(s));
	}
	printf("\n");
	s->ptr = s->head;
	return 0;
}
