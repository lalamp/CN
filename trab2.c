#include <stdio.h>
#include <math.h>

#define n 101

int main(){
    //leitura do arquivo
    char arq[100] = "C:/Users/lal4mp/Desktop/USP/CN/trabalho 2/dados.txt";

    FILE *file = fopen(arq, "r"); //abrir o arquivo
    if(file == NULL){
		printf("Falha na leitura do arquivo\n");
		return(1);
	}
    else{
        printf("Arquivo aberto para leitura com sucesso\n\n");
    }
    
    int i[102];
    float t[102], y[102];

    int ind = 0;
    char line[100];
    while(fgets(line, sizeof(line), file) != NULL){ //ler linha por linha do arquivo
        printf("%s", line);

        if(ind != 0){
            sscanf(line, "%d,%f,%f", &i[ind], &t[ind], &y[ind]); //pegar os dados da linha, tranformá-los de string para seus respectivos tipos (int, float) e aramazená-los nos respectivos vetores 
            printf("i[%d] = %d\n", ind, i[ind]);
            printf("t[%d] = %f\n", ind, t[ind]);
            printf("y[%d] = %f\n\n", ind, y[ind]);
        }
        ind++;
    }
 
    fclose(file);

    //ajuste => g1 = 1, g2 = x^2 => g(x) = a + bx^2
    int j;
    float soma1 = 0, soma2 = 0, soma3 = 0, soma4 = 0, soma5 = 0;
    for(j = 1; j <= 102; j++){ 
        soma1 += 1; //<g1, g1> = <1, 1>
        soma2 += 1*pow(t[j], 2); //<g1, g2> = <g2, g1> = <1, x^2>
        soma3 += pow(t[j], 2)*pow(t[j], 2); //<g2, g2> = <x^2, x^2>
        soma4 += 1*y[j]; //<g1, f> = <1, f>
        soma5 += pow(t[j], 2)*y[j]; //<g2, f> = <x^2, f>
    }

    float a, b;
    /* sistema
    a*soma1 + b*soma2 = soma4;
    a*soma2 + b*soma3 = soma5;

    a = (soma4 - b*soma2)/soma1;
    b = (soma5 - ((soma4 - b*soma2)/soma1)*soma2)/soma3;
    */
    b = (soma1*soma5 - soma2*soma4)/(soma1*soma3 - soma2*soma2);
    a = (soma4 - b*soma2)/soma1;
    printf("\n\na = %f\n", a);
    printf("b = %f\n", b);
    printf("g(x) = %f + %f*x^2\n", a, b);
    
    //soma dos resíduos
    float g[101], r[101];
    int p = 0;
    float soma_res = 0;
    for(j = 1; j <= 102; j++){ 
        g[p] = a + b*pow(t[j], 2); //g(x)
        r[p] = y[j] - g[p]; //resíduo => r(x) = f(x) - g(x)
        soma_res += pow(r[p], 2); //soma dos resíduos 
        p++;
    }
    printf("\nsoma dos residuos = %f", soma_res);

    //coeficiente de determinação (R^2 => R)
    float R, soma_y = 0, y_med, SQtot, SQres = soma_res;
    for(j = 1; j <= 102; j++){ 
        soma_y += y[j];
    }
    y_med = (soma_y)/n;

    for(j = 1; j <= 102; j++){ 
        SQtot += pow((y[j]-y_med), 2);
    }

    R = 1.0 - (SQres/SQtot);
    printf("\nR^2 = %f\n\n", R);
    
    return 0;
}