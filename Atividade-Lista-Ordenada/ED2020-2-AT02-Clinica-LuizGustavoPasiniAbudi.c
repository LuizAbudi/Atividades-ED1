/**
* @file ED2020-2-AT02-Clinica-LuizGustavoPasiniAbudi.c
* @author Luiz Gustavo Pasini Abudi
* @date 14-07-2021
* @brief Atividade Prática 02 - Manipulação de Listas

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

//Tamanho da string para pegar os valores no arquivo
#define MAX 200

//--------------------------------------------------------------------------------------------------

typedef struct
{
    int chave;       //identificaçao
    char dados[MAX]; //dados do arquivo

} Objeto;

typedef struct NoLista *PtrNoLista;

typedef struct NoLista
{
    Objeto obj;
    PtrNoLista proximo;
    PtrNoLista anterior;

} NoLista;

typedef struct
{
    PtrNoLista inicio;
    int tamanho;

} ListaDupla;

//--------------------------------------------------------------------------------------------------
//                                       INICIA LISTA
//--------------------------------------------------------------------------------------------------

void iniciaListaDupla(ListaDupla *lista)
{
    lista->inicio = NULL;
    lista->tamanho = 0;
}

//--------------------------------------------------------------------------------------------------
//                                       LISTA VAZIA
//--------------------------------------------------------------------------------------------------

bool estaVaziaLista(ListaDupla *lista)
{
    //verifica se o ptr está apontado para NULL
    if (lista->inicio == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------------------------------------------
//                                   INSERIR ELEMENTOS NA LISTA
//--------------------------------------------------------------------------------------------------

bool inserir(ListaDupla *lista, Objeto x)
{
    //cria uma nova lista
    PtrNoLista novo;
    //aloca memoria do novo
    novo = (PtrNoLista)malloc(sizeof(NoLista));
    //copia o valor do elemento para chave do Novo
    novo->obj = x;
    //cria uma lista auxiliar
    PtrNoLista aux;

    //verifica se a lista esta vazia
    // insere no começo se a lista esta vazia
    // ou é menor que o primeiro elemento
    if (estaVaziaLista(lista) == true)
    {
        novo->proximo = NULL;
        novo->anterior = NULL;
        lista->inicio = novo;
    }
    else if (x.chave < lista->inicio->obj.chave)
    {

        novo->anterior = NULL;
        lista->inicio->anterior = novo;
        novo->proximo = lista->inicio;
        lista->inicio = novo;
    }
    else
    {
        aux = lista->inicio;
        //percorre para achar a posiçao de inserçao
        while (aux->proximo != NULL && x.chave > aux->proximo->obj.chave)
        {
            aux = aux->proximo;
        }

        novo->proximo = aux->proximo;
        if (aux->proximo != NULL)
        {
            aux->proximo->anterior = novo;
        }
        novo->anterior = aux;
        aux->proximo = novo;
    }
    lista->tamanho++;
    return (true);
}

//--------------------------------------------------------------------------------------------------
//                                         IMPRIME LISTA
//--------------------------------------------------------------------------------------------------

void imprimirLista(ListaDupla *lista)
{
    //verifica se a lista esta vazia
    if (estaVaziaLista(lista) == true)
    {
        printf("A Lista está vazia");
    }
    else
    {
        //inicia aux para percorrer a lista
        PtrNoLista aux;
        //percorre a lista imprimindo os valores
        for (aux = lista->inicio; aux != NULL; aux = aux->proximo)
        {
            printf("{%d %s\n", aux->obj.chave, aux->obj.dados);
        }
    }
}

//--------------------------------------------------------------------------------------------------
//                                        IMPRIME REVERSO
//--------------------------------------------------------------------------------------------------

void imprimirReverso(ListaDupla *lista)
{
    //verifica se a lista esta vazia
    if (estaVaziaLista(lista) == true)
    {
        printf("A Lista está vazia");
    }
    else
    {
        //inicia aux para percorrer a lista
        PtrNoLista aux;
        aux = lista->inicio;

        //"caminho de ida"
        while (aux->proximo != NULL)
        {
            aux = aux->proximo;
        }
        printf("{");

        //"caminho de volta"
        while (aux->anterior != NULL)
        {
            printf("%d ", aux->obj.chave);
            aux = aux->anterior;
        }
        printf("%d", aux->obj.chave);
        printf("}\n");
    }
}

//--------------------------------------------------------------------------------------------------
//                                         PESQUISA NA LISTA
//--------------------------------------------------------------------------------------------------

void pesquisar(ListaDupla *lista, int x, FILE *arqsaida)
{
    //verifica se a lista esta vazia
    if (estaVaziaLista(lista) == true)
    {
        printf("Não possui elementos na lista");
    }
    //inicia aux para percorrer a lista
    PtrNoLista aux;
    aux = lista->inicio;
    while (aux != NULL && x > aux->obj.chave)
    {
        aux = aux->proximo;
    }
    //condiçao de parada (achou ou nao o objeto)
    if (aux == NULL || aux->obj.chave > x)
    {
        printf("O elemento não foi encontrado na lista!\n");
    }
    else
    {
        //imprime o objeto encontrado no arquivo
        fprintf(arqsaida, "{%d, %s", aux->obj.chave, aux->obj.dados);
    }
}

//--------------------------------------------------------------------------------------------------
//                                      TAMANHO DA LISTA
//--------------------------------------------------------------------------------------------------

int tamanhoLista(ListaDupla *lista)
{
    return (lista->tamanho);
}

//--------------------------------------------------------------------------------------------------
//                                         DESTROI LISTA
//--------------------------------------------------------------------------------------------------

bool destruirLista(ListaDupla *list)
{
    //inicia listas auxiliares
    PtrNoLista aux;
    PtrNoLista aux2;
    //verifica se a lista esta vazia
    if (estaVaziaLista(list) == true)
    {
        return false;
    }
    else
    {
        aux2 = list->inicio;
        while (aux2 != NULL)
        {
            aux = aux2;
            aux2 = aux2->proximo;
            free(aux);
            list->tamanho--;
        }
        printf("LISTA DESTRUIDA");
    }
}

//--------------------------------------------------------------------------------------------------
//                                      IMPRIME NO ARQUIVO
//--------------------------------------------------------------------------------------------------

void imprimirArq(ListaDupla *lista, FILE *arqsaida)
{
    //verifica se a lista esta vazia
    if (estaVaziaLista(lista) == true)
    {
        printf("A Lista está vazia");
    }
    else
    {
        //inicia aux para percorrer a lista
        PtrNoLista aux;
        //printf("{");
        //percorre a lista imprimindo os valores
        for (aux = lista->inicio; aux != NULL; aux = aux->proximo)
        {
            //imprime o conteudo da lista direto no arquivo
            fprintf(arqsaida, "{%d %s\n", aux->obj.chave, aux->obj.dados);
        }
        //printf("}\n");
    }
}

//--------------------------------------------------------------------------------------------------
//                                     IMPRIME REVERSO NO ARQUIVO
//--------------------------------------------------------------------------------------------------

void imprimirReversonoArq(ListaDupla *lista, FILE *arqsaida)
{
    //verifica se a lista esta vazia
    if (estaVaziaLista(lista) == true)
    {
        printf("A Lista está vazia");
    }
    else
    {
        //inicia aux para percorrer a lista
        PtrNoLista aux;
        aux = lista->inicio;

        //"caminho de ida" - percorre até chegar no ultimo elemento
        while (aux->proximo != NULL)
        {
            aux = aux->proximo;
        }

        //"caminho de volta"
        while (aux != NULL)
        {
            //imprime o conteudo da lista direto no arquivo
            fprintf(arqsaida, "{%d, %s\n", aux->obj.chave, aux->obj.dados);
            aux = aux->anterior;
        }

    } //else
}

//--------------------------------------------------------------------------------------------------
//                                          MAIN
//--------------------------------------------------------------------------------------------------

int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "");

    printf("Numero de parametros fornecidos: %d\n", argc);

    if (argc != 3)
    {
        printf("Quantidade de parametros invalida\n");
        return 0;
    }

    for (int i = 0; i < argc; i++)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    //abrir os arquivos em modo leitura e escrita
    FILE *entrada = fopen(argv[1], "r");
    FILE *saida = fopen(argv[2], "w");

    //Verificar se o arquivo de entrada é válido
    if (entrada == NULL)
    {
        printf("O arquivo de ENTRADA não pode ser aberto corretamente!\n");
        exit(1);
    }
    else
    {
        printf("O arquivo de entrada foi aberto com sucesso!\n");
    }
    //Verificar se o arquivo de saída é válido
    if (saida == NULL)
    {
        printf("O arquivo de SAÍDA não pode ser criado corretamente!\n");
        exit(1);
    }
    else
    {
        printf("O arquivo de saida foi criado com sucesso!\n");
    } //else

    ListaDupla lista;
    Objeto cadastro;

    //------INICIA A LISTA-----------------------------------------------------
    iniciaListaDupla(&lista);

    char c;
    char tipoArq;
    int auxPesquisa = 0;

    //loop para ler o arquivo ate o fim
    while (feof(entrada) == 0)
    {
        //pega o primeiro char do arquivo
        c = fgetc(entrada);
        //verifica se o char pego é uma chave (padrao do arquivo)
        if (c == '{')
        {
            //se tiver '{' -> pegar o ID (chave) e o restante da linha como string
            fscanf(entrada, "%d,%[^\n]\n", &cadastro.chave, cadastro.dados);
            //printf("{%d,%s\n", cadastro.chave, cadastro.dados);

            //INSERE NA LISTA
            inserir(&lista, cadastro);
        } //if
        else
        {
            //se não encontrar a '{' pegar o char da linha e comparar com 1, 2 e 3
            if (c == '1' || c == '2' || c == '3')
            {
                tipoArq = c;
                printf("Tipo arquivo: %c\n", tipoArq);
            }

            //Caso for 3, pegar o proximo char
            if (tipoArq == '3')
            {
                fscanf(entrada, "%d", &auxPesquisa);
                printf("Aux de pesquisa= %d\n", auxPesquisa);
            }

        } //else
    }     //while

    //printf("####################\n");
    //imprimirLista(&lista);

    switch (tipoArq)
    {
    //caso o numero do fim do arquivo for 1
    case '1':
        imprimirArq(&lista, saida);
        printf("SUCESSO!!\n");
        break;

    //caso o numero do fim do arquivo for 2
    case '2':
        //colocar o conteúdo da lista no arquivo ao contrario
        imprimirReversonoArq(&lista, saida);
        printf("SUCESSO!!\n");
        break;

    //caso o numero do fim do arquivo for 3
    case '3':
        //pesquisar na lista a chave, e imprime no arquivo
        pesquisar(&lista, auxPesquisa, saida);
        printf("SUCESSO!!\n");
        break;

    //caso de erro!
    default:
        printf("ERRO! Tipo de implementação não reconhecido!\n");
        break;
    } //switch case

    destruirLista(&lista);
    fclose(entrada);
    fclose(saida);
    return 0;
} //main
