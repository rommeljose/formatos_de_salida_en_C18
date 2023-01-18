/* 
 * File:   ADC.c
 * Author: Rommel Contreras
 *
 * Created on January 15, 2023, 06:00 PM
 */
#include <p18f4620.h>
#include <stdio.h>
#include <stdlib.h>
#include <adc.h>
#include <delays.h>

#include <usart.h>
#include <math.h>

#define BUF_SIZE 25
void rx_handler (void);

// El vector de alta prioridad está en la dirección 0x0008 
// y el vector de baja prioridad está en la dirección 0x0018.
#pragma code rx_interrupt = 0x8
void rx_int (void)
{
    _asm goto rx_handler _endasm
}
#pragma code


/* el micro detiene la ejecución del programa en curso y da un salto de programa 
 * para llegar al vector de interrupción (ISR) ejecutando el bloque de 
 * código que allí se encuentre*/
#pragma interrupt rx_handler
void rx_handler (void){
    unsigned  char c;
    
    /* Obtener el caracter recibido del USART */
    c = ReadUSART();
    
    //putcUSART(c); // putsUSART does not accept format specifiers like printf() 
    
    //putrsUSART ((const rom char *)"\rPing!\r");
    Nop();

    //printf ( "hex output: %2.4f",2.4567);

    /* Borrar el indicador de interrupción */
    PIR1bits.RCIF = 0;
    Nop();
}
 
//Bits de configuración para Fosc = 48Mhz
//#pragma config PLLDIV = 5, CPUDIV = OSC1_PLL2, USBDIV = 2
//#pragma config FOSC = HSPLL_HS, FCMEN = OFF, IESO = OFF
//#pragma config PWRT = OFF, BOR = OFF, VREGEN = OFF
//#pragma config WDT = OFF, WDTPS = 32768
#pragma config MCLRE = ON, LPT1OSC = OFF, PBADEN = OFF
//#pragma config STVREN = ON, LVP = OFF, ICPRT = OFF, XINST = OFF

#pragma config OSC = HS
#pragma config XINST = OFF  //Extended Instrution Set
#pragma config WDT = OFF
 
//#define _XTAL_FREQ 48000000
 
//int *resultado;
unsigned  int analin;
float valor;
char buf[10];
float test = 12.3456789;

void ftoa (float fval, char *buf, int nField, int nPlaces) 
 { 
 // Formats a floating point number into it's ASCII representation.
 // https://www.microchip.com/forums/m466563.aspx
 // Emulates %[w].[p]f in printf format statements for those using C18 which does support %f
 // 	Input:
 //		fval	the float to be converted to ASCII
 //		buf		a char array to contain the return string
 //		nField	total width of resulting field. Equivalent to the [width] field of printf
 //		nPlaces	width of fractional part. Equivalent to the [precision] field of printf
 //	Output:
 //		buf		Null terminated formatted string
 //
 // e.g ftoa(12.3456789,&buf,10,5); will produce buf  containing '  12.34567'
 // 
 	sprintf (buf,"%*d.%0*lu", nField-nPlaces-1, (int) fval, nPlaces, (long int) ((fval - (int) fval ) * pow(10, nPlaces)) ); 
 }

void main()
{
    TRISD = 0;
    PORTD = 0;
 
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

    /* Display a prompt to the USART */
    putrsUSART ((const far rom char *)"\n\rLero Lero!\n\r");

    /*Configuración del módulo AD
    * Fosc = 64
    * Alineación = derecha
    * 16 TAD
    * Canal AN0
    * Interrupción deshabilitada
    * VREF+ y VREF- conectados a VDD y VSS respectivamente
    * Valor de ADCON1 = 14 (Canal AN0 analógico, el resto digitales)
    */

    OpenADC(ADC_FOSC_64 &
    ADC_RIGHT_JUST &
    ADC_16_TAD,
    ADC_CH10 & //ADC_CH0 &
    ADC_INT_OFF &
    ADC_REF_VDD_VSS & // ADC_VREFPLUS_VDD &
    ADC_VREFMINUS_VSS,
    14);
 
    //Retardo de 50 Tcy
    Delay10TCYx(5);
     
    while(1)
    {
    //Iniciar la conversión
    ConvertADC();

    //Espera para que se complete la conversión
    while(BusyADC());

    //Capturando el resultado
    analin = ReadADC();

    /*Como el resultado es de 10 bits  y sólo se dispone de un puerto de 8 bits
    * para mostrarlo. El resultado se convierte en su equivalente de 8 bits dividiendo
    * por cuatro.
    */
    //resultado = resultado / 4;
    ////Mostrando el resultado
    //PORTD = resultado;
  
    valor = 3.3 * (analin*9.7751710654e-4);
    //ftoa(test, &buf, 10, 8);
    ftoa(valor,&buf,10,7);
    
    printf("Volt: %s\n", buf);
    printf("raw: %u\n\n", analin);
    
    Delay10KTCYx(130);
    }
}