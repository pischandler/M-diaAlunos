#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale>

struct arq1{
    int codigo;
    char nome[40];
    float n1, n2, n3, n4;
};

struct arq1 copia;

struct arq2{
    int codigo;
    char nome[40];
    float media;
};

struct arq2 *v, arqaux;

FILE *abrirarquivo(){
    FILE *arquivo1;
    arquivo1 = fopen("alunos.dat","r");
    if(arquivo1 == NULL) {
        printf("falha ao encontrar arquivo.");
        exit(1);
    }
    return arquivo1;
}


double registros(FILE *arquivo1){
    int mais = 0;
    while(!feof(arquivo1)){
        if(fread(&copia,sizeof(copia),1,arquivo1)!=0)
            mais++;
    }
    return mais;
}

void transfere_arquivo(FILE *arquivo1, struct arq2 *v){
    int n = 0;
    rewind(arquivo1);
    while(!feof(arquivo1)){
        if(fread(&copia,sizeof(copia),1,arquivo1)!=0){
         v[n].codigo = copia.codigo;
         strcpy(v[n].nome, copia.nome);
         v[n].media = (copia.n1+copia.n2+copia.n3+copia.n4)/4;
         n++;
        }
    }

}

void alfabetica(struct arq2 *v, int l) {
    int j;
    int i;
    j = l;
    while(j>0){
        for(i=0; i < j-1; i++){
            if(strcmp(v[i].nome, v[i+1].nome) > 0){
                arqaux.codigo = v[i].codigo;
                v[i].codigo = v[i+1].codigo;
                v[i+1].codigo = arqaux.codigo;

                strcpy(arqaux.nome, v[i].nome);
                strcpy(v[i].nome, v[i+1].nome);
                strcpy(v[i+1].nome, arqaux.nome);

                arqaux.media = v[i].media;
                v[i].media = v[i+1].media;
                v[i+1].media = arqaux.media;

            }
        }
        j--;
    }
}

void record(int x, struct arq2 *v){
    FILE *arquivo2;
    int i;
    int s;
    s = 1;
    arquivo2 = fopen("alunos.ord", "ab+");
    if(fread(&arqaux,sizeof(struct arq2), 1, arquivo2) == 0){
        for(i = 0; i < x; i++){
                arqaux.codigo = v[i].codigo;
                strcpy(arqaux.nome, v[i].nome);
                arqaux.media = v[i].media;
                fwrite(&arqaux,sizeof(struct arq2), 1, arquivo2);
        }
        s = 0;
    }

    rewind(arquivo2);

    printf("Universidade Estadual de Ponta Grossa\n");
    printf("Quantidade de alunos: %d", x);
    printf("Média Turma B\n");
    while(!feof(arquivo2)){
        if(fread(&arqaux,sizeof(struct arq2), 1, arquivo2) != 0){
            printf("Nome: %s \n Código: %d \n Média: %.2f \n", arqaux.nome, arqaux.codigo, arqaux.media);
        };
    }
    if(s == 0){
        printf("Arquivo alunos.ord criado. \n");
    }else{
        printf("Arquivo alunos.ord já existe. \n");
    }

    fclose(arquivo2);
}

    int codigo;
    char nome[40];
    float n1, n2, n3, n4;
int main(){
    setlocale(LC_ALL, "");
    FILE *arquivo2;
    struct arq2 *v;
    int f;
    arquivo2 = abrirarquivo();
    f = registros(arquivo2);
    v = (struct arq2*) calloc(f,sizeof(arq2));
    transfere_arquivo(arquivo2, v);
    alfabetica(v, f);
    record(f, v);
    free(v);

    system("pause");
    return 0;
}
