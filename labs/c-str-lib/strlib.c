int mystrlen(char *str){
    int length = 0;
    for(int i=0; str[i]!= '\0'; i++){
        length++;
    }

    return length;
}

char *mystradd(char *origin, char *addition){
    char *str = origin + mystrlen(addition);
   
    
    while(*addition!= '\0'){
        *str++ = *addition++;
    
    }


    *str = '\0';
    return origin;

}

int mystrfind(char *origin, char *substr){
    int pOrg =0, pSubs=0, index = 0, lenOrg = mystrlen(origin);
    while(origin[pOrg]!='\0'){
        index = pOrg;
        while(origin[pOrg]!='\0' && origin[pOrg] == substr[pSubs]){
            pOrg++;
            pSubs++;
        }

        if(lenOrg == pSubs)
            return index;
        pSubs = 0;
        pOrg++;
    }

    return -1;
}
