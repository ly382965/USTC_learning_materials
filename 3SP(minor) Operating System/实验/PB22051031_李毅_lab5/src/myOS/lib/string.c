int strLength(unsigned char *str){
    int n=0;
    while(*str++) n++;
    return n;
}

int strcpy(unsigned char *src, unsigned char *dst){
    int n=0;
    while(*src) {
        *dst++ = *src++;
        n++;
    }
    return n;
}

int strncpy(unsigned char *src, unsigned char *dst, unsigned int n){
    int nn=0;
    while(*src) {
        *dst++ = *src++;
        nn++;
	    if (nn >= n) break;
    }
    return nn;
}

int strcmp(unsigned char *str1, unsigned char *str2){
    unsigned char c1, c2;
    do {
        c1 = *str1++;
        c2 = *str2++;
        if (c1 != c2) return (c1 > c2)?1:-1;
        if (c1 == '\0') break;
    } while(1);
    return 0;  //equal    
}

/*
int strncmp(unsigned char *str1, unsigned char *str2, unsigned int n){
    unsigned char c1, c2;    

    while(n){
        c1 = *str1++;
        c2 = *str2++;        
        if (c1 != c2) return (c1 > c2)?1:-1;
        if (c1 == '\0') break;
    };
    return 0;
}*/
