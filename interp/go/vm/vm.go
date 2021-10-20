package vm

// #include "utils.h"
import "C"

import (
	"errors"
	"os"
	"unsafe"
)

const (
	metasmMagic = "metasm v_1_0"
)

type vmstate struct {
	pc     uint32
	acc    uint16
	memory [256]uint16
}

func LoadSrcIntoMemory(path string, memory *[256]uint16) error {
	var stream, err = os.Open(path)
	if err != nil {
		return err
	}

	var magic = make([]byte, len(metasmMagic))

	_, err = stream.Read(magic)
	if err != nil {
		return err
	}

	if string(magic) != metasmMagic {
		return errors.New("incorrect magic value")
	}

	var (
		magicLen        = (C.int)(len(metasmMagic))
		buffer   *int16 = (*int16)(C.readBinaryData(C.CString(path), magicLen))
	)

	if unsafe.Pointer(buffer) == C.NULL {
		return errors.New("buffer is NULL")
	}

	return nil
}
