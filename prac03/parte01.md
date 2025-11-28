## Ejercicio 3

    HAL_GPIO_WritePin(GPIOD, PIN_XXX, GPIO_PIN_SET);
    helper_ex02(PIN_BLUE);
    osDelay(miDelay);
    HAL_GPIO_WritePin(GPIOD, PIN_XXX, GPIO_PIN_RESET);
    osDelay(miDelay);

**helper_ex02(BLUE)**

- Ponerla en *Down* si el Flag está libre o encender el LED azul en caso contrario. 
- Simular la lectura y escritura en el recurso compartido durante 1s. 
- Apagar el LED azul. Subir la bandera (1)



b) Ejecute las tres tareas sin implementar ningún método de exclusión mutua, fijando en ***Normal***

la prioridad de las tareas 1 y 2, y ***Above*** ***Normal*** la prioridad de la tarea 3.

c) Ejecute las tres tareas implementando la suspensión del planificador

d) Compare el funcionamiento global del sistema en los tres casos y extraiga las conclusiones oportunas.



## Ejercicio 1

### Tarea LED verde (período: 1s) 

    Encender el LED verde
    
    // Acceso a la zona de memoria compartida 
    Comprobar el estado de la bandera: si es Up, ponerla en Down, simular la lectura y escritura en el recurso compartido durante 500ms y subir la bandera. 
    Si es Down encender el LED azul. 
    
    Apagar el LED verde

### Tarea LED rojo (período: 700 ms) 

    Encender el LED rojo
    ...
    Apagar el LED rojo

- Modifique la periodicidad de la tarea y compruebe los efectos que tiene esta variación en la aparición del primer conflicto (700 ms)

### Suspension planificador

    void helper_ej01()
        taskENTER_CRITICAL(); 
        Comprobación de la bandera, etc. 
        taskEXIT_CRITICAL();

Compruebe el funcionamiento del sistema. ¿Se enciende el LED azul en algún momento? ¿Cuáles son los efectos negativos de esta técnica?
