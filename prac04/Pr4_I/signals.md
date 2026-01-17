## Signals 

En CMSISv1 tenemos la instrucción **osSignalSet**(NombreTareaReceptora, 0x1)

## cflag.h

**Blue Task**
La tarea azul será la tarea remitente (Set) mientras que las tareas Verde y Roja serán las tareas receptoras (Wait).

**Tareas receptoras**
Cuando una tarea receptora tiene que hacer un Wait con este mecanismo, lo hace mediante la instrucción **CFlag_Wait**(). La tarea quedará, entones, esperando a que otra tarea haga un **CFlag_Set**().

---

## ToDo

**Red Task - Flag1**

- Parpadeo del LED a HF durante 15s. Set
- Parpadeo del LED a LF durante 10s. Clear
- Parpadeo del LED a HF durante 5s. Fin 

**Green Task - Flag2**

- Parpadeo del LED a HF durante 15s. Set
- Parpadeo del LED a LF durante 10s. Clear
- Parpadeo del LED a HF durante 5s. Fin 