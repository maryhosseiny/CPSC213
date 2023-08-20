
ld $t, r0          # r0 = addr of t
ld $d, r3          # r7 = addr of d
ld (r0), r1        # r1 = t
mov r1, r2         # r2 = t
inc r1             # r0 = t + 1
inca r1            # r0 = t + 4
shl $2, r1         # r0 = t << 2
and r2, r1         # r0 = r2 & t
shr $3, r1         # r0 = t / 8
mov r1, r4         # r4 = t
st r4, (r3)        # d = t
halt


.pos 0x1000
d:    .long 0      # d
.pos 0x2000
t:    .long 9      # t