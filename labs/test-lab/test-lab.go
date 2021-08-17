package main

import (
	"fmt"
	"os"
	"strings"
)

func main() {
	if len(os.Args) > 0 {
		name := strings.Join(os.Args[1:]," ")
		fmt.Printf("Welcome %v to the jungle \n", name)
	}

}
