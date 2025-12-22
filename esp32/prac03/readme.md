# Prac03

In lesson 3 we will learn several techniques for synchronizing the tasks so that they run in order. There are several reasons this is important.

- It is often necessary to control the access to shared resources such as  print services so that the task outputs don’t overlap each other.
- Some tasks need to be triggered by interrupts or timers reacting to outside events.

To this end, we will look at four very common methods that are used to  control the processing sequence in real-time operating systems.

First, we will use a binary semaphore to synchronize the blinking of our three LED lights so that they blink in sequential order.

How does the system know what order to sequence the lights? 

- We have given  the three LED tasks a higher priority (3) than the other tasks, so the scheduler prioritizes them first.

- The cycles of a blink (led on and off) doesn't consume CPU.

Finally, we modify the code for the TaskTally function. It doesn’t make sense to record the number of LEDs lit since it will always be 1 when they light sequentially. Instead we will have the OLED display the color of the  LED currently lit.
