#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int toDecimal(char *in){
    int i, length;
    long decimal = 0, base = 1;
    length = strlen(in);
   //printf("i funksjonen to decimal");
  for(i= length; i>=0; i--){
      if(in[i]>='0' && in[i]<= '9'){
          decimal+=(in[i]-48)*base;
          base *= 16;
      }else if(in[i]>='A'&& in[i]<='F'){
          decimal += (in[i]-55)*base;
          base *=16;
      }else if(in[i]>='a' && in[i]<= 'f'){
          decimal+=(in[i]-87)*base;
          base*=16;
      }
  }
  return decimal;
}
int main(){
    char* ch, ch2;

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
        strncat(&ch,&ch2,1);
        printf("%c",toDecimal(&ch));

        //write to output stream
        fputc(toDecimal(&ch), fptrOut);
    }
    fclose(fptrIn);
    fclose(fptrOut);
return 0;
}