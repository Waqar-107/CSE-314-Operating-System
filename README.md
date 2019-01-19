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


<b>task-2 : implementing a socket api in xv6</b>
<b>making a patch</b>

1. clone xv6 - keep it as a repo, not merge with others
2. make changes
3. commit changes
4. run "git show HEAD>patch_xv6_Socket_ROLL"
5. a patch file named patch_xv6_Socket_ROLL has been created

<b>unpack a patch</b>
1. git apply patch_file_name
2. make and make qemu

<b>detail of task 2</b>
***apply the patch to have the tester code ready to use

The system calls that should be implemented are as follows:


// Listen to a local port (parameter). Return 0 for success, negative for failure
int listen(int);


// Connect to remote port and host (parameter). Only "localhost" and "127.0.0.1" as host should be supported. Returns the local port number, if connection was successful. Negative value returned indicate failure.
int connect(int, const char* host);


// Send a buffer to remote host. The local port, buffer, size of data are parameters. Return 0 for success. Negative value for failure. Send blocks, if remote host has not yet read earlier data
int send(int, const char*, int);


// Receive data from remote host. The local port, buffer, size of buffer are parameters. Return 0 for success. Negative value for failure. recv blocks, if no data is available.
int recv(int, char*, int);


// Disconnect (and close) the socket. The local port is parameter.
int disconnect(int);


// Implement the following error codes. These should be available for user level programs, as well as in kernal space, as the defined constants.

//define constants that are available to both the user and kernel
#define E_NOTFOUND -1025
#define E_ACCESS_DENIED -1026
#define E_WRONG_STATE -1027
#define E_FAIL -1028
#define E_INVALID_ARG -1029


Error checking:
-------------------
Parameter issues should return E_INVALID_ARG
Accessing a socket that is not in the stable should return E_NOTFOUND
Accessing a socket from wrong process should return E_ACCESS_DENIED
Attempts to send or receive, when the socket is not connected, should return E_WRONG_STATE
If no more socket can be opened (limit exceeded), return E_FAIL

(Optional Task) Close the outstanding sockets owned by a process, when process terminates.
(Optional Task) Modify socktest to demonstrate the above feature

Limitations (Future work):
--------------------------------
- Send will block the caller process, until the recepients buffer is empty.
- Timeout cannot be specified in the recv() call
