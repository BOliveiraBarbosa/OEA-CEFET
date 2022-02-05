#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct _sinasc sinasc;

struct _sinasc {
    char CODMUNNASC[6]; /* Código do Município de Nascimento */
    char CODESTAB[7]; /* Código do Estabelecimento */
    char CODMUNRES[6]; /* Código do Município de Residência */
    char DTNASC[8]; /* Data de Nascimento no formato DDMMAAAA */
    char SEMAGESTAC[2]; /* Número de Semanas de Gestação */
    char SEXO[1]; /* Sexo 0 não informado, 1 Masculino ou 2 Feminino */
    char PESO[4]; /* Peso em gramas */
    char DTNASCMAE[8]; /* Data de Nascimento no formato DDMMAAAA */
};

int compara(const void *s1, const void *s2)
{
	return strncmp(((sinasc*)s1)->CODESTAB, ((sinasc*)s2)->CODESTAB, 7);
}

int acha_nascimento_capital(FILE*);         //Questão 04
void nascimento_menina_santos(FILE*);       //Questão 05
void nascimento_baixo_peso_campinas(FILE*); //Questão 06
void ordenacao_comparacao(FILE*, long);     //Questão 07
int nascimento_por_estabelecimento();       //Questão 08

int main(int argc, char**argv) {
    FILE *f;
    sinasc s;
    long tamanho_arquivo, tamanho_arquivo_registro, tamanho_estrutura;

    setlocale(LC_ALL, "Portuguese");

    f = fopen("sinasc-sp-2018.dat", "rb");

    if(!f) {
        fprintf(stderr, "Arquivo não pode ser aberto para leitura\n");
        return 1;
    }

    fseek(f, 0, SEEK_END);
    tamanho_arquivo = ftell(f);
    rewind(f);

    tamanho_estrutura = sizeof(sinasc);
    tamanho_arquivo_registro = tamanho_arquivo / tamanho_estrutura;

    printf("Tamanho do Arquivo: %ld \n", tamanho_arquivo);
    printf("Tamanho da Estrutura: %ld \n", tamanho_estrutura);
    printf("Tamanho do Arquivo em Registros: %ld \n", tamanho_arquivo_registro);

    acha_nascimento_capital(f);                        //Questão 04
    //nascimento_menina_santos(f);                       //Questão 05
    //nascimento_baixo_peso_campinas(f);                 //Questão 06
    //ordenacao_comparacao(f, tamanho_arquivo_registro); //Questão 07
    //nascimento_por_estabelecimento();                  //Questão 08
    
    fclose(f);
    system("pause");
    return 0;
}

int acha_nascimento_capital(FILE* f) {
    sinasc s;
    FILE *saida;
    long qtd, cont = 0;

    saida = fopen("sinasc-sp-capital-2018.dat", "wb");
    if(!saida)
    {
        fprintf(stderr, "Arquivo %s não pode ser aberto para escrita\n", saida);
        return 1;
    }

    qtd = fread(&s, sizeof(sinasc), 1, f);
    while (qtd > 0) {

        if(strncmp("355030", s.CODMUNNASC, 6) == 0) {
            fwrite(&s, sizeof(sinasc), 1, saida);
            cont ++;
        }

        qtd = fread(&s, sizeof(sinasc), 1, f);
    }

    printf("Tamanho em Registros do Novo Arquivo: %ld \n", cont);
    fclose(saida);
}

void nascimento_menina_santos(FILE* f) {
    sinasc s;
    long qtd, cont = 0;

    qtd = fread(&s, sizeof(sinasc), 1, f);
    while (qtd > 0) {
        if(strncmp("354850", s.CODMUNNASC, 6) == 0 && strncmp("2", s.SEXO, 1) == 0){
            cont ++;
        }

        qtd = fread(&s, sizeof(sinasc), 1, f);
    }

    printf("A quantidade de meninas que nasceram em Santos: %ld \n", cont);
}

void nascimento_baixo_peso_campinas(FILE* f) {
    sinasc s;
    long qtd, cont = 0;

    qtd = fread(&s, sizeof(sinasc), 1, f);
    while (qtd > 0) {
        if(strncmp("350950", s.CODMUNNASC, 6) == 0 && strncmp("2500", s.PESO, 4) > 0){
            cont ++;
        }

        qtd = fread(&s, sizeof(sinasc), 1, f);
    }

    printf("A quantidade de bebês que nasceram abaixo do peso em Campinas: %ld \n", cont);
}

void ordenacao_comparacao(FILE* f, long qtd) {
    sinasc *s;
    FILE *saida;
    s = (sinasc*) malloc(qtd * sizeof(sinasc));

    if(fread(s, sizeof(sinasc), qtd, f) == qtd)
	{
		printf("Lido = OK\n");
	}

    qsort(s,qtd,sizeof(sinasc),compara);
	printf("Ordenado = OK\n");

    saida = fopen("sinasc-sp-2018-ordenado.dat","wb");
	fwrite(s, sizeof(sinasc), qtd,saida);
	fclose(saida);
    printf("Escrito = OK\n");
	free(s);
}

int nascimento_por_estabelecimento() {
    FILE *g;
    sinasc s;
    long qtd, cont = 0, cont_estab = 0;
    char antigo[7];

    g = fopen("sinasc-sp-2018-ordenado.dat", "rb");
    
    if(!g) {
        fprintf(stderr, "Arquivo não pode ser aberto para leitura\n");
        return 1;
    }

    qtd = fread(&s, sizeof(sinasc), 1, g);

    while (qtd > 0) {
       if(strncmp(antigo, s.CODESTAB, 7) == 0){
            cont++;
       } else{
            printf("O número de nascimentos no estabelecimento %.7s: %ld \n", antigo, cont);
            cont_estab++;
            cont = 1;
       }

        strcpy(antigo, s.CODESTAB);
        qtd = fread(&s, sizeof(sinasc), 1, g);
    }
    printf("O total de estabelecimentos: %ld \n", cont_estab);

    fclose(g);
}