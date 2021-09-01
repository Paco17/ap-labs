#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// adds/subtracts/multiplies all values that are in the *values array.
// nValues is the number of values you're reading from the array
// operator will indicate if it's an addition (1), subtraction (2) or
// multiplication (3)
long calc(int operator, int nValues, int *values) {
    int tmp=values[0];
    int resultado = tmp;
    printf("%d", tmp);
    for(int i =1; i<nValues; i ++){
        if(operator==0){
            printf(" + %d", values[i]);
            resultado+=values[i];
        }else if(operator==1){
            printf(" - %d", values[i]);
            resultado-=values[i];
        }else{
            printf(" * %d", values[i]);
            resultado*=values[i];
        }
    } printf(" = %d\n", resultado);

    return 0;
}

int main(int argc, char**argv) {
    if(argc>3){
        char operator=-1;
        if(strcmp(argv[1], "add")==0){
            operator = 0;
        }else if(strcmp(argv[1], "sub")==0){
            operator = 1;
        }else if(strcmp(argv[1], "mult")==0){
            operator = 2;
        }else{
            printf("You didn't put a valid operator, you put: %s\n", argv[1]);
            return -1;
        }
        
        //printf("Operador: %d\n", operator);
        
        int arrayNum[argc-1];
        int cont =0;
        for(int i =2; i<argc; i++){
            for(int j =0; j<strlen(argv[i]); j++){
                //printf("Number: %c\n", argv[i][j]);
                if(!isdigit(argv[i][j])){
                    if(argv[i][j]!='-'){
                        printf("Este numero no es valido: %s\n", argv[i]);
                        return -1;
                    }
                }
            } arrayNum[cont] = atoi(argv[i]);
            cont+=1;
        }
        
        calc(operator, argc-2, arrayNum);






    }else{
        printf("You forget to put a number or an operator, not enough parameters\n");
        return -1;
    }
   
}
