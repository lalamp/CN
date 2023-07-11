#include <stdio.h>
#include <math.h>

double funcao(double x){ 
    return (exp(40*x) - 500*x -1);
}

double derivada(double x){
    return (40*exp(40*x) - 500);
}

int main(){
    //dados de entrada
    float x; //aproximação inicial da solução 
    printf("\nInforme a aproximacao inicial: ");
    scanf("%f", &x);

    float eps; //precisão/tolerância da solução
    printf("\nInforme a precisao: ");
    scanf("%f", &eps);

    int NMAX; //número máximo de iterações que podem ser feitas
    printf("\nInforme o numero maximo de iteracoes: ");
    scanf("%d", &NMAX);

    //método de Newton
    double xn; //valor de x da iteração n 
    double f; //função de x 
    double df; //derivada da função de x
    int iteracoes = 0; //número de iterações que já foram feitas
    double erro = eps + 1; //erro relativo estimado 

    while(erro > eps && iteracoes < NMAX){
        printf("\n\nIteracao %d \nx (inicial) = %f", iteracoes+1, x);
        f = funcao(x); 
        df = derivada(x); 

        xn = x - (f/df); //fórmula do método de Newton
        printf("\nxn = %f", xn);
        
        erro = (xn - x)/xn;  //cálculo do erro relativo estimado
        if(erro < 0){
            erro = erro*(-1);
        } 
        printf("\nerro = %f", erro);
        
        x = xn; //x recebe uma aproximação melhor do que a inicial/anterior
        iteracoes++;
        printf("\nx (final) = %f", x);
    }

    //saída
    if(iteracoes >= NMAX){
        printf("\n\nO metodo nao convergiu em %d iteracoes", NMAX);
    }
    else{
        printf("\n\nA solucao encontrada foi %f, com precisao de %f, obtida apos %d iteracoes\n\n", x, eps, iteracoes);
    }   
}