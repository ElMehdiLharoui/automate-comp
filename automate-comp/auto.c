#include <stdio.h>
#include"struct.h"
#include<ctype.h>
char current_Char;
FilePlace Mot;
char next_char()
{
    current_Char=getc(Fl);
    if(current_Char=='\n')NUMLIGNE++;
    return current_Char;
}
void init_pos(){
    ReturnToplace(Fl,Mot);
}
token etat_10(token t)
{
    return t;
}
token etat_9()
{
    switch (next_char())
    {
    case 's':
        return etat_10(alors);
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
        return etat_10(sinon);
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
    switch (c)
    {
    case 'n':
        return etat_3();
        break;
    default: 
        ungetc(c,Fl);
        return si;
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
    return oprel;
}
token etat_13()
{
    char c=next_char();
    switch (c)
    {
    case '=':
        return etat_14(); 
        break;
    default:
        ungetc(c,Fl);
        return oprel;
    }
}
token etat_12()
{
    char c=next_char();
   
    switch (c)
    {
    case '>':
        return etat_14(); 
        break;
    case '=':
        return etat_14();
        break;
    default: 
        ungetc(c,Fl);
        return oprel;
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
    if(isletter(c))return etat_16();
    if(ischiffre(c))return etat_16();
    ungetc(c,Fl);
    return id;
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
    if(ischiffre(c))return etat_23();
    ungetc(c,Fl);
    return nb;
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
    if(ischiffre(c))return etat_20();
    if(c=='E')return etat_21();
    ungetc(c,Fl);
    return nb;
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
        ungetc(c,Fl);
        return nb;
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
    char c,temp;
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
    temp=current_Char;
    if((c=next_char())==EOF)return scanof;
    ungetc(c,Fl);
    current_Char=temp;
    error(Fl,current_Char);
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