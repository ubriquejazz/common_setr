# Simulacion de Inversión de Prioridades 

## Prioridades

    Red     HighPrior 
    Orange  Medium 
    Green   Low Prior 

## Tareas

    ParpGreen = 2s (zona compartida) + 4s 
    ParpRed = 2s (zona compartida) + 4s 
    ParpOrange = 4s 

## Ejercicio 01

Execute only the tasks that make the green and red LEDs blink. Modify the task that controls
the flashing of the red LED to start its execution, before simulating the access to the shared
resource, suspending for 1s. Make use of the osDelay(1000) instruction. Execute the code and
restart the processor several times until you have correctly observed and understood the
sequence of flashes that occurs. This sequence will be like the one shown in Figure 2.

Going back to the three tasks, modify the code of the tasks that control the flashing of the red
LED and the orange LED so that they start their execution by suspending for 1s. In this way, it
will be the task controlling the flashing of the green LED, the lowest priority, that will acquire
the semaphore and leave it blocked when it is evicted. Run the code several times by restarting
the processor until you have correctly observed and understood the sequence of flashes that
occurs. Draw the corresponding timeline and explain how the inversion of priorities is reflected in it.

## Ejercicio 02

Repeat exercise 2.c). Execute, again, the code several times by restarting the processor until
you have correctly observed and understood the sequence of blinks that occurs. Draw the
corresponding chronogram and justify that the priority inversion problem has been eliminated.