/*  Eu pensei em fazer um algoritmo que separa-se o calculo do polinomio de modo
    parecido ao que o merge-sort faz, calculando cada vez uma menos parte ate
    chegar em polinomios unarios, mas tal algoritmo faria varias multiplicacoes
    repetidas calculando os x^(n), pois ele não guardaria os valores. Achei melhor
    faze-lo em um loop, para que os valores dos x^(n) possam ser guardados para as
    proximas aplicacoes facilmente, diminuindo o numero de multiplicacoes.*/

int calculapolinomio( int* coef, int* expo, int valor, int tamanho ) {
    int i, j, poli, expovalor;
        
    poli = 0;
    j = tamanho;
    expovalor = 1;
    for( i = 0; i < expo[0]; i++) {
        if ( i == expo[j] ) {
            poli += expovalor*coef[j];
            j--;
        }
        expovalor *= valor;
    }

    return poli;
}
