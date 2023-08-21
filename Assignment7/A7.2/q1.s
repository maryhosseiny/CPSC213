.pos 0x0
    ld   $sb, r5         # r5 = &sb (address of the stack base)
    inca r5              # increment the value of r5 to adjust the stack pointer
    gpc  $6, r6          # ra = pc + 6
    j    0x300           # jump to address 0x300
    halt                 # halt

.pos 0x100
    .long 0x00001000     # store val 0x00001000 in memory location 0x100

.pos 0x200
    ld   (r5), r0        # r0 = x (argument 1)
    ld   4(r5), r1       # r1 = y (argument 2)
    ld   $0x100, r2      # r2 = &arr (&0x100)
    ld   (r2), r2        # r2 = value of arr (0x100)
    ld   (r2, r1, 4), r3 # r3 = arr[y]
    add  r3, r0          # r0 = arr[y] + x
    st   r0, (r2, r1, 4) # r2 = x[y]
    j    (r6)            # jump to the return address

.pos 0x300
    ld   $-12, r0        # r0 = -12
    add  r0, r5          # allocate stack frame
    st   r6, 8(r5)       # store the return address
    ld   $1, r0          # r0 = 1
    st   r0, (r5)        # a = 1 (local var1)
    ld   $2, r0          # r0 = 2
    st   r0, 4(r5)       # b = 2 (local var2)
    ld   $-8, r0         # r0 = -8
    add  r0, r5          # allocate more space
    ld   $3, r0          # r0 = 3
    st   r0, (r5)        # x = 3
    ld   $4, r0          # r0 = 4
    st   r0, 4(r5)       # y = 4
    gpc  $6, r6          # return address
    j    0x200           # jump to 0x200
    ld   $8, r0          # r0 = 8
    add  r0, r5          # deallocate stack 
    ld   (r5), r1        # r1 = a
    ld   4(r5), r2       # r2 = b
    ld   $-8, r0         # r0 = -8
    add  r0, r5          # allocate stack space
    st   r1, (r5)        # x = 1
    st   r2, 4(r5)       # y = 2
    gpc  $6, r6          # return address
    j    0x200           # jump to 0x200
    ld   $8, r0          # r0 = 8
    add  r0, r5          # deallocate stack
    ld   8(r5), r6       # load return address
    ld   $12, r0         # r0 = 12
    add  r0, r5          # deallocate stack
    j    (r6)            # jump to return address

.pos 0x1000
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0

.pos 0x8000
    # These are here so you can see (some of) the stack contents
    # while running the code on the simulator.
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
sb: .long 0
