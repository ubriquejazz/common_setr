# Prac02 - Results

The OLED  display will show the number of LEDs lit at any given time.
Now open the serial monitor and reboot the board. After 5 seconds you should see the high watermark listings similar to that  shown below.

![img](https://miro.medium.com/v2/resize:fit:1006/1*ExOVWrj_XFc8yO5NJd4fvA.jpeg)

This is indicating how much free memory is available in each of the tasks.  

Since the code in these tasks doesn’t increase in memory requirements over time, you should be able to reduce the memory allocation in the *xTaskCreate* statements in the code. What happens if your initial guess at the  memory allocation is too low and a task runs out of memory?