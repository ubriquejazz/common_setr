# Inversion de Prioridades

- ParpGreen = 2s (zona compartida) + 4s 
- ParpRed = 2s (zona compartida) + 4s 
- ParpOrange = 4s 

## Prioridades

    Red     HighPrior 
    Orange  Medium 
    Green   Low Prior 

## Comments

Unfortunately the use of semaphores prevent the Red task to run, effect of priority inversion.

In a priority-based system, high-priority tasks are supposed to run before low-priority tasks. However, if a low-priority task holds a resource (semaphore) needed by a high-priority task, and a medium-priority task then runs and  prevents the low-priority task from finishing, the high-priority  task can be starved of the resource.

---

Priority inheritance temporarily raises the priority of the low-priority task to the priority of the high-priority task that is waiting for it. 

With a mutex the red task is running again.