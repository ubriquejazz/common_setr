# Comunicacion entre tareas II

## Ejercicio II_1

Como en el ejercicio de la práctica anterior, se pretende establecer una sincronización unilateral.

![alt text](fig/ej01.png "sincronización unilateral")

a) Implemente el sistema descrito creando dos semáforos (Azul2Verde, Azul2Rojo) para la sincronización.
b) Utilice las instrucciones ya conocidas para actuar sobre los semáforos
c) Inicialice los semáforos bloqueados para poder implementar la sincronización deseada.
d) ¿Podría utilizarse un mutex?

## Ejercicio II_2

![alt text](fig/ej02.png "sincronización bilateral")

## Ejercicio II_3

![alt text](fig/ej03.png "sincronización bilateral")

**Crear un archivo pool.c**

La definición de la estructura de datos.
La creación del semáforo (handle y semáforo) 
Las funciones de acceso que sean necesarias

**Tarea de control de la velocidad**

Cambio de la consigna de frecuencia de parpadeo del LED verde a 1Hz 
Cambio de la consigna de frecuencia de parpadeo del LED rojo a 10Hz 
Delay de 8 s.

Cambio de la consigna de frecuencia de parpadeo del LED verde a 10Hz 
Cambio de la consigna de frecuencia de parpadeo del LED rojo a 1Hz 
Delay. Volver al principio

**Tarea del LED verde (10s)**

Comprobar la frecuencia del pool
Mostrar por consola y ajustar parpadeo del LED

**Tarea del LED rojo (6s)**

Comprobar y ajustar la frecuencia de parpadeo del LED (idem)