# Shell Script Sample Problems

# Problem 1 :

Write a shell script script1.sh  that will prompt the user and receive two integers as input. The output will be "yes" only if one of the numbers is even and the other is odd. Otherwise, output will be "no".

# Problem 2 :

Write a shell script script2.sh  that will take integer numbers from the user until a zero is entered. The inputs can be both positive and negative. However, after a zero is entered, the output will be sum of all the positive numbers (ignoring the negative numbers) entered by the user.

# Problem 3 :

Write a shell script script3.sh that will take filenames as arguments and remove execute permission from the file, however only if the file is a regular file. The script must check to see that there is at least one argument, otherwise shows usage message for the script.

If we give the command  "ls -l"    in the current directory, the output is,
         drwxrwxr-x 4 cse cse 4096 Mar  9 00:19 a
        -rwxrwxr-x 1 cse cse    0 Mar  9 00:37 a.txt
        -rw-rw-r-- 1 cse cse    0 Mar  9 00:37 b.txt
        -rw-rw-r-- 1 cse cse    0 Mar  9 00:37 c.txt
        -rwxr-xr-x 1 cse cse  638 Mar  9 01:36 script3.sh

Now, if we give the following commands in turn, the output will be as follows:

       ./script3.sh

        Usage: script3.sh filename1 filename2 ...
            

     ./script3.sh a.txt sds b.txt a

        a.txt is currently executable.
       -rwxrwxr-x 1 cse cse 0 Mar  9 00:37 a.txt
        a.txt's executable permission is now changing.
        -rw-rw-r-- 1 cse cse 0 Mar  9 00:37 a.txt
         a.txt is currently not executable.
        sds does not exist.
       -rw-rw-r-- 1 cse cse 0 Mar  9 00:37 b.txt
       a is not a regular file.


# Problem 4

Write a shell script  script4.sh that will change the current working directory as shown in the following figure. Remember that, only files having extension .cpp should be renamed. And this should be done for all nested subdirectories also.

In the following figure, the directory tree on the left is before running the script which after running script4.sh will be changed to the one on the right.


# Problem 5:

Write a shell script script5.sh that will take a line number n and a string PATTERN as input and delete all the txt files in the directory which contains the string PATTERN in line n.
For example, consider the following files:

file1.txt
Twinkle twinkle little star
How I wonder what you are
Up above the world so high
Like a diamond in the sky

file2.txt
int i;
for (i=0;i<10;i++)
     printf("%d\n",i);

file3.txt
Dear friend,
I haven't seen you for a long time.
Please let me know where you are.

Now if you run 
       script5.sh 2 "for"
then file2.txt and file3.txt will be deleted as both of them contain "for" in line 2. Similarly, if you run
script5.sh 2  "you"
then file1.txt and file3.txt will be deleted.

# Problem 6:

Write a shell script script6.sh that deletes all the files in the current directory that has at least one digit in its file name.
Remember, you cannot delete any directory even if its name contains digit.

Suppose current directory contains the following files:
abc.txt     myfile_1.txt     program_v1.01     myfile.txt

After running script6.sh  the contents in the directory will be:
abc.txt     myfile.txt

