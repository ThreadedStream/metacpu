package main

import (
	"fmt"
	"github.com/ThreadedStream/metacpu/vm"
)

func main() {
	var (
		path   = "D:\\toys\\metacpu\\assembler\\samples\\sample.bin"
		memory [256]uint16
	)
	err := vm.LoadSrcIntoMemory(path, &memory)
	if err != nil {
		fmt.Printf("%s", err.Error())
	}
}
