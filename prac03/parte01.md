## Ejercicio 3

    HAL_GPIO_WritePin(GPIOD, PIN_XXX, GPIO_PIN_SET);
    helper_ex02(PIN_BLUE);
    osDelay(miDelay);
    HAL_GPIO_WritePin(GPIOD, PIN_XXX, GPIO_PIN_RESET);
    osDelay(miDelay);
    
## Ejercicio 1

### Tarea LED verde (período de ejecución: 1s) 

    Encender el LED verde
    
    // Acceso a la zona de memoria compartida 
    Comprobar el estado de la bandera:
    Si es Up, ponerla en Down, simular la lectura y escritura en el recurso compartido durante 500ms y subir la bandera. Si es Down encender el LED azul. 

    Apagar el LED verde

### Tarea LED rojo (período de ejecución: 1s) 

    Encender el LED rojo

    // Acceso a la zona de memoria compartida.
    Comprobar el estado de la bandera:
    Si es Up, ponerla en Down, simular la lectura y escritura en el recurso compartido durante 500ms y subir la bandera. Si es Down encender el LED azul. 
    
    Apagar el LED rojo

- Modifique la periodicidad de la tarea y compruebe los efectos que tiene esta variación en la aparición del primer conflicto (700 ms)

### Suspension planificador

    void helper_ej1()
        taskENTER_CRITICAL(); 
        Comprobación de la bandera, etc. 
        taskEXIT_CRITICAL();

Compruebe el funcionamiento del sistema. ¿Se enciende el LED azul en algún momento? ¿Cuáles son los efectos negativos de esta técnica?
