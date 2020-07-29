#include <stdio.h>

int main(){
    FILE *data;
    FILE *outData;

    data = fopen("data.txt", "r");
    outData = fopen("priors.dat", "wb");
    float value;
    while((fscanf(data, "%f", &value)) != EOF){
        fwrite(&value, sizeof(float), 1, outData);
    }

    fclose(data);
    fclose(outData);
    printf("Finish");
}