//A01636425 - Francisco Ramos
package main

import (
	"fmt"
	"io"
	"log"
	"net"
	"os"
	"strings"
)

func main() {

	tzArgs := make(chan []string, len(os.Args)-1)
	done := make(chan bool)
	go func() {
		for {
			foo, ok := <-tzArgs
			if ok {

				conn, err := net.Dial("tcp", foo[1])
				if err != nil {

					log.Fatal("Error de conexion.")
				}
				defer conn.Close()

				tmp := make([]byte, 256)
				for {
					_, err := conn.Read(tmp)
					if err != nil {
						if err != io.EOF {
							fmt.Println("Error:", err)
						}
						break
					}

					tz := strings.SplitN(string(tmp), "...", 2)
					print(tz[0] + ": ")
					fmt.Print(tz[1])
					break
				}

			} else {
				done <- true
				return
			}
		}
	}()

	for i := 1; i < len(os.Args); i++ {
		pair := strings.SplitN(os.Args[i], "=", 2)
		tzArgs <- pair
	}
	close(tzArgs)
	<-done

}
