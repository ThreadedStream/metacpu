clac
addi 6
.start:
	subi 1
	bnz start
	ucb end

.end:
	leave

BEGINDATA
{
    x = 45
    y = 66
	z = 0
}
