ld $i, r0           # r0 = addr of i
ld (r0), r1         # r1 = i
ld $e, r2           # r2 = e[0]
ld (r2, r1, 4), r3  # r3 = e[i]
mov r3, r5          # r5 = r3
ld $7, r4           # r4 = 7
ld (r0), r1         # r1 = i
add r4, r1          # r1 = i + 7
ld (r2, r1, 4), r4  # r4 = e[i + 7]
add r5, r4          # r4 = e[i + 7] + e[i]
ld $o, r6           # r6 = addr of o
st r4, (r6)         # o = e[i + 7] + e[i]
ld $y, r0           # r0 = addr of y
ld $0xf, r7         # r7 = 0xf
ld (r6), r6         # r6 = o
and r7, r6          # r6 = o & 0xf
st r6, (r0)         # y = o & 0xf
halt

.pos 0x1000
i:     .long 0     # i
.pos 0x1100
y:     .long 0     # y
.pos 0x1500
o:     .long 0     # o
.pos 0x2000
e:
      .long 4      # e[0]
      .long 0      # e[1]
      .long 0      # e[2]
      .long 0      # e[3]
      .long 0      # e[4]
      .long 0      # e[5]
      .long 0      # e[6]
      .long 3      # e[7]
      .long 0      # e[8]
      .long 0      # e[9]