ld $tmp, r0        # r0 = addr of tmp
ld $0, r1          # r1 = 0
st r1, (r0)        # tmp = 0

ld $tos, r2        # r2 = addr of tos
st r1, (r2)        # tos = 0

ld $a, r3          # r3 = addr of a
ld 0(r3), r4       # r4 = a[0]
ld $s, r5          # r5 = addr of s
ld (r2), r6        # r6 = tos
st r4, (r5, r6, 4) # s[tos] = a[0]

inc r1             # r1 = 1
st r1, (r2)        # tos = 1

ld 4(r3), r4       # r4 = a[1]
ld (r2), r6        # r6 = tos
st r4, (r5, r6, 4) # s[tos] = a[1]

inc r1             # r1 = 2
st r1, (r2)        # tos = 2

ld 8(r3), r4       # r4 = a[2]
ld (r2), r6        # r6 = tos
st r4, (r5, r6, 4) # s[tos] = a[2]

inc r1             # r1 = 3
st r1, (r2)        # tos = 3

dec r1             # r1 = 2
st r1, (r2)        # tos = 2

ld (r2), r6        # r6 = tos
ld (r5, r6, 4), r4 # r4 = s[tos]
st r4, (r0)        # tmp = s[tos]

dec r1             # r1 = 1
st r1, (r2)        # tos = 1

ld (r2), r6        # r6 = tos
ld (r5, r6, 4), r4 # r4 = s[tos]
ld (r0), r7        # r7 = tmp
add r4, r7         # r7 = tmp + s[tos]
st r7, (r0)        # tmp = tmp + s[tos]

dec r1             # r1 = 0
st r1, (r2)        # tos = 0

ld (r2), r6        # r6 = tos
ld (r5, r6, 4), r4 # r4 = s[tos]
ld (r0), r7        # r7 = tmp
add r4, r7         # r7 = tmp + s[tos]
st r7, (r0)        # tmp = tmp + s[tos]
halt      

.pos 0x200
a:  .long 0             # a[0]
    .long 0             # a[1]
    .long 0             # a[2]
s:  .long 0             # s[0]
    .long 0             # s[1]
    .long 0             # s[2]
    .long 0             # s[3]
    .long 0             # s[4]
tos:.long 0             # tos
tmp:.long 0             # tmp