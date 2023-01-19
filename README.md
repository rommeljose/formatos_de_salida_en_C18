# Formatos de Salida de datos en el Compilador C18 de Microchip


 por: Rommel Contreras - _rommeljose@gmail.com_

> Esta rutina en C, permite la exploración y uso de la librería usart.h del compilador C18 (MPLAB® C18); de uso general para la familia de
> microcontroladores PIC18xxx.
> 
> Esto requiere del uso y configuración de un Puerto Serial, basada en un módulo UART del Pic utilizado.
> Ejemplo de uso de la librería "usart.h".
> modo nativo; con el Pic **18F4620**
> programa: Usar_C18_Native
>> **ver:** [MPLAB_C18_Libraries_51297e.pdf](MPLAB_C18_Libraries_51297e.pdf)

>> El propósito de esta práctica es ilustrar el uso de la función de biblioteca C estándar printf(); y semejantes . Dado que su propósito original era imprimir texto en el dispositivo de salida estándar de una computadora (pantalla de monitor o impresora). El programa se desarrollo como plataforma para paracticar las utilidades de impresión o salida al puerto serial.

Uso del printf ---> ![Esuema General](./otros/uso_printf.png)

## Funciones que tienen salida por el puerto serial:

`fprintf`	Salida de cadena formateada a un stream o archivo.

`fputs` Salida de cadena a un stream o archivo.

`printf` Salida de cadena formateada al stdout.

`putc` Salida de carácter a un stream.

`puts` Secuencia de salida de cadena al stdout.

`sprintf` Salida de cadena formateada a un buffer de la memoria de datos.

`vfprintf` Salida de cadena formateada a un stream con los argumentis para procesar la cadena de formato  proporcionada a través de la función stdarg.

`vprintf` Salida de cadena formateada al stdout con los argumentis para procesar la cadena de formato  proporcionada a través de la función stdarg.

`vsprintf` Salida de cadena formateada a un buffer de la memoria de datos con los argumentis para procesar la cadena de formato  proporcionada a través de la función stdarg.

`_usart_putc` Salida de un solo carácter al USART (USART1 para los dispositivos que tienen más de un USART).

`_user_putc` Salida de un solo carácter de una manera definida por la aplicación.

Ejemplos printf ---> ![Ejemplos printf](./otros/ejemplos_prrintf.png)

> La  cadena  de  formato  se  procesa  un  carácter  a  la  vez  y  los  caracteres  se  emiten  tal  como  aparecen  en  la  cadena  de  formato;  a  excepción  de  los  especificadores  de  formato.  Un  especificador  de  formato  se  indica  en  la  cadena  de  formato  mediante  un  signo  de  porcentaje  (%);  a  continuación,  un  especificador  de  formato  bien  formado  tiene  los  siguientes  componentes. Excepto  por  la  operación  de  conversión,  todos  los  especificadores  de  formato  son  opcionales: 

1.	Caracteres  de  bandera  (el  orden  no  importa),  donde  un  carácter  de  bandera  es  uno  de:  #,  -,  + ,  0  o  espacio.
2.	Un ancho de campo, que es un valor constante entero decima o un asterisco (*).
3.	Una precisión de campo, que es un punto (.); opcionalmente seguido de un entero, decimal o un asterisco (*).
4.	Una especificación de tamaño, que es uno de los especificadores: h, H, hh, j, z, Z, t, T o l.
5.	Una  operación  de  conversión,  que  se expresa por uno de los siguientes caráteres: c,  b,  B,  d,  i,  n,  o,  p,  P,  s,  S,  u,  x,  X  o  %.

## Especificadores de formatos:

`%c`	Single character

`%s`	String (all characters until '\0')

`%d`	Signed decimal integer

`%o`	Unsigned octal integer

`%u`	Unsigned decimal integer

`%x`	Unsigned hexadecimal integer with lower case digits (e.g. 1a5e)

`%X`	Same as %x but with upper case digits (e.g. 1A5E)

`%f`	Signed decimal value (floating point); (esta especificación no aplica correctamente para C18)

`%e`	Signed decimal value with exponent (e.g. 1.26e-5)

`%E`	Same as %e but uses upper case E for exponent (e.g. 1.26E-5)

`%g`	Same as %e or %f, depending on size and precision of value

`%G`	Same as %g but will use capital E for exponent

### Carácteres Banderas:
- `#` Presentará la forma alternativa del resultado. Para la conversión de 0, la forma alternativa es como si se aumentara la precisión de tal manera que el primer dígito del resultado se ve obligado a ser cero. Para la conversión con x, un resultado distinto a cero tendrá un prefijo 0x agregado. Para la conversión con X, un resultado distinto de cero trendrá un prefijo 0X agregado. Para la conversión con b, un resultado distinto de cero tendrá un prefijo 0b agregado. Para la conversión B, un resultado distinto de cero tendrá un prefijo 0B agregado. Para otras conversiones, la bandera se ignora.
- `-` El resultado se justificará a la izquierda. Si no se especifica esta bandera, el resultado estará justificado a la derecha.
- `+` Para una conversión con signo, el resultado siempre comenzará con un signo + o -. De forma predeterminada, solo se agrega un carácter de signo al resultado si el resultado es negativo. Para otras conversiones, la bandera se ignora.
- `espacio` Para una conversión firmada, si el resultado no es negativo o no tiene caracteres, se antepondrá un espacio al resultado. Si se especifican los indicadores de espacio y +, se ignorará el indicador de espacio. Para ptras conversiones, la bandera se ignora.
- `0` Para las conversiones (d, i, o, u, b, B, x, X), los ceros iniciales se anteponen al resultado (después de cualquier signo y/o indicador de base) de modo que el resultado llene el ancho de campo. No se realiza relleno de espacio. Si también se especifica el indicador -, se ignorará el indicador 0. Si se especifica una precisión, se ignorará el indicador 0. Para otras conversione, la bandera se ignora.

### Precisión de campo
La precisión de campo especifica el número mínimo de dígitos que estarán presentes en el valor convertido para la conversión a d, i, o, u, b, B, x o X, o el número máximo de caracteres en el valor convertido para una s conversión.
Si el ancho del campo es un carácter de asterisco, *, se lee un argumento int para especificar el ancho del campo. Si el valor es negativo, es como si la precisión no estuviera especificada.
Para los operadores de conversión d, i, o, u, b, B, x o X, la precisión predeterminada es 1. Para todos los demás operadores de conversión, el comportamiento cuando no se especifica la precisión se describe a continuación.

### Especificaciones de tamaño
El carácter de especificación de tamaño se aplica a los especificadores de conversión de enteros, d, i, o, u, b, B, x o X, y el apuntador de conversión especificado, p y P. Si se presenta cualquier otro operador de conversión, este es ignorado.
- `hh` Para los especificadores de conversión de enteros, el argumento a convertir es un argumento char con signo o un char sin signo. Para un especificador de conversión n, el especificador denota un puntero a un argumento char con signo.
- `h` Para los especificadores de conversión de enteros, el argumento a convertir es un int corto o un int corto sin signo. Para un especificador de conversión n, el especificador denota un puntero a un argumento int corto. Como un int simple tiene el mismo tamaño que un int corto para MPLAB C18, esta opción no tiene ningún efecto real y está presente solo por motivos de compatibilidad. Para los especificadores de conversión de puntero, el argumento a convertir es un puntero de 16 bits.
- `H` Para los especificadores de conversión de enteros, el argumento a convertir es un int largo corto o un int largo corto sin signo. Para un especificador de versión n conversor, el especificador denota un puntero a un argumento int corto y largo. Para los especificadores de conversión de puntero, el argumento a convertir es un puntero de 24 bits. Por ejemplo, cuando se genera un far rom char *, se debe usar el especificador de tamaño H (%HS).
- `j` Para los especificadores de conversión de enteros, el argumento a convertir es un argumento intmax_t o uintmax_t. Para un especificador de conversión n, el especificador denota un puntero a un argumento intmax_t. Para MPLAB C18, esto es equivalente al especificador de tamaño l.
- `l` Para los especificadores de conversión de enteros, el argumento que se va a convertir es un entero largo o un entero largo sin signo. Para un especificador de conversión n, el especificador denota un puntero a un argumento int largo. Para los especificadores de conversión de puntero, se ignora el especificador de tamaño.
- `t` Para los especificadores de conversión de enteros, el argumento a convertir es un argumento ptrdiff_t. Para un especificador de conversión n, el especificador denota un puntero a un tipo de entero con signo correspondiente al argumento ptrdiff_t. Para MPLAB C18, esto es equivalente al especificador de tamaño h.
- `T` Para los especificadores de conversión de enteros, el argumento a convertir es un argumento ptrdiffrom_t. Para un especificador de conversión n, el especificador denota un puntero a un tipo de entero con signo correspondiente al argumento ptrdiffrom_t. Para MPLAB C18, esto es equivalente al especificador de tamaño H.
- `z` Para los especificadores de conversión de enteros, el argumento a convertir es un argumento size_t. Para un especificador de conversión n, el especificador denota un puntero a un tipo de entero con signo correspondiente al argumento size_t. Para MPLAB C18, esto es equivalente al especificador de tamaño h.
- `Z` Para los especificadores de conversión de enteros, el argumento a convertir es un argumento sizerom_t. Para un especificador de conversión n, el especificador
denota un puntero a un tipo de entero con signo correspondiente al argumento sizerom_t. Para MPLAB C18, esto es equivalente al especificador de tamaño H.
- `c` El argumento int se convierte en un valor de carácter sin signo y se escribe el carácter representado por ese valor.
- `d`, `i` El argumento int se formatea como decimal con signo con la precisión que indica el número mínimo de dígitos que se escribirán. Si el valor convertido tiene menos dígitos, se le anteponen ceros. Si el valor convertido es cero y la precisión es cero, no se escribirán caracteres.
- `o` El argumento int sin signo se convierte a octal sin signo con la precisión que indica el número mínimo de dígitos que se escribirán. Si el valor convertido tiene menos dígitos, se le anteponen ceros a la izquierda. Si el valor convertido es cero y la precisión es cero, no se escribirán caracteres. 
- `u` El argumento int sin signo se formatea como decimal sin signo con la precisión que indica el número mínimo de dígitos que se escribirán. Si el valor convertido tiene menos dígitos, se le anteponen ceros. Si el valor convertido es cero y la precisión es cero, no se escribirán caracteres. 
- `b` El argumento int sin signo se formatea como binario sin signo con la precisión que indica el número mínimo de dígitos que se escribirán. Si el valor convertido tiene menos dígitos, se le anteponen ceros. Si el valor convertido es cero y la precisión es cero, no se escribirán caracteres. 
- `B` El argumento int sin signo se formatea como binario sin signo con la precisión que indica el número mínimo de dígitos que se escribirán. Si el valor convertido tiene menos dígitos, se le anteponen ceros. Si el valor convertido es cero y la precisión es cero, no se escribirán caracteres. 
- `x` El argumento int sin signo se formatea como hexadecimal sin signo con la precisión que indica el número mínimo de dígitos que se escribirán. Los caracteres abcdef se utilizan para la representación de los números decimales del 10 al 15. Si el valor convertido tiene menos dígitos, se le anteponen ceros. Si el valor convertido es cero y la precisión es cero, no se escribirán caracteres.
- `X` El argumento int sin signo se formatea como hexadecimal sin signo con la precisión que indica el número mínimo de dígitos que se escribirán. Los caracteres ABCDEF se utilizan para la representación de los números decimales del 10 al 15. Si el valor convertido tiene menos dígitos, se le anteponen ceros. Si el valor convertido es cero y la precisión es cero, no se escribirán caracteres. 
- `s` Los caracteres de la matriz de memoria de datos del argumento char se escriben hasta
que se ve un carácter de terminación '\0' (el carácter '\0' no se escribe) o el número de caracteres escritos es igual a la precisión especificada. Si se especifica que la precisión es mayor que el tamaño de la matriz o no se especifica, la matriz debe contener un carácter de terminación '\0'.
- `S` Los caracteres de la matriz de la memoria del programa del argumento char se escriben hasta que se ve un carácter de terminación'\0'; (el carácter '\0'; no se escribe) o el número de caracteres escritos es igual a la precisión especificada. Si se especifica que la precisión es mayor que el tamaño de la matriz o no se especifica, la matriz debe contener un carácter de terminación '\0'. Cuando la salida proviene de un far rom char \*, se debe de utilizar la H como especificador de tamaño.
- `p` El puntero al argumento void (datos o memoria de programa) está configurado se convierte a un tipo de entero sin signo de tamaño equivalente y ese valor se procesa como si se hubiera especificado el operador de conversión x. Si el especificador de tamaño H está presente, el puntero es un puntero de 24 bits; de lo contrario, es un puntero de 16 bits. 
- `P` El puntero al argumento void (datos o memoria de programa) está configurado se convierte a un tipo de entero sin signo de tamaño equivalente y ese valor se
procesa como si se hubiera especificado el operador de conversión X. Si el especificador de tamaño H está presente, el puntero es un puntero de 24 bits; de lo
contrario, es un puntero de 16 bits.
- `n` El número de caracteres escritos hasta el momento se almacenará en la ubicación a la que hace referencia el argumento, que es un puntero a un tipo entero en la memoria de datos. El tamaño del tipo entero está determinado por el especificador de tamaño presente para la conversión, o un entero simple de 16 bits si no hay ningún especificador de tamaño presente.
- `%` Se escribe un carácter % literal. La especificación de conversión será %% solamente, no pueden estar presentes banderas u otros especificadores. Si un especificador de conversión no es válido (p. ej., un carácter indicador está presente para el especificador de conversión %%), el comportamiento no está definido. fprintf devuelve EOF si se produce un error; de lo contrario, devuelve el número de caracteres de salida.

[**Nota 1:**](https://www.puntoflotante.net/CONVERTIR-DE-PUNTO-FLOTANTE-A-STRING-EN-C18.pdf) Debido al tamaño extremo de la biblioteca printf, el punto flotante (tipo %f %g y %h) no es compatible para evitar que la biblioteca crezca. El costo en el espacio de la memoria del programa para agregar soporte de punto flotante es bastante extremo (requeriría que la biblioteca tuviera aproximadamente el doble de su tamaño actual), por lo que se eligió eliminar el soporte de printf de punto flotante para mantener el tamaño del código lo más pequeño posible y un tamaño razonable para la mayoría de las aplicaciones. Esto puede causar problemas a los usuarios que deseen mostrar números de coma flotante. Sin embargo, no es difícil convertir un número en un punto fijo para su visualización.

>> **ver tambien:** [The printf() Function](https://microchipdeveloper.com/tls2101:printf) y [MPLAB_C18_Libraries_51297e.pdf](https://github.com/rommeljose/MPLAB-C18/blob/fe1733e71892ce45d670f2f1202f8a638bfe136e/MPLAB_C18_Libraries_51297e.pdf)
