/* 
 * File:   main.c
 * Author: Stephanie Contreras
 *
 * Created on January 15, 2023, 12:37 PM
 */
#include <p18f4620.h>
#include <stdio.h>
#include <stdlib.h>

#include <usart.h>

#pragma config OSC = HS
//#pragma config WDT = Off
//#pragma config LVP = Off
//#pragma config DEBUG = On

void rx_handler (void);

#define BUF_SIZE 25

#pragma code rx_interrupt = 0x8
void rx_int (void)
{
    _asm goto rx_handler _endasm
}
#pragma code

char James = 'j';

#pragma interrupt rx_handler
void rx_handler (void)
{
    unsigned long char c;
    int d;

    /* Obtener el caracter recibido del USART */
    c = ReadUSART();
    d = atob(c);    //Convert a string to an 8-bit signed byte.
    //putcUSART(c); // putsUSART does not accept format specifiers like printf() 
    
    printf("Single character = %c\n"
           "Unsigned decimal integer = %2u\n"
            "Unsigned hexadecimal integer with lower case = %#04x\n"
            "Same as anterior but with upper case = %4X\n\n",c,c,c,c);
    //fprintf (stdout, "hex output: %#x",c);
    
    //putrsUSART ((const rom char *)"\rPing!\r");

    /* Borrar el indicador de interrupción */
    PIR1bits.RCIF = 0;
}

void main (void)
{
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

    /* Mostrar un aviso al USART */
    putrsUSART ((const char *)"\n\rIntroduce un Caracter!\r");

    /* Habilitar prioridad de interrupción */
    RCONbits.IPEN = 1;

    /* Hacer que la interrupción de recepción sea de alta prioridad */
    IPR1bits.RCIP = 1;

    /* Habilitar todas las interrupciones de alta prioridad */
    INTCONbits.GIEH = 1;

    /* Bucle para siempre */
    while (1)
    ;
}



