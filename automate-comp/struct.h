#pragma once
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
FILE* Fl;
unsigned long NUMLIGNE=1;
unsigned long AxeNUMLIGNE;
typedef struct{
    unsigned long NUMLIGNE;
    unsigned long Rem;
}FilePlace;
typedef enum token_type{
    si,sinon,alors,oprel,id,nb,err,scanof
}token;
char TableTokens[10][20]={"si","sinon","alors","oprel","id","nb","error","scanof"};
int isletter(char c)
{
    if((c>='a' && c<='z')||(c>='A' && c<='Z'))return 1;
    return 0;
}
int ischiffre(char c)
{
    if(c>='0' && c<='9')return 1;
    return 0;
}
FilePlace RememberPlace(FILE *file)
{
    FilePlace new;
    new.NUMLIGNE=NUMLIGNE;
    new.Rem=ftell(file);
    return new;
}
void ReturnToplace(FILE *file,FilePlace He)
{
    NUMLIGNE=He.NUMLIGNE;
    fseek(file,He.Rem,SEEK_SET);
}
void error(FILE*F,char c)
{
    printf("character inattendue %c dans la ligne : %d\n", c, NUMLIGNE);
}