#define _CRT_SECURE_NO_WARNINGS
#include"analysis.h"
#include<stdio.h>

int analysesentence(sentences* s, words* w, symboltable* t, FILE* fp)
{
	operators* opst = NULL;
	symbol* sbst = NULL;
	words* onesentence = NULL;
	while ((onesentence = getsentence(s)) != NULL)
	{
		link* oneword = NULL;
		while ((oneword = getword(onesentence)) != NULL)
		{
			operatortype o = _other;
			if ((o = wordtype(oneword, w)) == _other)
			{
				sbst = pushsymbol(sbst, oneword);
			}
			else
			{
				switch (o)
				{
				case _left:
				{
					opst = pushoperator(opst, o);
				}break;
				case _times:
				{
					if (opst == NULL)
					{
						opst = pushoperator(opst, o);
					}
					else
					{
						while (opst != NULL && opst->o == _divide)
						{
							operatortype temp;
							opst = popoperator(opst, &temp);
							if (execute(temp, &sbst,t,fp))
							{
								return 1;
							}
						}
						opst = pushoperator(opst, o);
					}
				}break;
				case _divide:
				{
					if (opst == NULL)
					{
						opst = pushoperator(opst, o);
					}
					else
					{
						while (opst != NULL && opst->o == _times)
						{
							operatortype temp;
							opst = popoperator(opst, &temp);
							if (execute(temp, &sbst, t,fp))
							{
								return 1;
							}
						}
						opst = pushoperator(opst, o);
					}
				}break;
				case _plus:
				{
					if (opst == NULL)
					{
						opst = pushoperator(opst, o);
					}
					else
					{
						while (opst != NULL && (opst->o == _times || opst->o == _divide || opst->o == _sub))
						{
							operatortype temp;
							opst = popoperator(opst, &temp);
							if (execute(temp, &sbst, t,fp))
							{
								return 1;
							}
						}
						opst = pushoperator(opst, o);
					}
				}break;
				case _sub:
				{
					if (opst == NULL)
					{
						opst = pushoperator(opst, o);
					}
					else
					{
						while (opst != NULL && (opst->o == _times || opst->o == _divide || opst->o == _plus))
						{
							operatortype temp;
							opst = popoperator(opst, &temp);
							if (execute(temp, &sbst, t,fp))
							{
								return 1;
							}
						}
						opst = pushoperator(opst, o);
					}
				}break;
				case _integer:
				{
					opst = pushoperator(opst, o);
				}break;
				case _floatnum:
				{
					opst = pushoperator(opst, o);
				}break;
				case _equals:
				{
					if (opst == NULL)
					{
						opst = pushoperator(opst, o);
					}
					else
					{
						while (opst != NULL && (opst->o == _integer || opst->o == _floatnum))
						{
							operatortype temp;
							opst = popoperator(opst, &temp);
							if (execute(temp, &sbst, t,fp))
							{
								return 1;
							}
						}
						opst = pushoperator(opst, o);
					}
				}break;
				case _write:
				{
					opst = pushoperator(opst, o);
				}break;
				case _right:
				{
					operatortype temp;
					while (opst->o != _left)
					{
						opst = popoperator(opst, &temp);
						if (execute(temp, &sbst, t,fp))
						{
							return 1;
						}
					}
					opst = popoperator(opst, &temp);
				}
				default:
					break;
				}
			}
		}
		while (opst != NULL)
		{
			operatortype temp;
			opst = popoperator(opst, &temp);
			if (execute(temp, &sbst, t,fp))
			{
				return 1;
			}
		}
		if (sbst != NULL)
			return 1;
	}
	return 0;
}

int execute(operatortype o, symbol** s, symboltable* t, FILE* fp)
{
	link* temp1 = NULL;
	link* temp2 = NULL;
	switch (o)
	{
	case _times:
	{
		*s = popsymbol(*s, &temp1);
		*s = popsymbol(*s, &temp2);
		if (temp1 == NULL || temp2 == NULL)
		{
			return 1;
		}
		symbol* value1 = inquiresymbol(t, temp1);
		symbol* value2 = inquiresymbol(t, temp2);
		if (value1 == NULL || value2 == NULL)
			return 1;
		if (value1->type == floatnumber || value2->type == floatnumber)
		{
			double result = (value1->type == floatnumber ? value1->floatvalue : value1->intvalue) *
				(value2->type == floatnumber ? value2->floatvalue : value2->intvalue);
			char sresult[30] = { '\0' };
			_gcvt(result, 20, sresult);
			link* l = initlink();
			for (int i = 0; i < 30; i++)
			{
				if (sresult[i] == '\0')
				{
					break;
				}
				appendlink(l, sresult[i]);
			}
			*s = pushsymbol(*s, l);

		}
		else
		{
			int result = value1->intvalue * value2->intvalue;
			char sresult[30] = { '\0' };
			_itoa(result, sresult, 10);
			link* l = initlink();
			for (int i = 0; i < 30; i++)
			{
				if (sresult[i] == '\0')
				{
					break;
				}
				appendlink(l, sresult[i]);
			}
			*s = pushsymbol(*s, l);
		}
	}break;
	case _divide:
	{
		*s = popsymbol(*s, &temp1);
		*s = popsymbol(*s, &temp2);
		if (temp1 == NULL || temp2 == NULL)
		{
			return 1;
		}
		symbol* value1 = inquiresymbol(t, temp1);
		symbol* value2 = inquiresymbol(t, temp2);
		if (value1 == NULL || value2 == NULL)
			return 1;
		if (value1->type == floatnumber || value2->type == floatnumber)
		{
			double result = (value2->type == floatnumber ? value2->floatvalue : value2->intvalue) /
				(value1->type == floatnumber ? value1->floatvalue : value1->intvalue);
			char sresult[30] = { '\0' };
			_gcvt(result, 20, sresult);
			link* l = initlink();
			for (int i = 0; i < 30; i++)
			{
				if (sresult[i] == '\0')
				{
					break;
				}
				appendlink(l, sresult[i]);
			}
			*s = pushsymbol(*s, l);

		}
		else
		{
			int result = value2->intvalue / value1->intvalue;
			char sresult[30] = { '\0' };
			_itoa(result, sresult, 10);
			link* l = initlink();
			for (int i = 0; i < 30; i++)
			{
				if (sresult[i] == '\0')
				{
					break;
				}
				appendlink(l, sresult[i]);
			}
			*s = pushsymbol(*s, l);
		}
	}break;
	case _plus:
	{
		*s = popsymbol(*s, &temp1);
		*s = popsymbol(*s, &temp2);
		if (temp1 == NULL || temp2 == NULL)
		{
			return 1;
		}
		symbol* value1 = inquiresymbol(t, temp1);
		symbol* value2 = inquiresymbol(t, temp2);
		if (value1 == NULL || value2 == NULL)
			return 1;
		if (value1->type == floatnumber || value2->type == floatnumber)
		{
			double result = (value1->type == floatnumber ? value1->floatvalue : value1->intvalue) +
				(value2->type == floatnumber ? value2->floatvalue : value2->intvalue);
			char sresult[30] = { '\0' };
			_gcvt(result, 20, sresult);
			link* l = initlink();
			for (int i = 0; i < 30; i++)
			{
				if (sresult[i] == '\0')
				{
					break;
				}
				appendlink(l, sresult[i]);
			}
			*s = pushsymbol(*s, l);

		}
		else
		{
			int result = value1->intvalue + value2->intvalue;
			char sresult[30] = { '\0' };
			_itoa(result, sresult, 10);
			link* l = initlink();
			for (int i = 0; i < 30; i++)
			{
				if (sresult[i] == '\0')
				{
					break;
				}
				appendlink(l, sresult[i]);
			}
			*s = pushsymbol(*s, l);
		}
	}break;
	case _sub:
	{
		*s = popsymbol(*s, &temp1);
		*s = popsymbol(*s, &temp2);
		if (temp1 == NULL || temp2 == NULL)
		{
			return 1;
		}
		symbol* value1 = inquiresymbol(t, temp1);
		symbol* value2 = inquiresymbol(t, temp2);
		if (value1 == NULL || value2 == NULL)
			return 1;
		if (value1->type == floatnumber || value2->type == floatnumber)
		{
			double result = (value2->type == floatnumber ? value2->floatvalue : value2->intvalue) -
				(value1->type == floatnumber ? value1->floatvalue : value1->intvalue);
			char sresult[30] = { '\0' };
			_gcvt(result, 20, sresult);
			link* l = initlink();
			for (int i = 0; i < 30; i++)
			{
				if (sresult[i] == '\0')
				{
					break;
				}
				appendlink(l, sresult[i]);
			}
			*s = pushsymbol(*s, l);

		}
		else
		{
			int result = value2->intvalue - value1->intvalue;
			char sresult[30] = { '\0' };
			_itoa(result, sresult, 10);
			link* l = initlink();
			for (int i = 0; i < 30; i++)
			{
				if (sresult[i] == '\0')
				{
					break;
				}
				appendlink(l, sresult[i]);
			}
			*s = pushsymbol(*s, l);
		}
	}break;
	case _integer:
	{
		*s = popsymbol(*s, &temp1);
		if (temp1 == NULL)
			return 1;
		symbol* value1 = inquiresymbol(t, temp1);
		if (value1 != NULL)
			return 1;
		appendsymboltable(t, temp1, integer, 0, 0);
		*s = pushsymbol(*s, temp1);
	}break;
	case _floatnum:
	{
		*s = popsymbol(*s, &temp1);
		if (temp1 == NULL)
			return 1;
		symbol* value1 = inquiresymbol(t, temp1);
		if (value1 != NULL)
			return 1;
		appendsymboltable(t, temp1, floatnumber, 0, 0);
		*s = pushsymbol(*s, temp1);
	}break;
	case _write:
	{
		*s = popsymbol(*s, &temp1);
		if (temp1 == NULL)
			return 1;
		symbol* value1 = inquiresymbol(t, temp1);
		if (value1 == NULL)
			return 1;
		if (value1->type == integer)
		{
			fprintf(fp, "%d\n", value1->intvalue);
		}
		else
		{
			fprintf(fp, "%g\n", value1->floatvalue);
		}
	}break;
	case _equals:
	{
		*s = popsymbol(*s, &temp1);
		*s = popsymbol(*s, &temp2);
		if (temp1 == NULL || temp2 == NULL)
		{
			return 1;
		}
		symbol* value1 = inquiresymbol(t, temp1);
		symbol* value2 = inquiresymbol(t, temp2);
		if (value1 == NULL || value2 == NULL)
			return 1;
		if (value2->name == NULL)
			return 1;
		if (modifysymboltable(t, value2->name, value1->type, value1->floatvalue, value1->intvalue))
			return 1;
	}break;
	default:
		break;
	}
	return 0;
}

words* initial()
{
	char key[] = "(*/+-int float=write)";
	link* l = initlink();
	for (int i = 0; i < 22; i++)
	{
		appendlink(l, key[i]);
	}
	words* w = buildwords(l);
	deletelink(l);
	return w;
}

operatortype wordtype(link* l, words* w)
{
	int index = 0;
	link* op = NULL;
	operatortype o[] = { _left,
	_times,
	_divide,
	_plus,
	_sub,
	_integer,
	_floatnum,
	_equals,
	_write,
	_right,
	_other };
	while ((op = getword(w)) != NULL)
	{
		if (strlinkcmp(op, l))
		{
			w->ptr = w->head;
			return o[index];
		}
		index++;
	}
	w->ptr = w->head;
	return _other;
}
