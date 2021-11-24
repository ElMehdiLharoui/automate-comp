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
    mot_clef,oprel,id,nb,err
}token;
char TableTokens[5][50]={"mot_clef","oprel","id","nb","error"};
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