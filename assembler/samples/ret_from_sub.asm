clac
.start:
    ucb do_smth
    ucb end

.print_char:
    outb
    ret

.do_smth:
    addi 101
    ucb print_char
    ret

.end:
    leave
