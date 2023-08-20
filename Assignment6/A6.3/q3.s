.pos 0x1000
			ld $s, r0				    		# r0 = addr of s
			ld 0(r0), r0			  			# r0 = s[0]
			ld $0, r1				   			# r1 = 0 = i'
			ld $n, r7				    		# r7 = addr of n
			ld 0(r7), r7			  			# r7 = n
			bgt r7, ave							# goto ave if 0 < n
ave:	
      		mov r1, r2		      				# r2 = i
			mov r1, r3				  			# r3 = i
			shl $1, r2				  			# r2 = i<<1
			shl $2, r3		  					# r3 = i<<2
			add r3, r2			  				# r2 = i * 6
			ld $1, r3				    		# r3 = 1
			add r2, r3				  			# r3 = i * 6 + 1
			ld (r0, r3, 4), r3					# r3 = grade 0
			ld $2, r4				    		# r4 = 2
			add r2, r4			  				# r4 = 2 + i * 6
			ld (r0, r4, 4), r4  				# r4 = grade 1
			add r4, r3				  			# r3 = grade 0 + grade 1
			ld $3, r4				    		# r4 = 3
			add r2, r4				  			# r4 = 3 + i * 6
			ld (r0, r4, 4), r4					# r4 = grade 2
			ld $4, r5				    		# r5 = 4
			add r2, r5				  			# r5 = 4 + i * 6
			ld (r0, r5, 4), r5  				# r5 = grade 3
			add r5, r4				  			# r4 = grade 2 + grade 3
			add r4, r3				  			# r3 = grade[0-3]
			shr $2, r3				  			# r3 = grades average (grade[0-3]/4)
			ld $5, r4				   			# r4 = 5
			add r2, r4				 			# r4 = 5 + i * 6
			st r3, (r0, r4, 4) 					# computed avg = avg
			inc r1					   			# r1 = i++
			mov r1, r3				 			# r3 = i
			not r3					   			# r3 = ~i
			inc r3					   			# r3 = -i
			add r7, r3				 			# r3 = n - i
			bgt r3, ave	 						# goto ave if 0 < n - i
			ld $1, r3							# r3 = 1
      		not r3            					# r3 = ~r3
      		inc r3            					# r3 = -1
			add r7, r3							# r3 = n - 1
			beq r3, med	      					# if n - 1 == 0 goto med
			br sort					  			# to sort
sort:		
      		ld $0, r1				  			# r1 = 0 = i
			ld $n, r2				  			# r2 = addr of n
			ld (r2), r2							# r2 = n
			ld $1, r3				  			# r3 = 1
      		not r3            					# r3 = ~r3
      		inc r3        						# r3 = -1
			add r3, r2							# r2 = n - 1
			ld $j, r4				  			# r4 = addr of j
			st r2, 0(r4)						# j = n - 1
			j L4 
L2:  
      		inc r1			      				# r1 = i++
			ld $j, r2				  			# r2 = addr of j
			ld 0(r2), r2						# r2 = j
			mov r1, r3							# r3 = i
			not r3					  			# r3 = ~i
			inc r3					  			# r3 = -i
			add r2, r3			  				# r3 = j - i
			bgt r3, L4 							# goto L4 if 0 < j - i 
			ld $1, r3				  			# r3 = 1
      		not r3            					# r3 = ~r3
      		inc r3            					# r3 = -1
			add r3, r2							# r2 = j - 1
			ld $j, r4				  			# r4 = addr of j
			st r2, 0(r4)						# j = j - 1
			ld $0, r1				 			# r1 = 0 = i'
			bgt r2, L4 							# jump to L4 if j > 0
			br med				  				# jump to med
swap:	
      		mov r1, r2							# r2 = i
			mov r1, r3							# r3 = i
			shl $1, r2							# r2 = i<<2
			shl $2, r3							# r3 = i<<4
			add r3, r2							# r2 = i * 6
			ld $6, r5							# r5 = 6
			ld $6, r7							# r7 = 6
			add r2, r7			  				# r7 = r5+ i * 6
			add r2, r5			  				# r5 = r6+ i * 6
			j L3
L3:	
      		ld (r0, r2, 4), r4					# r4 = val of student i
			ld (r0, r5, 4), r6					# r6 = val of student i + 1
			st r4, (r0, r5, 4)					# i + 1 = i
			st r6, (r0, r2, 4)					# i = i + 1
			inc r2					  			# r2 = r2 + 1
			inc r5					  			# r5 = r5 + 1
			mov r2, r4							# r4 = r2
			not r4					  			# r4 = ~r2
			inc r4					  			# r4 = -r2
			add r7, r4							# r4 = (6 + i*6) - r2
			bgt r4, L3					        # goto L3 if (6 + i * 6)-r2 > 0
			br L2								# goto L2
L4: 
      		mov r1, r2							# r2 = i
			mov r1, r3							# r3 = i
			shl $1, r2							# r2 = i<<1
			shl $2, r3							# r3 = i<<2
			add r3, r2							# r2 = i * 6
			ld $5, r3				  			# r3 = 5
			ld $11, r5							# r5 = 11
			add r2, r3							# r3 = 5 + i * 6
			add r2, r5							# r5 = 11 + i * 6
			ld (r0, r3, 4), r4					# r4 = avg of i
			ld (r0, r5, 4), r6					# r6 = avg of i + 1
			not r6					  			# r6 = ~r6
			inc r6					  			# r6 = -r6
			add r6, r4							# r4 = r4 - r6
			bgt r4, swap						# goto swap if avg of student i > i + 1
			br L2								# goto L2
med:
      		ld $n, r1				  			# r1 = &n
			ld 0(r1), r1						# r1 = n
			shr $1, r1							# r1 = n>>1 = n/2
			mov r1, r2							# r2 = r1
			mov r1, r3							# r3 = r1
			shl $1, r2							# r2 = r2<<1 = r2*2
			shl $2, r3							# r3 = r2<<2 = r2*4
			add r3, r2							# r2 = r2 * 6
			ld (r0, r2, 4), r4					# r4 = avg median 
			ld $m, r5				  			# r5 = &m
			st r4,  0(r5)		  				# m = median average
			halt

.pos 0x3000
n:		.long 3									# number of students
m:		.long 0									# median average
s:		.long base								# dynamic array of students
base:	
      .long 1234			# studend id
			.long 80		# grade 0
			.long 88		# grade 1
			.long 90		# grade 2
			.long 50		# grade 3
			.long 0  		# computed average

			.long 5678		# studend id
			.long 50		# grade 0
			.long 66		# grade 1
			.long 79		# grade 2
			.long 53		# grade 3
			.long 0   		# computed average

			.long 9012		# studend id
			.long 80		# grade 0
			.long 89		# grade 1
			.long 95		# grade 2
			.long 99		# grade 3
			.long 0   		# computed average

.pos 0x5000
j:		.long 0	