#include"symbols.h"

symboltable* initsymboltable()
{
	symboltable* t = (symboltable*)malloc(sizeof(symboltable));
	t->head = NULL;
	t->length = 0;
	t->ptr = NULL;
	t->tail = NULL;
	return t;

}

int appendsymboltable(symboltable* t, link* l, symboltype s, double v1, int v2)
{
	if (t->head == NULL)
	{
		t->head = (symbol*)malloc(sizeof(symbol));
		t->head->name = l;
		t->head->type = s;
		t->head->next = NULL;
		if (s == floatnumber)
			t->head->floatvalue = v1;
		else
			t->head->intvalue = v2;
		t->length += 1;
		t->ptr = t->head;
		t->tail = t->head;
	}
	else
	{
		symbol* current = (symbol*)malloc(sizeof(symbol));
		current->next = NULL;
		current->name = l;
		current->type = s;
		if (s == floatnumber)
			current->floatvalue = v1;
		else
			current->intvalue = v2;
		t->length += 1;
		t->tail->next = current;
		t->tail = current;
	}
	return 0;
}

int modifysymboltable(symboltable* t, link* l , symboltype p, double d, int i)
{
	symbol* s = NULL;
	t->ptr = t->head;
	while ((s = getsymbol(t)) != NULL)
	{
		if (strlinkcmp(s->name, l))
		{
			break;
		}
	}
	if (s == NULL)
	{
		return 1;
	}
	s->floatvalue = d;
	s->intvalue = i;
	s->type = p;
	return 0;
}

symboltable* deletesymbletable(symboltable* t)
{
	t->ptr = NULL;
	t->tail = NULL;
	while (t->head != NULL)
	{
		symbol* current = t->head;
		t->head = t->head->next;
		free(current);
	}
	free(t);
	return NULL;
}

symbol* getsymbol(symboltable* t)
{
	if (t->ptr == NULL)
	{
		return NULL;
	}
	symbol* s = t->ptr;
	t->ptr = t->ptr->next;
	return s;
}

symbol* inquiresymbol(symboltable* t, link* l) //需要进一步完善
{
	symbol* s = NULL;
	l->ptr = l->head;
	t->ptr = t->head;
	while ((s = getsymbol(t)) != NULL)
	{
		if (strlinkcmp(s->name, l))
		{
			return s;
		}
	}
	t->ptr = t->head;
	int flag = 0;
	flag = isnumber(l);
	switch (flag)
	{
	case 0:
	{
		return NULL;
	}break;
	case 1:
	{
		s = (symbol*)malloc(sizeof(symbol));
		s->name = NULL;
		s->intvalue = stoint(l);
		s->floatvalue = 0;
		s->type = integer;
		s->next = NULL;
		return s;
	}break;
	case 2:
	{
		s = (symbol*)malloc(sizeof(symbol));
		s->name = NULL;
		s->floatvalue = stofloat(l);
		s->intvalue = 0;
		s->type = floatnumber;
		s->next = NULL;
		return s;
	}break;
	case 3:
	{
		return NULL;
	}
	default: return NULL;
		break;
	}
}

int isnumber(link* l)
{
	int dot = 0;
	char ch = '\0';
	int sub = 0;
	if ((ch = getlinkchar(l)) == '-')
	{
		sub = 1;
	}
	else
	{
		l->ptr = l->head;
	}
	while ((ch = getlinkchar(l)) != 0)
	{
		if (ch == '.')
		{
			dot++;
			continue;
		}
		if (dot >= 2)
		{
			l->ptr = l->head;
			return 3;
		}
		if (!(ch <= '9' && ch >= '0'))
		{
			l->ptr = l->head;
			return 0;
		}
	}
	l->ptr = l->head;
	return dot + 1;
}

int stoint(link* l)
{
	int sum = 0;
	char ch = '\0';
	int sub = 0;
	if ((ch = getlinkchar(l)) == '-')
	{
		sub = 1;
	}
	else
	{
		l->ptr = l->head;
	}
	while ((ch = getlinkchar(l)) != 0)
	{
		sum = (ch - '0') + sum * 10;
	}
	l->ptr = l->head;
	sum = sub == 0 ? sum : -sum;
	return sum;
}

double stofloat(link* l)
{
	int index = 0;
	int e = 0;
	char ch = '\0';
	double sum = 0.0;
	int sub = 0;
	if ((ch = getlinkchar(l)) == '-')
	{
		sub = 1;
	}
	else
	{
		l->ptr = l->head;
	}
	while ((ch = getlinkchar(l)) != 0)
	{
		index++;
		if (ch == '.')
		{
			e = index;
			continue;
		}
		sum = double((ch - '0')) + sum * 10.0;
	}
	for (int i = 0; i < l->length - e; i++)
	{
		sum /= 10;
	}
	sum = sub == 0 ? sum : -sum;
	return sum;
}

operators* pushoperator(operators* t, operatortype o)
{
	operators* current = (operators*)malloc(sizeof(operators));
	current->o = o;
	current->next = t;
	return current;
}

operators* popoperator(operators* t, operatortype* o)
{
	if (t == NULL)
	{
		return NULL;
	}
	*o = t->o;
	operators* current = t->next;
	free(t);

	return current;
}

symbol* pushsymbol(symbol* s, link* l)
{
	symbol* current = (symbol*)malloc(sizeof(symbol));
	current->name = l;
	current->next = s;
	return current;
}

symbol* popsymbol(symbol* s, link** l)
{
	if (s == NULL)
	{
		return NULL;
	}
	*l = s->name;
	symbol* current = s->next;
	free(s);
	return current;
}

