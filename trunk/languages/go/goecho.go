package main

import (
	"os"
	"flag" // парсер параметров командной строки
)

var omitNewline = flag.Bool("n", false, "не печатать последнюю линию")

const (
	Space   = " "
	Newline = "\n"
)

func main() {
	flag.Parse() // Сканирование списка аргументов и установка флагов
	var s string = ""
	for i := 0; i < flag.NArg(); i++ {
		if i > 0 {
			s += Space
		}
		s += flag.Arg(i)
	}
	if !*omitNewline {
		s += Newline
	}
	os.Stdout.WriteString(s)
}
