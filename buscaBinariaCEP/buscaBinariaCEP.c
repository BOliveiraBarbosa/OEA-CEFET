#include <stdio.h>
#include <stdlib.h>
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

int buscaBinaria (FILE*, char**, long, long);

int main( int argc, char**argv)
{
    FILE *f;
    Endereco e;
    long fim, tamanhoArquivo;

    if(argc != 2){
        fprintf(stderr, "USO, %s [CEP]", argv[0]);
        return -1;
    }

    f = fopen("cep_ordenado.dat", "r");
    fseek(f, 0, SEEK_END);
    tamanhoArquivo = ftell(f);
    rewind(f);

    printf("Tamanho do Arquivo: %ld \n", tamanhoArquivo);
    printf("Tamanho da Estrutura: %ld \n", sizeof(Endereco));
    printf("Tamanho do Arquivo em Registros: %ld \n", tamanhoArquivo/sizeof(Endereco));

    fim = (tamanhoArquivo / sizeof(Endereco)) - 1;
    
    buscaBinaria(f, argv, 0, fim);

    fclose(f);
    return 0;
}

int buscaBinaria (FILE *f, char**argv, long inicio, long fim)
{
    Endereco e;
    long meio, i = 0;

    while (inicio <= fim)
    {
        i++;
        meio = (inicio + fim) / 2;

        fseek(f, meio * sizeof(Endereco), SEEK_SET);
        fread(&e, sizeof(Endereco), 1, f);

        if(strncmp(argv[1], e.cep, 8)==0)
		{
			
            printf("\n%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
            printf("O numero de CEPs verificados foi: %ld \n", i);
            return 0;
            
		} else {
            if(strncmp(argv[1], e.cep, 8) > 0)
            {
                inicio = meio + 1;
            }
             else
            {
                if(strncmp(argv[1], e.cep, 8) < 0)
                {
                    fim = meio - 1;
                }
            }
        }
    }
    
    printf("\n O CEP nao foi encontrado!");
    printf("O numero de CEPs verificados foi: %ld \n", i);
    return 0;
}