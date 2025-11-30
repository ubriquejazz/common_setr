# Comunicacion entre tareas I

## Ejercicio I_1

Las banderas de condición se utilizarán para coordinar la tarea que hace parpadear el LED azul con las otras dos.

![alt text](fig/ej01.png "bandera condicion")

**Tarea Parpadeo del LED azul.**

- Parpadeo del LED, inicialmente, a 10 Hz.
- Si las dos banderas están en SET, pasar a parpadea a 1Hz. Si las dos banderas están en RESET, pasar a parpadea a 10Hz.

**Tarea Parpadeo del LED rojo/verde** 

- Parpadeo del LED a 10Hz durante 15s. Set de la bandera 2.
- Parpadeo del LED a 1Hz durante 10s. Clear de la bandera 2.
- Parpadeo del LED a 10Hz durante 5s. Fin de la tarea.

a) Dibuje un cronograma en el que se muestre la secuencia de eventos que se produce en el mismo.

b) Complete la definición de la bandera para convertirla en un objeto encapsulado (condition.h)

## Ejercicio I_2 (signal)

La tarea Azul será la tarea remitente mientras que las tareas Verde y Roja serán las tareas receptoras.

![alt text](fig/ej02.png "sincronización unilateral")