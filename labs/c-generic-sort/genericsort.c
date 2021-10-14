//Francisco Ramos - A01636425
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINES 10000
void *lineptr[MAX_LINES];

void quicksort(void *lineptr[], int left, int right,
	   int (*comp)(void *, void *));

void mergesort(void *lineptr[], int left, int right,
	   int (*comp)(void *, void *));

int readlines(FILE *inputFile);

void writelines(FILE *output, int nlines);

int numcmp(char *, char *);

int numcmp(char *s1, char *s2) {
    double v1 = atof(s1),
        v2 = atof(s2);

    return (int) (v1 - v2);
}


void writelines(FILE *output, int nlines) {
    for (int i = 0; i < nlines; i++) {
        fprintf(output, "%s", (char *)lineptr[i]);
    }
	fclose(output);
}

int readlines(FILE *inputFile) {
    char *line;

	int lines = 0;

    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, inputFile) != -1)) {
		if (lines == MAX_LINES) {
            printf("El archivo es demasiado grande porfavor reduzca las lineas");
            exit(0);
        }
        lineptr[lines] = malloc(strlen(line));
        strcpy(lineptr[lines++], line);
    }

	fclose(inputFile);
    return lines;
}


int main(int argc, char **argv) {
	if (argc < 2) {
		printf("El formato debe ser:\n ./genericsort -n numbers.txt -quicksort -o qs_sorted_numbers.txt\n ");
		printf("o \n./genericsort strings.txt -mergesort -o ms_sorted_strings.txt\n\n");
		return -1;
	}


	FILE *inputFile,
		 *outputFile;

	char inputName[50] = "",
		 outputName[50] = ""; 

	int number = 0;
	
	if (strcmp(argv[1], "-n") == 0) {
		if (argc != 6) {	
			printf("El formato debe ser:\n ./genericsort -n numbers.txt -quicksort -o qs_sorted_numbers.txt\n ");
			printf("o \n./genericsort strings.txt -mergesort -o ms_sorted_strings.txt\n\n");
			return -1;
		}
		number = 1; 
	} else if (argc != 5) {
		printf("El formato debe ser:\n ./genericsort -n numbers.txt -quicksort -o qs_sorted_numbers.txt\n ");
		printf("o \n./genericsort strings.txt -mergesort -o ms_sorted_strings.txt\n\n");
		return -1;
	}

	strcat(inputName, argv[1+number]); 

	if (strcmp(argv[3+number], "-o") != 0) {
		printf("El formato debe ser:\n ./genericsort -n numbers.txt -quicksort -o qs_sorted_numbers.txt\n ");
		printf("o \n./genericsort strings.txt -mergesort -o ms_sorted_strings.txt\n\n");
		return -1;
	}

	strcat(outputName, argv[4+number]); 

	if ((inputFile = fopen(inputName, "r")) == NULL) {
		printf("El archivo no puede encontrarse, no existe\n");
		return 0;
	}

	int lines = readlines(inputFile);

	if (strcmp(argv[2+number], "-quicksort") == 0) {
		quicksort(lineptr, 0, lines-1, (number ? (int (*)(void *, void *)) numcmp : (int (*)(void *, void *))strcmp));
	}if (strcmp(argv[2+number], "-mergesort") == 0) {
		mergesort(lineptr, 0, lines-1, (number ? (int (*)(void *, void *)) numcmp : (int (*)(void *, void *))strcmp));
	}

    if ((outputFile = fopen(outputName, "w")) == NULL)
    {
        printf("No se puede crear el archivo\n");
        return -1;
    }

    writelines(outputFile, lines);

    return 0;
}
