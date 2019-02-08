program space/logical space is divided into pages
ram/physical space is divided into frames

page size = frame size

***pages are loaded in frame 

total m bits
|--------|----|
|  p     | d  |
|--------|----|
 p = page number, m-n bits
 d = page displacement, n bits

*why page size is a power of 2?

ans: displacement is of n bits, then 2^n possible combination, so page size is always a power of two, and as frame size = page size, it is also a power of 2


from the pagetable, the pth entry will carry  corresponding frame number.
then frame num is concatenated with displacement and the physical memory will be acquired 




required files: mmu.h, vm.c, exec.c, trap.c, proc.c

Main --> kaj
1. prothom e notun jei jei jaygay process crate hocche shei shei jaygay swappagefile khulte hobe

2. allocuvm() ekta important function jeta user program ke page allocate kore. eikhane tomake check korte hobe tuimi jei process e kaj korcho shetate ki 15 tar beshi page allocate kora hoise kina

3. jodi hoye thake then ekta array based / linked list based queue implement koro jekhane fifo banabo

4. dhoro max_sync_page =4  e 1 2 3 4 ta page ase. ekhon notun page 5 ashle 1 remove hobe queue theke 1 write hobe swap file e , ar queue hobe 2 3 4 5

5. ekhon tomar program dui ta part thake ekta hocche page directory arekta hocche page index

6. ekhon program jokhon ager page access korte chaibe tokhon page fault dibe. trap 14 jeta

7. tomar kaj hocche trap 14 e ashle tumi prothom e check korba je page ta swapped kora hoise kina jodi hoye thake then oi ager moto tumi head remove korba
ar tail e page ta insert korba
eitai FIFO


boot order of xv6
xv6 main() --> initcode -> init -> sh
ei shob gula call hoy exec.c er maddhome
