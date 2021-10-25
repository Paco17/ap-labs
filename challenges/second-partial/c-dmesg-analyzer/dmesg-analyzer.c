//Francisco Javier Ramos - A01636425
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define REPORT_FILE "dmesg-report.txt"

//Tam del Hash
#define HASHLEN 5000

unsigned hash(char *key);
void insert(char *key, char *log);
void analizeLog(char *logFile, char *report);


struct hash {
    char *data[HASHLEN]; // Msg de Log
    char *key; // Tipo de Log
};

struct hash *array[HASHLEN];

//Metodo insertar
void insert(char* key, char* log) {
    struct hash *item = (struct hash*) malloc(sizeof(struct hash));
    int index = hash(key);
    int i = 0;
    
    while(array[index] != NULL) {
        if(strcmp(array[index]->key, key) == 0){
            while(array[index]->data[i] != NULL) i++;
            array[index]->data[i] = malloc (sizeof(char) * strlen(log));
            strncpy(array[index]->data[i], log, strlen(log));
            return;
        }
      index++;
      index %= HASHLEN;
    }

    item->key = malloc (sizeof(char) * strlen(key));
    strncpy(item->key, key, strlen(key));
    item->data[0] =  malloc (sizeof(char) * strlen(log));
    strncpy(item->data[0], log, strlen(log));
    array[index] = item;
}

unsigned hash(char *key){
    unsigned hashval;
    for(hashval = 0; *key != '\0'; key++){
        hashval = *key + 31 *hashval;
        return  hashval % HASHLEN;
    }
}

//Metodo Principal
void analizeLog(char *logFile, char *report) {
    printf("Generating Report from: [%s] log file\n", logFile);

    array[HASHLEN] = (struct hash*) malloc(sizeof(struct hash));
    
    FILE *fp;
	char * line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen(logFile,"r");

    if (fp  == NULL){
		return;
	}

    int i = 0;
    FILE *rep;

    while ((read = getline(&line, &len, fp)) != -1) {
		if(strcmp("\n", line) != 0){
            int tiempo, posicion, start, len;
            tiempo = posicion = start = len = 0;
            
            if(line[posicion] == '['){
                while(line[posicion] != ']'){
                    posicion++;
                    tiempo++;
                }

                posicion += 2;
                tiempo += 1;
                start = posicion;
                
                while(':' != line[posicion] && posicion < strlen(line)){
                    posicion++;
                    len++;
                }

                char log[len];
                char tmpArra[tiempo];
                
                if(posicion == strlen(line)){
                    
                    strncpy(tmpArra, line, tiempo);
                    tmpArra[tiempo] = '\0';

                    char msg[strlen(line) - tiempo];
                    strncpy(msg, line + tiempo, strlen(line) - tiempo);
                    msg[strlen(line) - tiempo] = '\0';

                    char msg2[strlen(line)];
                    strcpy(msg2, tmpArra);
                    strcat(msg2, msg);
                    msg2[strlen(line)] = '\0';   

                    insert("General", msg2);
      
                }else{
                    strncpy(log, line + start, len);
                    strncpy(tmpArra, line, tiempo);
                    log[len] = '\0';
                    tmpArra[tiempo] = '\0';

                    char msg[strlen(line) - len - tiempo];
                    msg[strlen(line) - len - tiempo] = '\0';
                    strncpy(msg, line + posicion + 1, strlen(line) - len - tiempo);

                    char msg2[strlen(line) - len + 1];
                    strcpy(msg2, tmpArra);
                    strcat(msg2, msg);
                    msg2[strlen(line) - len + 1] = '\0';
                    insert(log, msg2);
                }               
            }
		}
    }
    
   
    rep = fopen(REPORT_FILE, "w+");

    for(i = 0; i < HASHLEN; i++) {
        if(array[i] != NULL){
            fprintf(rep,"%s:\n",array[i]->key );
            for(int j = 0; j < HASHLEN; j ++ )
                if(array[i]->data[j] !=NULL )
                    fprintf(rep, "\t%s",  array[i]->data[j]);
        }
    }


    int fd;
    fd=open(REPORT_FILE,O_RDWR);
    close(fd);
}

int main(int argc, char **argv) {

    if (argc < 2) {
        printf("Usage:./dmesg-analizer logfile.txt\n");
        return 1;
    }

    analizeLog(argv[1], REPORT_FILE);
    return 0;
}





