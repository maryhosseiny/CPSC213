.pos 0x100
                ld $z, r0       # r0 = address of z
                ld (r0), r1     # r1 = z
                inc r1          # r1 = r1 + 1
                inca r1         # r1 = r1 + 4
                shl $0x6, r1    # r1 = r1 << 6
                ld (r0), r2     # r2 = z
                and r2, r1      # r1 = r1 & z
                shr $0x4, r1    # r1 = r1 / 16
                ld $h, r3       # r3 = address of h
                st r3, (r1)     # h = r1
                halt            # halt
.pos 0x1000
h:              .long 0x00000000 #h
.pos 0x2000
z:              .long 0x0aaaaaaa #z