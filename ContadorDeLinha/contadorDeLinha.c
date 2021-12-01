/* Faça um programa que receba do usuario um arquivo texto */
/* e mostre na tela quantas linhas esse arquivo possui.    */

#include <stdio.h>

int main(int argc, char** argv)
{
    FILE *entrada, *saida;
    int c;

    if(argc != 2)
    {
        fprintf(stderr, "Erro na chamada do comando. \n");
        fprintf(stderr, "Uso: %s [ARQUIVO]. \n", argv[0]);
        return 1;
    }

    entrada = fopen(argv[1], "r");
    if(!entrada)
    {
        fprintf(stderr, "Arquivo %s não pode ser aberto para leitura\n", argv[1]);
        return 1;
    }

    //Começa com 1 devido o programa utilizar de “\n” para contar as linhas. Logo a ultima linha não será contada.
    int cont = 1;

    c = fgetc(entrada);
    while (c != EOF)
    {
        if(c == '\n')
        {
            cont++;
        }
        c = fgetc(entrada);
    }

    fclose(entrada);
    printf("\n O documento possui %d linhas! \n", cont);
    return 0;
}
