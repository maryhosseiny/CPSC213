.pos 0x100
                ld $a, r0           # r0 = addr of a 
                ld $b, r1           # r1 = addr of b
                ld $0, r2           # r2 = 0 = i'
                ld $n, r3           # r3 = &n
                ld (r3), r3         # r3 = n
                ld $0, r4           # r4 = 0 = c'
L0:             mov r2, r5          # r5 = i'
                not r5              # r5 = ~i
                inc r5              # r5 = -i
                add r3, r5          # r5 = n - i
                bgt r5, L1          # if (i<n) goto L1
                br L3               # else goto L3
L1:             ld (r0, r2, 4), r5  # r5 = a[i]
                ld (r1, r2, 4), r6  # r6 = b[i]
                mov r6, r7          # r7 = b[i]'
                not r7              # r7 = ! b[i]
                inc r7              # r7 = - b[i]
                add r5, r7          # r7 = a[i] - b[i]
                bgt r7, L2          # if (a[i] > b[i]) goto L2
                inc r2              # r2 = r2 + 1 (i++)
                br L0               # goto L0, loop back
L2:             inc r4              # r4 = r4 + 1 (c += 1)
                inc r2              # r2 = r2 + 1 (i++)
                br L0               # goto L0, loop back
L3:             ld $c, r5           # r5 = addr of c
                st r4, (r5)         # c = c' 
                ld $i, r6           # r6 = addr of i
                st r2, (r6)         # i = i'          
                halt            

.pos 0x200
i:              .long 0xffffffff    # i = -1
n:              .long 0x5           # n = 5
a:              .long 0xa           # 10
                .long 0x14          # 20
                .long 0x1e          # 30
                .long 0x28          # 40
                .long 0x32          # 50
b:              .long 0xb           # 11
                .long 0x14          # 20
                .long 0x1c          # 28
                .long 0x2c          # 44
                .long 0x30          # 48
c:              .long 0x0           # c = 0