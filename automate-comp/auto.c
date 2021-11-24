#include <stdio.h>
#include"struct.h"
#include<ctype.h>
char mot[50];
FilePlace Mot;
char next_char()
{
    char r=getc(Fl);
    if(r=='\n')NUMLIGNE++;
    return r;
}
void init_pos(){
    ReturnToplace(Fl,Mot);
}
token etat_10()
{
    char c;
    if(isspace(c=next_char())||c==EOF)
    {
        return mot_clef;
    }
    return err; 
}
token etat_9()
{
    switch (next_char())
    {
    case 's':
        return etat_10();
        break;
    default:
        return err;
    }
}
token etat_8()
{
    switch (next_char())
    {
    case 'r':
        return etat_9();
        break;
    default:
        return err;
    }
}
token etat_7()
{
    switch (next_char())
    {
    case 'r':
        return etat_8();
        break;
    default:
        return err;
    }
}
token etat_6()
{
    switch (next_char())
    {
    case 'l':
        return etat_7();
        break;
    default:
        return err;
    }
}
token etat_4()
{
    switch (next_char())
    {
    case 'n':
        return etat_10();
        break;
    default:
        return err;
    }
}
token etat_3()
{
    switch (next_char())
    {
    case 'o':
        return etat_4();
        break;
    default:
        return err;
    }
}
token etat_2()
{
    char c=next_char();
    if(isspace(c)||c==EOF){
        return mot_clef;
    }
    switch (c)
    {
    case 'n':
        return etat_3();
        break;
    default:
        return err;
    }
}
token etat_1()
{
    switch (next_char())
    {
    case 'i':
        return etat_2();
        break;
    default:
        return err;
    }
}
token etat_0()
{
    switch (next_char())
    {
    case 's':
        return etat_1();
        break;
    case 'a':
        return etat_6();
        break;
    default:
        return err;
    }
}
token etat_14()
{
    char c;
   if(isspace(c=next_char())||c==EOF)
    {
        return oprel;
    }
    return err; 
}
token etat_13()
{
    char c=next_char();
    if(isspace(c)||c==EOF)return oprel;
    switch (c)
    {
    case '=':
        return etat_14(); 
        break;
    default:
        return err;
    }
}
token etat_12()
{
    char c=next_char();
    if(isspace(c)||c==EOF)return oprel;
    switch (c)
    {
    case '>':
        return etat_14(); 
        break;
    case '=':
        return etat_14();
        break;
    default:
        return err;
    }
}
token etat_11()
{
    char c=next_char();
    switch (c)
    {
    case '<':
        return etat_12();
        break;
    case '>':
        return etat_13();
        break;
    case '=':
        return etat_14();
        break;
    default:
        return err;
    }
}
token etat_16()
{
    char c=next_char();
    if(isspace(c)||c==EOF)return id;
    if(isletter(c))return etat_16();
    if(ischiffre(c))return etat_16();
    return err;
}
token etat_15()
{
    char c=next_char();
    if(isletter(c))return etat_16();
    return err;
}
token etat_23()
{
    char c=next_char();
    if(isspace(c)||c==EOF)return nb;
    if(ischiffre(c))return etat_23();
    return err;
}
token etat_22()
{
    char c=next_char();
    if(ischiffre(c))return etat_23();
    return err;
}
token etat_21()
{
    char c=next_char();
    if(ischiffre(c))return etat_23();
    if(c=='+' || c=='-') return etat_22();
    return err;
}
token etat_20()
{
    char c=next_char();
    if(isspace(c)||c==EOF)return nb;
    if(ischiffre(c))return etat_20();
    if(c=='E')return etat_21();
    return err;
}
token etat_19()
{
    char c=next_char();
    if(ischiffre(c))return etat_20();
    return err;
}
token etat_18()
{
    char c=next_char();
    if(isspace(c)||c==EOF)return nb;
    if(ischiffre(c))return etat_18();///////////////we know//////////////////
    switch (c)
    {
    case '.':
        return etat_19();
        break;
    case 'E':
        return etat_21();
        break;
    default:
        return err;
    }
}
token etat_17()
{
    char c=next_char();
    if(ischiffre(c))return etat_18();
    return err;
}
token fail()
{
    char c;
    token R=etat_0();
    if(R!=err)return R;
    init_pos();
    R=etat_11();
    if(R!=err)return R;
    init_pos();
    R=etat_15();
    if(R!=err)return R;
    init_pos();
    R=etat_17();
    if(R!=err)return R;
    if((c=next_char())==EOF)return scanof;
    ungetc(c,Fl);
    return err;
}
void putInFile(char*car,FILE*file)
{
    fprintf(file,"[%s]",car);
}
char* scanner(char*chemin)
{
    NUMLIGNE=1;
    Fl=fopen(chemin,"r");
    char*Lexia="Lexical_file.txt";
    FILE*LEX=fopen(Lexia,"w");
    token tok;
    char c;
    Mot=RememberPlace(Fl);
    while((tok=fail())!=scanof)
    {
        putInFile(TableTokens[tok],LEX);
        while(isspace(c=getc(Fl)));
        ungetc(c,Fl);
        Mot=RememberPlace(Fl);
    }
    fclose(Fl);
    fclose(LEX);
    return Lexia;
}