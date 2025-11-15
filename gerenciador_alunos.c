#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 100
#define ARQUIVO "alunos.dat"

typedef struct {
    char nome[MAX_NOME];
    int matricula;
    float nota;
} Aluno;

void limpaBuffer();
int tamanho();
void cadastrar();
void consultar();
void menu();

int main() {
    FILE *file = fopen(ARQUIVO, "r+b");
    if (file == NULL) {
        file = fopen(ARQUIVO, "w+b");
        if (file == NULL) {
            printf("Erro ao criar o arquivo!\n");
            return 1;
        }
    }
    fclose(file);
    
    menu();
    return 0;
}

void limpaBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int tamanho() {
    FILE *file = fopen(ARQUIVO, "rb");
    if (file == NULL) return 0;
    
    fseek(file, 0, SEEK_END);
    long bytes = ftell(file);
    fclose(file);
    
    return bytes / sizeof(Aluno);
}

void cadastrar() {
    FILE *file = fopen(ARQUIVO, "ab");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    
    Aluno aluno;
    
    printf("\n=== CADASTRO DE ALUNO ===\n");
    
    printf("Nome: ");
    fgets(aluno.nome, MAX_NOME, stdin);
    aluno.nome[strcspn(aluno.nome, "\n")] = '\0';
    
    printf("Matrícula: ");
    scanf("%d", &aluno.matricula);
    
    printf("Nota: ");
    scanf("%f", &aluno.nota);
    
    limpaBuffer();
    
    fwrite(&aluno, sizeof(Aluno), 1, file);
    fclose(file);
    
    printf("Aluno cadastrado com sucesso!\n");
}

void consultar() {
    int total = tamanho();
    if (total == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }
    
    int posicao;
    printf("\nTotal de alunos cadastrados: %d\n", total);
    printf("Digite a posição do aluno que deseja consultar (1 a %d): ", total);
    scanf("%d", &posicao);
    limpaBuffer();
    
    if (posicao < 1 || posicao > total) {
        printf("Posição inválida!\n");
        return;
    }
    
    FILE *file = fopen(ARQUIVO, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    
    Aluno aluno;
    fseek(file, (posicao - 1) * sizeof(Aluno), SEEK_SET);
    fread(&aluno, sizeof(Aluno), 1, file);
    fclose(file);
    
    printf("\n=== ALUNO ENCONTRADO ===\n");
    printf("Posição: %d\n", posicao);
    printf("Nome: %s\n", aluno.nome);
    printf("Matrícula: %d\n", aluno.matricula);
    printf("Nota: %.2f\n", aluno.nota);
}

void menu() {
    int opcao;
    
    do {
        printf("\n=== SISTEMA DE GERENCIAMENTO DE NOTAS ===\n");
        printf("1. Cadastrar aluno\n");
        printf("2. Consultar aluno\n");
        printf("3. Ver total de alunos\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limpaBuffer();
        
        switch (opcao) {
            case 1:
                cadastrar();
                break;
            case 2:
                consultar();
                break;
            case 3:
                printf("\nTotal de alunos cadastrados: %d\n", tamanho());
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}