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
#include <xc.h>
#include<delays.h>
#include<stdio.h>
#include <unmc_lcd_216.h>
#include <unmc_rtcc_01.h>
#include <unmc_config_01.h>
#include <unmc_inout_01.h>


//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/// Funcion Caratula
/// Display presentation day hour
/// variable lecture diasem, anio, dia, hora, etc
//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[

    void caratula(void)
    {
        lcd_comand(0b00001100);             //Enciende display sin cursor y sin blink  
        lcd_gotoxy(1,1);        
        lcd_putrs("UNIMIC");
        sprintf(buffer2,"%02u/%02u/%02u",dia,mes,anio);
        lcd_gotoxy(9,1);
        lcd_putrs(buffer2);
        sprintf(buffer2,"%02u:%02u:%02u",hora,minuto,segundo);
        lcd_gotoxy(1,2);
        lcd_putrs(buffer2);
        b=b++;
        if(b<7)
           {
            lcd_gotoxy(1,1);
            lcd_putrs("UNIMIC");
           }
        if(b>6)
           {
            if(b==11){b=0;}
            lcd_gotoxy(1,1);
            lcd_putrs("      ");
           }
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
    TRISA = 0b11111111;
    TRISB = 0;
    TRISC = 0b00000111;
    //TRISAbits.TRISA0=1;
    //TRISBbits.TRISB0=0;
    //TRISCbits.TRISC0=0;
    ANCON0=0b11111111;          // Config AN7 to AN0 Digital Ports
    ANCON0=0b10010111;          // Config AN11 Analog Port
    ADCON0=0b00101101;          // Control AN11 Analog Port
    ADCON1=0b00010000;          // Config Analog Port
    RTCCFGbits.RTCEN=1;
    RTCCFGbits.RTCWREN=1;
    T1CONbits.T1OSCEN=1;
    Write_RTC();
    lcd_init();
    lcd_comand(0b00001111);     //Display=on / Cursor=off / Blink=off
    LED_2_Off;
    LED_3_Off;
    }
/*------------------------------------------------------------------------------
********************************************************************************
Funcion main
Funcion principal del programa
********************************************************************************
--------------------------------------------------------------------------------*/
void setClock(int8 x){
    switch (x) {
        case 10:    
          dia++;
          if(dia > 31){
                dia = 1;
          }
          break;
        case 13:
          mes++;
          if(mes > 12){
            mes = 1;
          }
          break;
        case 16:
          anio++;
          break;
        case 2:    
          hora++;
          if(hora > 23){
             hora = 0;
          }
          break;
        case 5:
          minuto++;
            if(minuto > 59){
                minuto = 0;
            }
          break;
        default:
          break;
        }
        Write_RTC();
        __delay_ms(50);
} 
    
    
    
    
int main(void)
{
Setup();
int8 x = 9;
int8 y = 1;

while(1)
    {
    Read_RTC();
    caratula();
    lcd_setcursor_vb(1,1);
    lcd_gotoxy(x,y);
    if(switch1 == 0)
    {
        x++;
        lcd_gotoxy(x,y); 
        __delay_ms(50);
        
        if(   (x==11 && y ==1)
           || (x==14 && y ==1)
           || (x==3  && y==2)
           || (x==6  && y==2)    ){
            lcd_setcursor_vb(0,0);
            x++;  
        }
        
        if (x == 17){
            x = 1;
            y = 2;
        }
        
        if(y == 2 && x == 9){
            y = 1;
        }
    }

    if(switch2 == 0){
        setClock(x);
    }
    __delay_ms(98);             // 98ms retardo maximo para esta funcion

    }
return 0;
}
