# Comm. y sicnronizacion entre tareas

## Sincro unilateral

Sistema basado en dos semáforos (Azul2Verde, Azul2Rojo) para la misma sincronización.

En este caso, las instrucciones Set y Wait serán  sustituidas por las operaciones Wait y Release de los semáforos.

## Sincro bilateral

- Permiso para avance de la otra tarea (ack)
- Solicitud de sincro con la otra tarea (request)

## pool.h

No existe sincronizacion, se envian datos al pool periodicamente y otra tarea los recoje.

Dos consignas de frecuencia de parpadeo: FreqGreen y FreqRed
La tarea correspondiente va a comprobar la frecuencia, ajustar parpadeo del LED.

## mailbox

1. **Elemento de Datos:** Una variable `int` para almacenar el valor de la temperatura en décimas de grado Celsius.
2. Un **Mutex** (`Mailbox_Mutex`) para asegurar que solo una tarea (Adquisición o Monitoreo) acceda a la variable de temperatura a la vez.
3. **Sincronización:**
   - **Semáforo 1 (`DataAvailable_Sem`)**: Usado por `T_Adquisicion` para indicar que hay un dato nuevo listo.
   - **Semáforo 2 (`BufferEmpty_Sem`)**: Usado por `T_Monitoreo` para indicar que el dato anterior ha sido leído y el buffer está listo para recibir el siguiente.

#### `T_Adquisicion` llama a `Mailbox_Post`

1. **Espera Buffer Vacío:** Hace `osSemaphoreWait(BufferEmpty_Sem, osWaitForever)`. Esto suspende a la tarea hasta que `T_Monitoreo` lea el dato anterior y libere el semáforo.

2. **Adquiere Mutex:** Hace `osMutexWait(Mailbox_Mutex, osWaitForever)` para obtener acceso exclusivo a la variable de datos.

3. **Escribe Datos:** `mailbox.temperature_data = new_temp;`

4. **Libera Mutex:** Hace `osMutexRelease(Mailbox_Mutex)`.

5. **Señala Datos Listos:** Hace `osSemaphoreRelease(DataAvailable_Sem)`.

#### `T_Monitoreo` llama a `Mailbox_Pend`

1. **Espera Datos Listos:** Hace `osSemaphoreWait(DataAvailable_Sem, osWaitForever)`. Esto suspende a la tarea hasta que `T_Adquisicion` coloque y señale un dato.

2. **Adquiere Mutex:** Hace `osMutexWait(Mailbox_Mutex, osWaitForever)` para obtener acceso exclusivo a la variable de datos.

3. **Lee Datos:** `read_temp = mailbox.temperature_data;`

4. **Libera Mutex:** Hace `osMutexRelease(Mailbox_Mutex)`.

5. **Señala Buffer Vacío:** Hace `osSemaphoreRelease(BufferEmpty_Sem)`.

Este esquema asegura que la comunicación es **segura** (por el Mutex) y **sincronizada** (la Tarea adquisición espera a que la de monitoreo termine, y viceversa, gracias a los dos semáforos).