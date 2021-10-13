#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINES 5000 
void *lineptr[MAX_LINES];


void quicksort(void *lineptr[], int left, int right,int (*comp)(void *, void *));

void mergesort(void *lineptr[], int left, int right, int (*comp)(void *, void *));

int readLines(FILE *file);

//Me quede creando los ultimo metodos
int numcmp(char *s1, char* s2)


int main(int argc, char **argv)
{
	if(argc> 4 && argc<7){
		FILE *in;
		FILE *out;
		char *method; 
		bool flag = true;
		
		//ReadFile

		//Si es el quicksort
		if((strcmp(argv[1], "-n") == 0 ) && argc == 6 && (strcmp(argv[3], "-quicksort") == 0)){
			
			method = argv[3];
			in = fopen(argv[2], "r");
			
			if(in == NULL){
				printf("Archivo no existe o error al buscarlo\n");
				return -1;
			}
		}if(argc == 5 && (strcmp(argv[2], "-mergesort") == 0)){
			method = argv[2];
			in = fopen(argv[1], "r");
			flag = false;
			if(in == NULL){
				printf("Archivo no existe o error al buscarlo\n");
				return -1;
			}
		}

		readLines(in);
		if(flag){//quicksort
			quicksort(lineptr, 0, numLines-1, (sortNumbers ? (int (*)(void *, void *)) numcmp : (int (*)(void *, void *))strcmp));
		}else{

		}
		
	}else{
		printf("El formato debe ser:\n ./genericsort -n numbers.txt -quicksort -o qs_sorted_numbers.txt\n ");
		printf("o \n./genericsort strings.txt -mergesort -o ms_sorted_strings.txt\n\n");		
	}

    return 0;
}

int readLines(FILE *file){
	char *line;
	int nl = 0;
	size_t len = 0;
	ssize_t read;

	while((read = getline(&line, &len, file))!= -1){
		if(nl==MAX_LINES){
			printf("Big File try something smaller");
			return -1;
		}
		printf("%s\n",line);
		lineptr[nl] = malloc(strlen(line));
		nl ++;
	}

	fclose(file);
	return nl;


}




