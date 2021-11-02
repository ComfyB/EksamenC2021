#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
int toDecimal(char *hex){
    int i,value, length;
    long decimal = 0, base = 1;
    length = strlen(hex);
    printf("i funksjonen to decimal");
  for(i= length--; i>=0; i--){
      if(hex[i]>='0' && hex[i]<= '9'){
          decimal+=(hex[i]-48)*base;
          base *= 16;
      }else if(hex[i]>='A'&& hex[i]<='F'){
          decimal += (hex[i]-55)*base;
          base *=16;
      }else if(hex[i]>='a' && hex[i]<= 'f'){
          decimal+=(hex[i]-87)*base;
          base*=16;
      }
  }
  return decimal;
}
int main(){
    char ch, ch2;
    char* str[2];
    int decimal;
    
    //åpne filer for input/output
    FILE *fptrIn = fopen("hexdec.txt", "r");
    FILE *fptrOut = fopen("toascii.txt", "w");

    //check if file is found
    if(fptrIn == NULL || fptrOut == NULL){
        printf("File Not found");
        exit(1);
    }
    //while to read through file.
    while ((ch=fgetc(fptrIn)) != EOF){
        ch2= fgetc(fptrIn);
        str= ''
        strncat(str,&ch,1);
        strncat(str,&ch2,1);
        printf("%lld",toDecimal(str));

    }
    fclose(fptrIn);
    fclose(fptrOut);
return 0;
}