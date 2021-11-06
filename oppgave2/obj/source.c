#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int toDecimal(char *in);
int letterOccurenceCounter();

int main(){
    char* ch, ch2;
   //åpne filer for input/output
    FILE *fptrIn = fopen("hexdec", "r");
    FILE *fptrOut = fopen("toascii", "w");

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
    letterOccurenceCounter();
return 0;
}
int letterOccurenceCounter(){
    char* c;
    int counter[28];
    int tmp, i,character;
    memset(counter,0,sizeof(counter));
    printf("\n");
    FILE *fptrInput = fopen("toascii", "r");
      if(fptrInput == NULL) {
        printf("File Not found");
        exit(1);
    }
    while((c=fgetc(fptrInput))!= EOF){
       tmp = toupper(c);
       tmp = (int)tmp-65;
       if(tmp>=0 && tmp<=28)
            counter[tmp] += 1;
    } 
    
    for(i = 0; i<28; i++){
        character = i;        
        printf("%c = ", character+65);
        printf("%d\n",counter[i]);
    }

  return 0;

} 

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