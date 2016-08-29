/*********************************************************************
 *
 *                Unimic 01 Version 1.1   10 September 2015
 *
 ***********************************************************************
 * FileName:        main.c
 * Dependencies:
 * Processor:       PIC18F26J50
 * Compiler:        XC8 1.34
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 ***********************************************************************/
/*#include <xc.h>
#include<delays.h>
#include<stdio.h>
#include <unmc_lcd_216.h>
#include <unmc_rtcc_01.h>
#include <unmc_config_01.h>
#include <unmc_inout_02.h>
*/

#include "keyboard.h"

//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/// Funcion Caratula
/// Display presentation day hour
/// variable lecture diasem, anio, dia, hora, etc
//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[

    void caratula(void)
    {
        lcd_comand(0b00001100);             //Enciende display sin cursor y sin blink  
        lcd_gotoxy(1,1);        
        lcd_putrs("UNIMIC  TECLADO ");
        //sprintf(buffer2,"%02u/%02u/%02u",dia,mes,anio);
        //lcd_gotoxy(9,1);
        //lcd_putrs(buffer2);
        //sprintf(buffer2,"%01u",key);
        lcd_gotoxy(1,2);
        //lcd_putrs(buffer2);
     
    }

//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/// Funcion Setup
///
///
//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[

    void Setup(void)
    {
    OSCTUNEbits.INTSRC=1;       //setea el oscilador de 32768 para el RTC
    OSCTUNEbits.PLLEN=0;        //desactiva PLL
    OSCCONbits.IRCF0=1;         //selecciona el clock en 8MHz
    OSCCONbits.IRCF1=1;
    OSCCONbits.IRCF2=1;
    OSCCONbits.SCS0=0;          //oscilator INTRC
    OSCCONbits.SCS1=0;
    TRISA = 0b11110000;
    TRISB = 0;
    TRISC = 0b00000111;
    //TRISAbits.TRISA0=1;
    //TRISBbits.TRISB0=0;
    //TRISCbits.TRISC0=0;
    ANCON0=0b11111111;          // Config AN7 to AN0 Digital Ports
    //ANCON1=0b10010111;          // Config AN11 Analog Port
    ANCON1=0b11111111;          // Config AN12 to AN8 Digital Ports
    ADCON0=0b00101101;          // Control AN11 Analog Port
    ADCON1=0b00010000;          // Config Analog Port
    RTCCFGbits.RTCEN=1;
    RTCCFGbits.RTCWREN=1;
    T1CONbits.T1OSCEN=1;
    Write_RTC();
    lcd_init();
    lcd_comand(0b00001100);     //Display=on / Cursor=off / Blink=off
    LED_2_On;
    LED_3_On;
    }
/*------------------------------------------------------------------------------
********************************************************************************
Funcion main
Funcion principal del programa
********************************************************************************
--------------------------------------------------------------------------------*/

/*char read_keyboard(){
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
*/    
    
int main(void){
Setup();
caratula();
while(1){
    //Read_RTC();
    //caratula();
    //lcd_gotoxy(1,2);
    
    int8 teclado[16][16];
    int8 i = 0;
    int8 j = 0;
    
    for (i = 0; i < 4; i++ ){
        for (j = 0; j < 4; j++){
            teclado [i][j] = 0;
        }
    }
    
    char input = read_keyboard();
    
    if (input == 16){
        lcd_gotoxy(1,1);
        lcd_putrs("                                ");
        lcd_gotoxy(1,1);
        lcd_putrs("null pointer");
        lcd_gotoxy(1,2);
        lcd_putrs("exception");
        input = 0;
        key = 0;
        __delay_ms(98);
    }
}    
       
return 0;
}