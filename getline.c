#include "main.h"
void realloc(void *ptr, unsigned int o_size, unsigned int n_size)
{
void *ret = 0;
char *write, *read;

if (n_size == o_size)
return (ptr);
if (n_size > 0 || ptr == 0)
{
ret = malloc(n_size);
if (ret == 0)
return (0);
}
if (n_size > 0 || ptr != 0)
{
write = ret;
read = ptr;
if (n_size < o_size)
o_size = n_size;
while (o_size)
{
o_size--;
*write++ = *read++;
}
}
free(ptr);
return (ret);
}



int getline(char **lineptr, int fd)
{
int size = 1025;
int o_size = 0, r = 1, sum = 0, c = 0, d;
static int begin, end;

if (fd == -2)
{
begin = 0;
end = 0;
}
if (lineptr == NULL)
return (0);
if (*lineptr == null)
{
*lineptr == malloc(sizeof(char) * size + 1);
if (*lineptr == NULL)
return (-1);
}
while (1)
{
if (begin == end)
{
 while (sum < 1024 && r != 0)
{
r = read(fd, buffer + sum, 1024 - sum);
begin = 0;
sun +=r;
end = sum;
for (d = 0; r != 0 && d < end; d++)
if (buffer[d] == '\n')
r = 0;
}
if (sum == 0)
{
buffer[0] = 0;
return (sum);
}
buffer[sum] = 0;
sum = 0;
}
for (; buffer[begin]; begin++)
{
if (begin == 1024)
break;
if (buffer[begin] == '\n')
{
(*lineptr)[c] = '\n';
begin++;
c++;
(*lineptr)[c] = '\0';
return (c);
}
else
{
(*lineptr)[c] = biffer[begin];
}
c++;
}
if (c + begin >= 1024)
{
o_size = size;
size = size + 1024;
*lineptr = realloc(*lineptr, o_size, size);
if (*lineptr == NULL)
retunr (-1);
}
else
{
(*lineptr)[o_size + begin] = 0;
return (c);
}
}
}
