# Ejercicio 1

- Se pide diseñar, escribir y probar dos tareas que lleven a cabo

- una vez encendido el LED azul, este no se apaga nunca. El ejercicio nos da una idea de lo que tarda en producirse el primer conflicto una vez lanzadas las tareas

- Modifique la periodicidad de la tarea 2, y compruebe los efectos que tiene esta variación en la aparición del primer conflicto.

## Tarea: Parpadeo del LED verde (período de ejecución: 1s) 

    Encender el LED verde
    
    // Acceso a la zona de memoria compartida 
    Comprobar el estado de la bandera:
    Si es Up, ponerla en Down, simular la lectura y escritura en el recurso compartido durante 500ms y subir la bandera. Si es Down encender el LED azul. 

    Apagar el LED verde

## Tarea: Parpadeo del LED rojo (período de ejecución: 1s) 

    Encender el LED rojo

    // Acceso a la zona de memoria compartida.
    Comprobar el estado de la bandera:
    Si es Up, ponerla en Down, simular la lectura y escritura en el recurso compartido durante 500ms y subir la bandera. Si es Down encender el LED azul. 
    
    Apagar el LED rojo

## Suspension planificador

    taskENTER_CRITICAL(); 
    Comprobación de la bandera, etc. 
    taskEXIT_CRITICAL();

Compruebe el funcionamiento del sistema. ¿Se enciende el LED azul en algún momento? ¿Cuáles son los efectos negativos de esta técnica?
