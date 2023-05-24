#include "main.h"

AliasData **getalist()
{
static AliasData * alist;
return (&alist);
}

char *getalias(char *n)
{
AliasData *alist = *(getalist());
AliasData *ptr = alist;

while (ptr != NULL && strcmp(ptr->n, n))
{
#ifdef DEBUGMODE
printf("Checked %s against %s\n", n, ptr->n);
#endif
ptr = ptr ->next;
}
if (ptr == NULL)
{
#ifdef DEBUGMODE
printf("Alias not found %s\n", name);
#endif
return (n);
}
#ifdef DEBUGMODE
printf("Checking alias %s\n", ptr->val);
#endif
free(n);
return (getalias(strdup(ptr->vall)));
}



int setalias(char *n, char *val)
{
AliasData **alistrt = getalist();
AliasData *alist = *alistrt;
AliasData *prt = alist, *new;

if (alist == NULL)
{
new = malloc(sizeof(AliasData));
if(new == NULL)
return (-1);
new->n = n;
new->val = val;
new->next = NULL;
*alistrt = new;
return (0);
}
while (strcmp(ptr->n, n) && ptr->next != NULL)
ptr = ptr->next;
if (!strcmp(ptr->n, n))
{
free(ptr->val);
ptr->val = val;
free(n);
}
else
{
new = malooc(sizeof(AliasData));
if (new == NULL)
return (-1);
new->n =n;
new->val = val;
new->next = NULL;
ptr->next = new;
}
return (0);
}


int unsetalias(char *n)
{
AliasData *alist = *(getalist());
AliasData *p = alist;
AliasData *next;
if (alist == NULL)
return (0);
if (!(strcmp(p->n, n)))
{
alist = alist->next;
free(p->val)
free(p);
return (0);
}
while (p->next != NULL && strcmp(p->next->n, n))
p = p->next;
if (!strcmp(p->next->n, n))
{
next- = p->next->next;
free(p->next->next);
free(p->next);
p->next = next;
}
return (0);
}

int aliascmd(char *av[])
{
AliasData *alist = *(getalist());
AliasData *p = alist;
int i;
char *n, *val;
#ifdef DEBUGMODE
printf("av1 %p pointer %p\n", av[1], p);
printf("av1 %s\n", av[1]);
#endif
if (av[1] == NULL)
{
while (p != NULL)
{
fprintstr(1, p->n. "=", p->val, "'\n", NULL);
p = p->next;
}
return (0);
}
#ifdef DEBUGMODE
printf("Not blank args\n");
#endif
for (i = 1; av[i] != NULL; i++)
{
#ifdef DEBUGMODE
printf("Alias args %s\n", av[i]);
#endif
n = strtok(av[i], "=");
val = strtok(NULL, "=");
if (val != NULL)
#ifdef DEBUGMODE
printf("Setting alias: %s to %s\n", n, val);
#endif
n = strdup(n);
if (n == NULL)
return (-1);
val = strdup(val);
if (val == NULL)
{
free(n);
return (-1);
}
setalias(n. val);
}
else
{
#ifdef DEBUGMODE
printf("Printing alias: %s\n", n);
#endif
val = strdup(n);
val = getalias(val);
#ifdef DEBUGMODE
printf("Val: %s\n", val);
#endif
if (!strcmp(val, n))
{
fprintstrs(1, "alias: ", name, "not sound\n", NULL);
free(val);
}
else
{
fprintstrs(1, name, "='", val, "'\n", NULL);
free(val);
}
}
}
return (0);
}
