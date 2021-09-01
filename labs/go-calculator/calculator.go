package main

import (
	"fmt"
	"os"
	"strconv"
	 
)

// adds/subtracts/multiplies all values that are in the *values array.
// nValues is the number of values you're reading from the array
// operator will indicate if it's an addition (1), subtraction (2) or
// multiplication (3)
func calc(operator int, values []int) int {
	result:=values[0]
	fmt.Printf("%v",result)
	for i:=1; i<len(values); i++{
		if operator == 0 {
			fmt.Printf(" + %v",values[i])
			result+=values[i]
		}

		if operator == 1 {
			fmt.Printf(" - %v",values[i])
			result-=values[i]
		}

		if operator == 2 {
			fmt.Printf(" * %v",values[i])
			result*=values[i]
		}
		
	}
	fmt.Printf(" = %v\n", result)
	return 0
}

func main() {
	arr := os.Args
	operator:=-1
	if len(arr)>3 {
		if arr[1]=="add" {
			operator = 0
		}else if arr[1] == "sub" {
			operator = 1
		}else if arr[1] == "mult" { 
			operator = 2
		}else{
			fmt.Printf("This operator %v is invalid", operator)
			return
		}
		
		//Check valid numbers
		var num []int;
		for i:=2; i<len(arr); i++{
			for j:=0; j<len(arr[i]); j++{
				
				if !(arr[i][j]<58 && arr[i][j] >47) {
					if  !(j==0 && arr[i][j]==45){
						fmt.Printf("This is not a valid number %v\n", arr[i])
						return
					}
				}
			};
			value, err := strconv.Atoi(arr[i])
			if err == nil {
				num = append(num, value)
			}else{
				fmt.Printf("Something went wrong in the numbers")
			}
		}

		calc(operator, num)
	}else{
		fmt.Printf("Missing parameters, at least 3 parameters (1 operator and 2 numbers)")
		return
	}
	/*operator := os.Args[1]

	for i := 1; i < 5; i++ {
		fmt.Printf("%v\n", operator)
	}*/

}
