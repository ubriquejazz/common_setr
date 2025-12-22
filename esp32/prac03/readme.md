# Prac03

In lesson 3 we will learn several techniques for synchronizing the tasks so that they run in a  controlled order. There are several reasons this is important.

- It is often necessary to control the access to shared resources such as  print services so that the task outputs don’t overlap each other.
- Some tasks need to be triggered by interrupts or timers reacting to outside events.

To this end, we will look at four very common methods that are used to  control the processing sequence in real-time operating systems.

- interupts and timer events
- semaphores, mutexes and queues