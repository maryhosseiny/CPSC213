ld $a, r0           # r0 = &a
ld $3, r1           # r1 = 3
ld (r0), r2         # r2 = val of a
st r1, (r2)         # a = 3

ld $p, r3           # r3 = &p
ld (r3), r4         # r4 = p
st r0, (r4)         # p = &a

dec r3              # r3 = *p - 1
#st r3, (r3)         # p* = p* - 1 NOT SURE ABOUT THIS LINE

ld $b, r5           # r5 = &b[0]
st r5, (r4)         # p =  &b[0]

inc r4              # p = 3 (p++)

ld (r5, r2, 4), r1  # r1 = b[a]
ld (r3, r2, 4), r6  # r6 = p[a]
st r1, (r6)         # p[a] = b[a]

ld $3, r1           # r1 = 3
ld 0(r5), r2        # r6 = b[0]
st r2, (r3, r1, 4)  # (p + 3) = b[0]
halt

.pos 0x200
b:  .long 1         # b[0]
    .long 2         # b[1]
    .long 3         # b[2]
    .long 4         # b[3]
    .long 5         # b[4]
a:  .long 2         # a    
p:  .long 2         # *p