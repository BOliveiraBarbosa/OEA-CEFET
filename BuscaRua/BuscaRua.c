/* Faça um programa que receba do usuario uma palavra */
/* e busque os logradouros no arquivo "cep.dat"       */

#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

int main(char argc, char** argv)
{
    FILE *CEP;
    Endereco e;
    int quant;

    if(argc != 2)
    {
        fprintf(stderr, "USO: %s [CEP]", argv[0]);
        return 1;
    }

    // Se for igual a "300" significa que a estrutura do "Endereco" está OK!
    printf("\n Tamanho da Estrutura: %ld\n\n", sizeof(Endereco));

    CEP = fopen("cep.dat", "rb"); // Leitura em binário
    quant = fread(&e, sizeof(Endereco), 1, CEP);

    int cont = 0, totalRua = 0;
    while (quant > 0)
    {
        cont++;
        e.logradouro[71] = '\0';

        if(strstr(e.logradouro, argv[1]) != NULL )
        {
            printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n", e.logradouro, e.bairro, e.cidade, e.uf, e.sigla, e.cep);
            printf("______________________________________________________________________\n");
            totalRua++;
        }

        /* if(totalRua >= 20)
        {
            break; // Limitar a quantidade de Ruas encontradas 
        } */

        quant = fread(&e, sizeof(Endereco), 1, CEP);
    }

    printf("\n Total de %d ruas com o nome %s, de um total de %d ruas lidas!\n", totalRua, argv[1], cont);
    fclose(CEP);
    return 0;
}
