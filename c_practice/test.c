#include <stdio.h>
#include <stdlib.h>
FILE * fp;
int main()
{
    char input_txt[100];
    char first_char;
    fp = fopen("text.txt", "r");
    //input_txt[0] = 'H';
    //input_txt[1] = '\n';
    //printf("%s", input_txt);
    first_char = fgetc(fp);
    printf("Tada: %c\n", first_char);
    fgets(input_txt, 100, fp);
    printf("%s", input_txt);
}
