#include <stdio.h>
#include <stdlib.h>

//Año bisiesto?
int leap(int *y){
    if((*y % 4==0 && *y % 100 !=0)|| *y %400==0){
        return 1;
    }return 0;
}

//Retornar nombre del mes
char *month_name(int n){
    static char *name[] = {
       "Illegal month",
       "Jan", "Feb", "Mar",
       "Apr", "May", "Jun",
       "Jul", "Aug", "Sep",
       "Oct", "Nov", "Dec"
   };

   return (n < 1 || n > 12) ? name[0] : name[n];
}


/* month_day function's prototype*/
void month_day(int year, int yearday, int *pmonth, int *pday){
    int i = 0;
    while(yearday > pday[i]){
        yearday -= pday[i];
        i++;
    }

    printf("%s %02d, %d\n",month_name(i+1), yearday, year);
}

int main(int arg, char** argv) {
    //Checar numero de argumentos
    if(arg<2){
        printf("Faltan argumentos");
    }else if(arg>3){
        printf("Hay mas argumentos de los necesarios");
    }else{

        int year = atoi(argv[1]);
        int days = atoi(argv[2]);

        //Checar si inputs son validos
        if(year<=0 || days<=0 || days>366){
            printf("El año o la cantidad de dias no son validos"); 
            return 0;
        }

        //Checar si es año bisiesto
        int days_per_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if(leap(&year)){
            //printf("Año bisiesto");
            days_per_month[1]+=1;
            
        }else{
            if(days==366){
                printf("No es  año bisiesto, no esta permitido 366 dias");
                return 0;
            }
        }
        static int months[] = {1,2,3,4,5,6,7,8,9,10,11,12};

        month_day(year, days, months, days_per_month);

    }

    return 0;
}
