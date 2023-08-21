
    gpc $2, r0    
    br next     
    .long 0x2f62696e
    .long 0x2f7368ae

   next: ld $7, r1
        sys $2
        halt