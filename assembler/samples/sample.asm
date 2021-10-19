.start:
	clac
	addi 200

.loop:
	sub x
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
