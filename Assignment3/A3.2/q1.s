ld $l, r0                # r0 = addr of l
ld $9, r1                # r1 = 9
ld $n, r2                # r2 = addr of n
ld (r0, r1, 4), r3       # r3 = l[9]
st r3, (r2)              # n = l[9]
    
ld (r2), r4              # r4 = n
ld (r0, r4, 4), r3       # r3 = l[n]
st r3, (r2)              # n = l[n]
    
ld $w, r2                # r2 = addr of w
ld $d, r3                # r3 = addr of d
st r2, (r3)              # d = &w
    
ld (r3), r4              # r4 = d
ld $8, r5                # r5 = 8
st r5, (r2)              # *d = 8 
    
ld $6, r5                # r5 = 6
ld (r0, r5, 4), r4       # r3 = l[6]
shl $2, r4               # r4 = r4*4
add r0, r4               # r4 = r0 + r4
st r4, (r3)              # d = &l[l[6]]

ld (r3), r4              # r4 = &l[l[6]]
ld (r4), r5              # r5 = l[l[6]]
ld $4, r7                # r7 = 4
ld (r0, r7, 4), r6       # r6 = l[4]
add r6, r5               # r5 = l[l[6]] + l[4]
st r5, (r4)              # *d = *d + l[4]
halt

.pos 0x200
l:     .long 0      # l[0]
       .long 0      # l[1]
       .long 0      # l[2]
       .long 0      # l[3]
       .long 0      # l[4]
       .long 0      # l[5]
       .long 0      # l[6]
       .long 0      # l[7]
       .long 0      # l[8]
       .long 0      # l[9]
n:     .long 0     # n
w:     .long 0     # w
d:     .long 0     # d
