clac
.start:
    ucb do_smth
    ucb end

.do_smth:
    addi 101
	outb
	clac
	submem counter
	cmp counter
	bnz do_smth
    ret

.end:
    leave

BEGINDATA{ 
	counter = 2
}