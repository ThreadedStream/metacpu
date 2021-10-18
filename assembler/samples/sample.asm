.start:
	clac
	addi 6

.loop:
	subi 1
	bnz loop	
	ucb end

.end:
	leave

BEGINDATA
{
    x = 45
    y = 66
	z = 0
}
