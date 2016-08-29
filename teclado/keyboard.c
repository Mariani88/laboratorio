#include "keyboard.h"
#include <unmc_rtcc_01.h>

char read_keyboard(){
    row1=1;row2=0;row3=0;row4=0;
    {
        if (column1==1){key=1;sprintf(buffer2,"%01u",key);lcd_putrs(buffer2);while(column1==1){};}
        if (column2==1){key=2;sprintf(buffer2,"%01u",key);lcd_putrs(buffer2);while(column2==1){};}
        if (column3==1){key=3;sprintf(buffer2,"%01u",key);lcd_putrs(buffer2);while(column3==1){};}
        if (column4==1){key=11;lcd_putrs("A");while(column4==1){};}
    }
    row1=0;row2=1;row3=0;row4=0;
    {
        if (column1==1){key=4;sprintf(buffer2,"%01u",key);lcd_putrs(buffer2);while(column1==1){};}
        if (column2==1){key=5;sprintf(buffer2,"%01u",key);lcd_putrs(buffer2);while(column2==1){};}
        if (column3==1){key=6;sprintf(buffer2,"%01u",key);lcd_putrs(buffer2);while(column3==1){};}
        if (column4==1){key=12;lcd_putrs("B");while(column4==1){};}
    }
    row1=0;row2=0;row3=1;row4=0;
    {
        if (column1==1){key=7;sprintf(buffer2,"%01u",key);lcd_putrs(buffer2);while(column1==1){};}
        if (column2==1){key=8;sprintf(buffer2,"%01u",key);lcd_putrs(buffer2);while(column2==1){};}
        if (column3==1){key=9;sprintf(buffer2,"%01u",key);lcd_putrs(buffer2);while(column3==1){};}
        if (column4==1){key=13;lcd_putrs("C");while(column4==1){};}
    }
    row1=0;row2=0;row3=0;row4=1;
    {
        if (column1==1){key=14;lcd_putrs("*");while(column1==1){};}
        if (column2==1){key=0;sprintf(buffer2,"%01u",key);lcd_putrs(buffer2);while(column2==1){};}
        if (column3==1){key=15;lcd_putrs("#");while(column3==1){};}
        if (column4==1){key=16;lcd_putrs("D");while(column4==1){};}
    }
    __delay_ms(98);             // 98ms retardo maximo para esta funcion

    
     return key;   
}
