#include <stdio.h>

int main(){
    FILE *file =  fopen("crossn09.b08", "r");
    FILE *file2 = fopen("cn9", "w");
    int c = 1, otype = 0;

    if(file == NULL){
        printf("No se puede abrir el archivo\n");
        return 0;
    }

    while(!feof(file)){
        
        fread(&otype, 1, 1, file);
        fprintf(file2, "%d: %d\n", c, otype);
        //otype = 1;
        c++;
    }

    return 0;
}
