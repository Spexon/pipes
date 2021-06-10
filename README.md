# pipes

The output for the first part of the homework (pipes) is basically executing the shell command 
ps -aux | sort -r -n -k 5. This program utilizes a pipe ( | in the shell) to combine the ps -aux command (which checks for active processes for all users on your computer) and uses that output for the next command sort -r -n -k 5 (which sorts the previous output, -r = reverse result, -n = numeric sort, -k = sort via a key).

