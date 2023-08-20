.pos 0x100
                ld $array, r0           # r0 = address of array[0]
                ld (r0), r1             # r1 = array[0]
                ld $origin, r2          # r2 = address of origin
                st r1, (r2)             # origin = address of array[0]
                ld $array, r0           # r0 = address of array[0]
                ld 0x4(r0), r1          # r1 = array[1]
                st r1, (r0)             # array[0] = array[1]
                ld $origin, r0          # r0 = address of origin
                ld (r0), r1             # r1 = origin
                ld $array, r2           # r2 = address of array
                st r1, 0x4(r2)          # array[1] = origin
                halt 
.pos 0x1000
origin:         .long 0x00000000        # origin
.pos 0x2000
array:          .long 0x00000010        #array[0]
                .long 0x00000020        #array[1]
                .long 0x00000030        #array[2]
                .long 0x00000040        #array[3]
                .long 0x00000050        #array[4]
                .long 0x00000060        #array[5]
                .long 0x00000070        #array[6]
                .long 0x00000080        #array[7]
                .long 0xffffffff        #array[8]
                .long 0x00000090        #array[9]