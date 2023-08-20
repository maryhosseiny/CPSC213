ld $s, r0          # r0 = addr of s
st r0, (r0)        # r0 = s
ld $array, r1      # r1 = addr of array
ld $3, r2          # r2 = 3
ld (r1, r2, 4), r3 # r3 = array[3]
st r3, (r0)        # s = array[3]
ld $1, r2          # r2 = 1
ld (r1, r2, 4), r4 # r4 = array[1]
ld $3, r5          # r5 = 3
st r4, (r1, r5, 4) # array[3] = array[1]
ld (r0), r0        # r0 = s
st r0, (r1, r2, 4) # array[1] = s
halt

.pos 0x1000
s:     .long 0 # the variable a
.pos 0x2000
array:
      .long 0 # the variable b[0]
      .long 2 # the variable b[1]
      .long 0 # the variable b[2]
      .long 5 # the variable b[3]
      .long 0 # the variable b[4]
      .long 0 # the variable b[5]