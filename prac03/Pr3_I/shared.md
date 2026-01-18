# 3A: Shared resources

## Ejercicio 1 (y 2)

Al suspender el planificador, no existe la posibilidad de que se cambie de contexto en medio de la comprobación de la bandera. Si ocurre, flag==0 y se enciende el led azul.

## Ejercicio 3

En [common_esp32](https://github.com/ubriquejazz/common_eps32) se emplea una misma función para dos tareas distintas (en la creación del thread se pasa los distintos delays).

Poner un delay bloqueante dentro de helper() no es buena idea. ChatGPT propone una técnica basada en una variable llamada **action_needed** que proporciona una respuesta ágil.

**Access:** The lines `if (Flag == 1) { Flag = 0; } else { action_needed = 1; }` are executed safely and atomically relative to other tasks.

## Ejercicio 4 (y 5)

Un semáforo puede mejorar el rendimiento pero no deja de haber un delay bloqueante.

Using a Mutex is the correct synchronization primitive for protecting the shared global variable `Flag` from being simultaneously accessed or modified by multiple concurrent tasks.

However, the key takeaway remains the same: You must not include the blocking delay while the Mutex is held.