.start:
	clac
	addi 10

.print_acc:
	subi 1
	out 
	cmpi 0
	big print_acc
	ucb end

.end:
	leave

BEGINDATA
{
    x = 0
    y = 66
	z = 0
}
