/* 
 * File:   main.c
 * Author: Rommel Contreras
 *
 * Created on January 15, 2023, 12:37 PM
 */

#include <p18f4620.h>
#include <stdio.h>
#include <stdlib.h>
//#include <spi.h>
#include <usart.h>
//#include "sensor_TC77.h"
#include <math.h>

#pragma config OSC = HS
#pragma config XINST = OFF  //Extended Instrution Set
#pragma config WDT = OFF
//#pragma config LVP = Off
//#pragma config DEBUG = On

void rx_handler (void);

#define BUF_SIZE 25

// El vector de alta prioridad está en la dirección 0x0008 
// y el vector de baja prioridad está en la dirección 0x0018.
#pragma code rx_interrupt = 0x8
void rx_int (void)
{
    _asm goto rx_handler _endasm
}
#pragma code

//unsigned char dummy[10] = { 0x42, 0x00, 0x41, 0x04, 0xA4, 0xA5, 0xA6, 0xA7,0xA8, 0xA9};
#define Vref 2.5
#define LSB 1/(pow(2,23)-1)
#define GAIN 1;

unsigned float dataframe_24(unsigned char* dummy, unsigned float* data, int length);
unsigned char dummy[10]={0xDE, 0xAD, 0xBE, 0xEF, 0xFF, 0xDE, 0xAD, 0xBE, 0xEF, 0xFF};
unsigned float data[((sizeof(dummy)/3))], AAA[((sizeof(dummy)/3))];
unsigned short long aux[3];
int i, *length = sizeof(dummy), dl;

int t;

unsigned short long p, u, y;
unsigned short long  w[8];

//void data_print(unsigned float* data, int dl);
unsigned float dataframe_24(unsigned char* dummy, unsigned float* data, int length){
    unsigned char i;
    int n = 5; //length;
    unsigned short long aux[3];
    for(i=0; i < length/3 ;++i){
        aux[0]= (0x000000 | dummy[i*3+1]);// | (dummy[1]<<8);// | (dummy[(2)]);
        aux[0]=((aux[0])<<16);
        aux[1]=(0x000000 | dummy[i*3+2]);
        aux[1]=(aux[1]<<8);
        aux[2]= dummy[i*3+3];
        aux[0]=aux[0]|aux[1]|aux[2];
        aux[0]= aux[0] ^ 0x800000;
        //data= (0xFFFFFF-1)*(Vref*LSB)/GAIN;
        data[i]= ((aux[0]-1)*Vref*LSB)/GAIN;
        //printf("%HS\n",data);
        //AAA[i] = data[i];
    }
    return;
}

/* el micro detiene la ejecución del programa en curso y da un salto de programa 
 * para llegar al vector de interrupción (ISR) ejecutando el bloque de 
 * código que allí se encuentre*/
#pragma interrupt rx_handler
void rx_handler (void){
    unsigned  char c;

    int i, *lenght = sizeof(dummy), dl;
    int d;
    unsigned float R = data[0];
    char q[10];
    Nop();
    
    /* Obtener el caracter recibido del USART */
    c = ReadUSART();
    
    // Rommel Aser
    //t = dataframe_24(dummy, data, length);
    
    d = atob(c);    //Convert a string to an 8-bit signed byte.
    ltoa(1458, q);
    
    //putcUSART(c); // putsUSART does not accept format specifiers like printf() 
    
    printf("Single character = %c\n"
           "Unsigned decimal integer = %2u\n"
            "Unsigned hexadecimal integer with lower case = %#04x\n"
            "Same as anterior but with upper case = %4X\n"
            "hex output: %f\n\n",c,c,c,c,R);
    
    //putrsUSART ((const rom char *)"\rPing!\r");
    Nop();

    //printf ( "hex output: %2.4f",2.4567);

    /* Borrar el indicador de interrupción */
    PIR1bits.RCIF = 0;
    Nop();
}

void main (void)
{
    
    Nop();
    // configurar los registros
    TRISB = 0x12; // 0b00010010; // puerto rx y tx establecido en 1
    PORTB = 0x01; // 0b00000001; // 1: apagado, 0: encendido (para que parpadee el LED RB0)
    ADCON1 = 0x70; // 0b01110000; // establecer RB0, PCFG6 y PCFG5 como RCSTAbits digitales.SPEN  = 1; // establece el bit de habilitación del puerto serie
    TXSTAbits.TXEN = 1; // establece el bit de habilitación de transmisión

    /* Abre el USART configurado como 8N1, 4800 baudios, en modo sondeado @ 4MHZ*/
    OpenUSART (USART_TX_INT_OFF &
    USART_RX_INT_ON &
    USART_ASYNCH_MODE &
    USART_EIGHT_BIT &
    USART_CONT_RX &
    USART_BRGH_HIGH, 52);
    
   
    while (1){
        dataframe_24(dummy, data, length);
        for (i; i<=3; i++){ 
            fprintf(t,"%u",7);
            printf ( "hex output: %d",4);
            Nop();
            Nop();
            //######################
        }

    }
}
