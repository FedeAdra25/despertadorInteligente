o famoso Readme!

/* Lo mismo que lo del DHT22.
El display esta explicado en el codigo. Hice una libreria bonita

Unico problema: Es lento. El simulador es lento. L E N T O
mucho
duele
Hay que poner delays de 5 segundos solo para leer lo que escribe antes de que crashee
cuando tiene que hacer las 500+ iteraciones del display. 
(Las hace, se cuelga, vuelve y el delay).
TRISTEZA
*/

Abri TestingCubeMX_LED/TestingCubeMX_LED.ioc

Esto sirve para seleccionar que pines usar, poner la USART con el BAUD que quieras,
etc etc.
La configure para PA13/PC13 Salidas para LED.
PA9/PA10 USART1
PB15 DHT22

anda a Project Manager,
asegurate que Toolchain/IDE sea MKD-ARM V5.32 (como minimo)

Arriba a la derecha dice "Generate code". Apreta ahi

IMPORTANTE
Esto te va a abrir el Keil si apretas Open Project.
La cuestion es que, dentro del Keil escribas codigo donde esta marcado con un comentario.

/* USER CODE BEGIN XXXXXXXXX */
Codigo bonito
/* USER CODE END XXXXXXXXXX */

Si lo escribis afuera, y luego usas el STM32CubeMX para volver a setear algun Puerto o Pin nuevo,
o agregas USART2, o etc, todo codigo fuera de ese comentario se borra porque se asume autogenerado.
Entonces... Se genera denuevo. Cuidado!

Bueno del Keil abris, modificas lo que quieras y te vas a "Build"
En \MDK-ARM\TestingCubeMX_LED\ te va a generar el .hex 
pero mas importante y bonito te va a generar un .axf
Hacele una copia, y cambiale la extension a .elf

De ahi abri el proyecto de Proteus "LED + DHT11 with CubeMX.pdsprj"
Doble click al STM, y pega el path al archivo .elf que tenes ahora.

Joya, ahora ya podes ver al DHT22 funcionar mal! 