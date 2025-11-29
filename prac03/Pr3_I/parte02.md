## Ejercicio 4 - Semaforos

a) Modifique el código del ejercicio anterior creando un semáforo binario y sustituyendo las instrucciones que deshabilitan y habilitan el planificador por las que utilizan el semáforo.

b) Pruebe el funcionamiento del semáforo fijando el parámetro WaitTimeMilliseconds a 0.

c) Estudie el funcionamiento del sistema en ambos casos y compárelo con el funcionamiento de ejercicio anterior. El uso de un semáforo como método de exclusión mutua, ¿mejora el rendimiento del sistema?

___

Using a 0-millisecond timeout is commonly referred to as **polling** or **try-acquire**.

- **Avoid Deadlock:** It guarantees that your task will **never block indefinitely**, which can be useful in time-sensitive control loops or tasks that must not miss a deadline.
- **Alternative to Blocking:** It is the standard way to implement a **try-acquire** or a **non-blocking attempt** to access a resource.

---

El sistema funciona, los tiempos son los siguientes:

- RED = 200 ms, GREEN = 550 ms (misma prioridad)
- ORANGE = 50 ms (alta prioridad)



## Ejercicio 5 - Mutex

a) Modifique el código del ejercicio 5a) creando un Mutex y utilizándolo como método de exclusión mutua sustituyendo las instrucciones que correspondan.

b) ¿Observa alguna diferencia significativa en el rendimiento del sistema?

___

Using a Mutex is the **correct synchronization primitive** for protecting the shared global variable `Flag` from being simultaneously accessed or modified by multiple concurrent tasks.

However, the key takeaway remains the same: **You must not include the blocking delay (`delay_1s()`) while the Mutex is held.**

**Access:** The lines `if (Flag == 1) { Flag = 0; } else { action_needed = 1; }` are executed safely and atomically relative to other tasks.

___

El uso del mutex bloquea el parpade del LED rojo y verde. Esto se debe a que el mutex debe ser liberado por la tarea que lo creo. 
