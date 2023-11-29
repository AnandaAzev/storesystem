#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Produto{
    int codigo;
    char nome[50];
    float valor;
    char status[10];
};

//Função void para fazer a venda de produtos, verificando se este está disponível ou não antes de fazer a venda 

void venda(int cont, struct Produto *estoque) {
    int i, codprod;

    printf("---------------------------------------------\n");
    printf("Codigo  Produto    Preco   Disponibilidade\n");
    printf("---------------------------------------------\n");

    for (i = 0; i < cont; i++) {
        printf("%d %s %.2f %s\n", estoque[i].codigo, estoque[i].nome, estoque[i].valor, estoque[i].status);
    }



    printf("\nDigite o código do produto a ser vendido:\n");
    scanf("%d", &codprod);

    for (i = 0; i < cont; i++) {
        if (estoque[i].codigo == codprod) {
            if (estoque[i].status != "Disponível") {
                printf("O produto com codigo %d ja foi vendido.\n", codprod);
                return;
            } else {
                strcpy(estoque[i].status, "Vendido");
                break;
            }
        }
    }

    FILE *f = fopen("estoque.txt", "w");

    if (f == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (i = 0; i < cont; i++) {
        fprintf(f, "%d %s %.2f %s\n", estoque[i].codigo, estoque[i].nome, estoque[i].valor, estoque[i].status);
    }

    fclose(f);
    printf("Venda realizada com sucesso.\n");

}



//Função void que irá imprimir o conteúdo dp arquivo txt que contém o estoque.
void listar() {

    int codigo;
    char nome[10];
    float valor;
    char status[15];

    FILE *f = fopen("estoque.txt", "r");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("---------------------------------------------\n");
    printf("Codigo  Produto    Preco   Disponibilidade\n");
    printf("---------------------------------------------\n");

    while (fscanf(f,"%d%s%f%s", &codigo, nome, &valor, status)== 4){

          printf("%d  %12s   %8.2f   %13s \n", codigo, nome, valor, status);

        }
    printf("---------------------------------------------\n");
    fclose(f);
}

//Função void que procura o produto pelo seu código e faz a exclusão deste do arquivo txt.
void excluirprod() {
    int cod, codigo;
    char nome[10];
    float valor;
    char status[15];

    FILE *f = fopen("estoque.txt", "r+");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo para leitura e escrita.\n");
        return;
    }

    FILE *temp = fopen("temporario.txt", "w+");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(f);
        return;
    }

    printf("Escreva o código do produto a ser apagado: ");
    scanf("%d", &cod);

    int encontrado = 0;

    while (fscanf(f, "%d%s%f%s", &codigo, nome, &valor, status) == 4) {
        if (cod == codigo) {
            encontrado = 1;
        } else {
            fprintf(temp, "%d %s %.2f %s\n", codigo, nome, valor, status);
        }
    }

    fclose(f);
    fclose(temp);

    if (!encontrado) {
        printf("Produto não encontrado.\n");
    } else {
        remove("estoque.txt");
        rename("temporario.txt", "estoque.txt");
        printf("Produto excluído com sucesso.\n");
    }
}


//Função void que irá adicionar um novo produto ao arquivo txt.
void novoproduto(){
    int codigonov, codigo;
    char nome[10];
    float valor;
    char status[15];

    FILE *f = fopen("estoque.txt", "a+");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo para leitura e escrita.\n");
        return;
    }


    printf("Código do novo produto:\n");
    scanf("%d", &codigonov);

     codigo = 0;

    while(fscanf(f, "%d%s%f%s", &codigo, nome, &valor, status) == 4){
        if (codigo == codigonov){
            printf("Codigo de produto ja existe.");
            return;
        }
    }

    printf("Nome do novo produto:\n");
    scanf("%s", nome);
    printf("Valor do novo produto:\n");
    scanf("%f", &valor);
    strcpy(status, "Disponivel");

    codigo = 0;

    while(fscanf(f, "%d%s%f%s", &codigo, nome, &valor, status) == 4){
        if (codigo == codigonov){
            printf("Codigo de produto ja existe.");
            return;
        }
    }

    fprintf(f, "\n%d %s %.2f %s", codigonov, nome, valor, status);
    fclose(f);
    printf("Produto cadastrado com sucesso.");

}

//Main vai ler opções e chamar as funções corretas
int main() {
    int opcao;
     int i = 0, cont;
    struct Produto estoque[100];
    FILE *f;

    system("color D");


    do {
        printf("\nSandroca Boutique bem-vinda ao sistema comercial!\n");
        printf("\nMenu de tarefas:\n");
        printf("\n1 - Venda.\n");
        printf("2 - Listar Produtos.\n");
        printf("3 - Excluir Produto.\n");
        printf("4 - Cadastrar novo produto.\n");
        printf("5 - Sair.\n");
        printf("Escolha uma opcao:\n");
        scanf("%d", &opcao);

        switch (opcao) {

        case 1:
              f = fopen("estoque.txt", "r");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return 1;
    }

    cont = 0;
    i = 0;

    while (fscanf(f, "%d%s%f%s", &estoque[i].codigo, estoque[i].nome, &estoque[i].valor, estoque[i].status) != EOF) {
        i++;
        cont++;
    }

    fclose(f);

    venda(cont, estoque);
    break;



        case 2:
            listar();
            break;

        case 3:
            excluirprod();
            break;

        case 4:
            novoproduto();
            break;

        case 5:
            printf("Saindo do programa.\n");
            break;

        default:
            printf("Opção inválida. Tente novamente.\n");
            break;
        }
    } while (opcao != 5);

    return 0;
}
