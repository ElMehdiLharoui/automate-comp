#include <stdlib.h>
#include"auto.c"
void main()
{
    token t=fail();
    printf("%s\n",TableTokens[t]);
}