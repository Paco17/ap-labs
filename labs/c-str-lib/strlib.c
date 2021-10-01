int mystrlen(char *str){
    int length = 0;
    for(int i=0; str[i]!= '\0'; i++){
        length++;
    }

    return length;
}

char *mystradd(char *origin, char *addition){
    char* str[mystrlen(origin)+ mystrlen(addition)];
    int i= 0, j=0;
    
    while(origin[i]!= "/0"){
        str[i] = origin[i];
        i++;
    }

    while(addition[j] != '/0'){
        str[i] = origin[j];
        j++;
    }

    return str;

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
