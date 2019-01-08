# CSE-314-Operating-System

# offline-1:
on bash
task is inside the doc, there is a zip file that have output and test-case

# online-1:
A1: there are some txt files. a file will be the source that will be given as a argument. for each line of the src, find if it can be found as a part of a line in a file 

B1: there is 3 folders with name of country, inside there are cricket player category and pdfs. inside the categories there can be pdfs and txt files where information of player is given in seperate txt files. the task is, for each country, make a txt file and write all the players info.

B2: some directories are given, inside them there are files (.cpp, .c etc.) and directories. the task is to execute all the cpp files e.g. x.cpp->x.exe

# offline-2
on pthread, semaphore and mutex

# online-2
on pthread, semaphore and mutex

# xv6

emulator for running the .img -> 'sudo apt-get install qemu-system'

<b>task-1:</b> make a system_call and a user_program to test the system_call. the user_program needs to placed in 'make' file to be compiled 

* the name of the function will be waqar_hassan_khan()

* we first define it in 'syscall.h' with a number - there are other system_calls with numbers (1-n), we assign ours with (n+1)

* next we need to add a pointer to the system call in the 'syscall.c' file. this file contains an array of function pointers which uses the above-defined numbers(defines in syscall.h) as pointers to system calls which are defined in a different location. e.g [SYS_funcname] sys_funcname
actually its like assigning in an array.

When the system call with number 22(in our my case, can be different in yours) is called by a user program, the function pointer sys_funcname which has the index SYS_funcname will call the system call function

* next we define the function prototype in 'syscall.c'

* now implement the function in 'sysproc.c'
in 'sysproc.c' the actual codes of sys calls are not implemented, instead it checks parameter validity then call some function of same sort and return the value to the user function.
here we write 
sys_nameOfFunction(){

	//validation code

	return nameOfFunction();

}

nameOfFunction is implemented in 'proc.c'. 

* define the function name in defs.h

* In order for a user program to call the system call, an interface needs to be added. Therefore, we need to edit the 'usys.S' file where we should add the following line.

SYSCALL(funcname)

* now we define it in 'user.h' file 

ret_type funcName(params);

this would be the function which the user program calls. this function will be mapped to the system call with the number 22 which is defined as SYS_funcname preprocessor directive.

*** adding a user program in xv6:

the 'Makefile' needs to be edited, there is a 'UPROGS=' with all the files starting with '_', just add your program name there without any extension. e.g- _progname\ here the '\' indicates that it is a multiline code(multiline string or single line comments are written in multiline like this)

then there is a paragraph named 'EXTRA=' here put your program name with extension e.g- progname.c 
note: there is a '\' after the last name here, write the name before the '\'

then compile with-> 'make clean' -> 'make'
then use 'make qemu'
