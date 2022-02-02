# Objetivos

Se desea realizar un despertador inteligente, que muestre la fecha y hora, junto con la
temperatura y humedad en un display gráfico. 
El despertador sonará a la hora que sea
configurado en un buzzer activo genérico (en simulación usaremos el del Proteus, pero
tenemos pensado en otra iteración reemplazarlo por un speaker para poder reproducir audios).

Para medir la temperatura y humedad se usará el sensor DHT11 cuya precisión nos parece
aceptable teniendo en cuenta que la aplicación principal es un despertador inteligente (±2°C
para medir temperatura y ±5%RH para medir humedad). 

Para el display gráfico se va a usar en Proteus el Ampire128x64 que tiene un controlador KS0108, 
para el cual encontramos una librería de drivers implementada que dice funcionar en la familia 
cortex M3. Por último, el RTC que guardará información de en qué segundo, minuto, hora, día, 
mes y año estamos, será un DS1307.

El despertador permitirá configurar la fecha y hora, agregar una alarma (tal vez más de una si
llegamos) y, cuando llegue la hora indicada, hacer sonar el buzzer hasta que se presione algún
botón con el que la alarma se detendrá.

Respecto a cómo el usuario interactúa con el sistema hemos pensado agregar 5 o 6 botones
(arriba, abajo, izquierda, derecha, ok, cancelar) y hacer un menú amigable con el mismo,
tomando inspiración de los smartwatches de hoy en día.