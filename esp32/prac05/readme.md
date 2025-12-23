# Prac05

Now we are ready to add the command processor. We’re going to add this in two parts.

- Command Parser to read the keyboard entry and validate that is a correct command.
- Command Executor to take the validated input entry and perform the requested command.

We will use a queue to pass the validated command from the command parser to the command executor. Why separate the two tasks? 

In the future we  may want to add the ability to enter commands from a web interface, or through some other input method. We  would simply have the new input device send commands to the same command queue as the command parser and avoid writing additional processing  code. 

##

