# Parte 2

## Pseudocodigo

Los retardos (DelayTimeMsec) serán:

- 200ms para la tarea 1.
- 550ms para la tarea 2.

for(;;)

    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_XX, GPIO_PIN_SET); 
    // Acceso recurso 
    OsDelay(DelayTimeMsec); 
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_XX, GPIO_PIN_RESET); 
    OsDelay(DelayTimeMsec);

Para el acceso a la zona compartida, el seudocódigo sería:

    Comprobar el estado de la bandera.
    Ponerla en Down si está libre o encender el LED azul en caso contrario. Simular la lectura y escritura en el recurso compartido durante 1s. Apagar el LED azul.
    Subir la bandera.

Finalmente, el código para la tercera tarea que haga parpadear el LED naranja será mucho más sencillo:

    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
    OsDelay(50);

## Ejercicio 3 - Suspension planificador

a) Pruebe, en primer lugar, cada una de las tareas independientemente.

b) Ejecute las tres tareas sin implementar ningún método de exclusión mutua, fijando en Normal la prioridad de las tareas 1 y 2, y Above Normal la prioridad de la tarea 3.

c) Ejecute las tres tareas implementando la suspensión del planificador como método de exclusión mutua, tal y como se hizo en el ejercicio anterior.

d) Compare el funcionamiento global del sistema en los tres casos y extraiga las conclusiones oportunas.

## Ejercicio 4 - Semaforos

a) Modifique el código del ejercicio anterior creando un semáforo binario y sustituyendo las instrucciones que deshabilitan y habilitan el planificador por las que utilizan el semáforo.

b) Pruebe el funcionamiento del semáforo fijando el parámetro WaitTimeMilliseconds a 0.

c) Estudie el funcionamiento del sistema en ambos casos y compárelo con el funcionamiento de ejercicio anterior. El uso de un semáforo como método de exclusión mutua, ¿mejora el rendimiento del sistema?

## Ejercicio 5 - Mutex

a) Modifique el código del ejercicio 5a) creando un Mutex y utilizándolo como método de exclusión mutua sustituyendo las instrucciones que correspondan.

b) ¿Observa alguna diferencia significativa en el rendimiento del sistema?

c) Diseñe un experimento, sobre los ejercicios 4 y 5, que permita comprobar las ventajas del uso e un Mutex frente a un semáforo.
