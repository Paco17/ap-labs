#include <stdio.h>
#include <string.h>

extern int mystrlen(char*);
extern char* mystradd(char*, char*);
extern int mystrfind(char*, char*);

int main(int argc, char* argv[]) {
    if(argc == 4){
        if(strcmp(argv[0], "-add")){//Funcion add
             printf("Initial Length: %d\n", mystrlen(argv[2]));
            char* newString = mystradd(argv[2], argv[3]);
            printf("New String:  %s\n", newString);
            printf("New Length: %d\n\n", mystrlen(newString));

        }else if(strcmp(argv[0], "-find")){//Funcion find
            int p = mystrfind(argv[2], argv[3]);
            if(p>=0){
                printf("[%s] string was found at [%d] position\n\n", argv[3], p);
            }
            else{
                printf("Error no hubo ocurrencias\n");
            }
           
        }else{
            printf("Error en nombrar la funcion. \n Ej: ./main.o -add (or -find) 'Initial String '' 'This is the rest to be added' \n ");

        }

    }else{
        printf("No hay suficientes parametros. \n Ej: ./main.o -add 'Initial String '' 'This is the rest to be added' \n ");
    }
    return 0;
}
