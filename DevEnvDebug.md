# Debugage des programmes #

Le debuggage se fait à l'aide de GDB (site officiel : http://www.gnu.org/software/gdb/gdb.html).

L'installation de GDB avec la carte APF9328 http://www.armadeus.com/wiki/index.php?title=GDB

Voici les commandes principales de GDB extraite de la 'man page'.

```
break [file:]function
    Set a breakpoint at function (in file).
run [arglist]
    Start your program (with arglist, if specified).
bt
    Backtrace: display the program stack.
print expr
    Display the value of an expression.
c
    Continue running your program (after stopping, e.g. at a breakpoint).
next
    Execute next program line (after stopping); step over any function calls in the line.
edit [file:]function
    look at the program line where it is presently stopped.
list [file:]function
    type the next of the program in the vicinity of where it is presently stopped.
step
    Execute next program line (after stopping); step into any function calls in the line.
help [name]
    Show information about GDB command name, or general information about using GDB.
quit
    Exit from GDB.
```

En général, les 'must' sont :
  * run
  * bt
  * quit