/**
* @file ED2021-1-AT03-IndiceRemissivo-LuizGustavoPasiniAbudi.c
* @author Luiz Gustavo Pasini Abudi
* @date 02-08-2021
* @brief Atividade Prática 03 - Manipulação de Arvores

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

//---------------------------------------------------
// Tipos
//---------------------------------------------------

typedef struct NoLista *PtrNoLista;

typedef struct NoLista
{
    //chave para a lista
    int chaveLista;
    //ptr para o proximo elemento da lista
    PtrNoLista proximo;

} NoLista;

typedef struct
{
    //ptr para inicio da lista
    PtrNoLista inicio;
    //tamanho da lista
    int tamanho;

} ListaDinamica;

// NoArvore* PtrNoArvore -> PtrNoArvore* (**NoArvore)
typedef struct NoArvore *PtrNoArvore;

// NoArvore (struct)
typedef struct NoArvore
{
    // elemento da arvore
    char *palavra;
    // ponteiro p filho esquerda
    PtrNoArvore esquerda;
    // ponteiro p filho direita
    PtrNoArvore direita;
    //ponteiro para uma lista da arvore
    ListaDinamica listaArvore;

} NoArvore;

//---------------------------------------------------
//                     FUNÇÕES
//---------------------------------------------------

//----------------------------------------------------
//                  INICIA LISTA
//----------------------------------------------------

void iniciaListaDinamica(ListaDinamica *lista)
{
    //inicio
    lista->inicio = NULL;
    //tamanho
    lista->tamanho = 0;
}

//----------------------------------------------------
//                  LISTA VAZIA
//----------------------------------------------------

bool estaVaziaListaDinamica(ListaDinamica *lista)
{
    return (lista->tamanho == 0);
}

//---------------------------------------------------
//             INSERE ELEMENTOS NA LISTA
//---------------------------------------------------

void inserirListaDinamica(ListaDinamica *lista, int elemento)
{
    //criar o ponteiro
    PtrNoLista novo;
    //alocar a memoria para o novo
    novo = (PtrNoLista)malloc(sizeof(NoLista));
    //copia o valor do elemento para chave do Novo
    novo->chaveLista = elemento;

    //inserçao caso a lista esiver vazia ou se o elemento for menor do que primeiro elemento da lista
    if (estaVaziaListaDinamica(lista) || elemento < lista->inicio->chaveLista)
    {
        //proximo do novo aponta para nulo(inicio)
        novo->proximo = lista->inicio;
        //inicio aponta para o novo no
        lista->inicio = novo;
    }
    else //caso a lista nao esta vazia
    {
        //aux para percorrer a lista
        PtrNoLista aux;
        //aponta para o começo da lista
        aux = lista->inicio;
        //percorrer ate encontrar o ponto de insercao
        while (aux->proximo != NULL && elemento > aux->proximo->chaveLista)
        {
            aux = aux->proximo;
        }
        //proximo Novo aponta proximo aux
        novo->proximo = aux->proximo;
        //proximo do aux aponta para o novo
        aux->proximo = novo;
    }
    //incrementa o contador
    lista->tamanho++;
}

//---------------------------------------------------
//                  IMPRIME LISTA
//---------------------------------------------------

void imprimirListaDinamica(ListaDinamica *lista, FILE *saida)
{
    int x; //variavel para auxiliar
    //printf("Lista = {");

    PtrNoLista percorre;
    //percorre a lista
    for (percorre = lista->inicio; percorre != NULL; percorre = percorre->proximo)
    {
        //condiçao para nao inserir elementos repetidos
        if (x != percorre->chaveLista)
        {
            //printa no arquivo de saida
            fprintf(saida, ",%d", percorre->chaveLista);
            //x recebe o novo valor
            x = percorre->chaveLista;
        }
        //printf("%d ", percorre->chaveLista);
    }
    //quebra a linha no arquivo
    fprintf(saida, "\n");
    //printf("}\n");
}

//---------------------------------------------------
//                 INICIA ARVORE
//---------------------------------------------------

void iniciaArvore(PtrNoArvore *arvore)
{
    (*arvore) = NULL;
}

//---------------------------------------------------
//          VERIFICA SE ESTA VAZIA ARVORE
//---------------------------------------------------

bool estaVaziaArvore(PtrNoArvore *arvore)
{
    return ((*arvore) == NULL);
}

//---------------------------------------------------
//                   INSERÇÃO
//---------------------------------------------------

bool insereArvore(PtrNoArvore *arvore, char *x)
{

    //criterio de parada -> arvore vazia
    if ((*arvore) == NULL)
    {
        //aloca memoria para o no da arvore
        (*arvore) = (PtrNoArvore)malloc(sizeof(NoArvore));
        //a info da arvore recebe o valor a ser inserido
        (*arvore)->palavra = x;
        //strcpy((*arvore)->palavra, x);
        //as folhas recebem NULL
        (*arvore)->direita = (*arvore)->esquerda = NULL;
        //inicia a lista para auxiliar no problema
        iniciaListaDinamica(&(*arvore)->listaArvore);

        return (true);
    }

    // criterio parada fracasso (false)
    //compara o valor a ser inserido com o valor existente na arvore
    if (strcmp((*arvore)->palavra, x) == 0)
    {
        //nao insere e da uma mensagem de erro
        printf("Warning: chave já existente\n");
        return (false);
    }

    // percorrer a arvore (via recursão)
    // valor da arvore > valor x -> recursao p/ esquerda
    if (strcmp((*arvore)->palavra, x) > 0)
    {
        return (insereArvore(&(*arvore)->esquerda, x));
    }
    // valor da arvore < valor x -> recursao p/ direita
    else
    {
        return (insereArvore(&(*arvore)->direita, x));
    }
}

//---------------------------------------------------
//                   PESQUISA
//---------------------------------------------------

bool pesquisaArvore(PtrNoArvore *arvore, char *x, int pag)
{
    // fim de recursão (parada)
    // se eu atingir (*arvore) == NULL -> falso (nao existe)
    if ((*arvore) == NULL)
    {
        return (false);
    }

    // achei o elemento
    // se (*arvore)->x == x -> verdadeiro (existe)
    if (strcmp((*arvore)->palavra, x) == 0)
    {
        //insere valor da pagina na lista
        inserirListaDinamica(&(*arvore)->listaArvore, pag);
        return (true);
    }

    // recursao
    if (strcmp((*arvore)->palavra, x) > 0)
    {

        // valor da arvore > valor x -> recursao p/ esquerda
        return (pesquisaArvore(&(*arvore)->esquerda, x, pag));
    }
    else
    {

        // valor da arvore < valor x -> recursao p/ direita
        return (pesquisaArvore(&(*arvore)->direita, x, pag));
    }
}

//---------------------------------------------------
//                   PERCURSOS
//---------------------------------------------------

// emOrdem
void percursoEmOrdem(PtrNoArvore *arvore, FILE *saida)
{
    if ((*arvore) == NULL)
        return;
    // recursivo no esquerda
    percursoEmOrdem(&(*arvore)->esquerda, saida);
    // imprime o valor da arvore no arquivo
    fprintf(saida, "%s", (*arvore)->palavra);
    //chama a funçao para imprimir o conteudo da lista no arquivo
    imprimirListaDinamica(&(*arvore)->listaArvore, saida);
    // recursivo no direita
    percursoEmOrdem(&(*arvore)->direita, saida);
}

//---------------------------------------------------
//                   DESTRUÇÃO
//---------------------------------------------------

void destroiArvore(PtrNoArvore *arvore)
{
    //percorre a arvore e vai desalocando a memoria
    if ((*arvore) != NULL)
    {
        destroiArvore(&(*arvore)->esquerda);
        destroiArvore(&(*arvore)->direita);
        free(*arvore);
        (*arvore) = NULL;
    }
}

//---------------------------------------------------
//                   MAIN
//---------------------------------------------------

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
    char confere;
    //busca um caracter no arquivo
    confere = fgetc(entrada);
    //se nao encontrar o arq está vazio
    if (confere == EOF)
    {
        printf("\nO arquivo de entrada está VAZIO!\n");
        return 0;
    }
    // se encontar volta o cursor para o inicio do arquivo
    fseek(entrada, 0, SEEK_SET);

    //Verificar se o arquivo de entrada é válido
    if (entrada == NULL)
    {
        printf("\nO arquivo de ENTRADA não pode ser aberto corretamente!\n");
        exit(1);
    }
    else
    {
        printf("\nO arquivo foi aberto com sucesso!\n\n");
    }

    //Verificar se o arquivo de saída é válido
    if (saida == NULL)
    {
        printf("\nO arquivo de SAÍDA não pode ser criado corretamente!\n\n");
        exit(1);
    }
    else
    {
        printf("\nO arquivo foi criado com sucesso!\n");
    } //else

    //uso da arvore na main
    PtrNoArvore raiz;
    // inicializacao da arvore
    iniciaArvore(&raiz);
    //variavel para acessar o no da arvore
    NoArvore x;

    //lista na main
    ListaDinamica lista;
    //iniciando uma lista na main
    iniciaListaDinamica(&lista);

    //iniciando variaveis para pegar o texto do arquivo
    char texto[10000];
    //variaveis para quebrar o testo corretamente
    const char virgula[20] = ">";
    const char virgula2[10] = ",";
    //variavel para armazenar os termos do aquivo
    char termosDef[10000];
    //variavel que armazena o texto quebrado
    char *token;
    char *tokenTermo;

    //variaveis que pegam os indices de cada posiçao da string
    int i = 0;
    int j = -1;
    //variavel para auxiliar na busca de caracter no arquivo
    char c;

    //percorre o arquivo ate achar o fim
    while (!feof(entrada))
    {
        //pega caracter do arquivo
        c = fgetc(entrada);
        //se encontrar um caracter igual a '<'
        if (c == '<')
        {
            //pega o texto do arquivo
            fgets(texto, sizeof(texto), entrada);
            //quebra o texto tirando virgulas, pontos, etc
            token = strtok(texto, virgula);
            //percorre o texto passando todos as letras para minusculo
            for (int i = 0; i < strlen(texto); i++)
            {
                texto[i] = tolower(texto[i]);
            }

            //percorre cada posiçao da string armazenada no texto
            while (i < strlen(texto))
            {
                //se encontrar o ':' incrementa no i e no j
                if (texto[i] == ':')
                {
                    i++;
                    j++;
                }
                //so entra aqui caso tenha encontrado o ':', pois o j é inicializado com -1
                if (j >= 0)
                {
                    //copia o caracter da posiçao i para a veriavel Termos -> que sao os termos do arquivo
                    termosDef[j] = texto[i];
                    //printf("%s\n", termosDef);
                    //incrementa a posiçao do j
                    j++;
                }
                //incrementa a posiçao do i
                i++;
            }
        }
    }
    //printf("%s\n", termosDef);
    //quebra o texto que possui os termos, retirando as virgulas, obtendo as palavras separadas
    tokenTermo = strtok(termosDef, virgula2);
    while (tokenTermo != NULL)
    {
        //copia a palavra para uma variavel do tipo NoArvore
        x.palavra = tokenTermo;
        //printf("%s\n", tokenTermo);
        //a cada palavra encontrada insere ela na arvore
        insereArvore(&raiz, x.palavra);
        //condiçao para ir para a proxima palavra
        tokenTermo = strtok(NULL, virgula2);
    }

    //volta o cursor do arquivo para o começo
    fseek(entrada, 0, SEEK_SET);

    //variavel para pegar o valor das paginas
    int contaPag = 0;
    //variavel que auxilia na quebra do texto
    char *tokenPalavras;
    //variavel que possui os char que serao retirados do texto
    char pontuacao[15] = " >,.!?()\n";

    //
    //i = 0;
    //pega o conteudo da primeira linha do arquivo
    //caso para retirar os termos que ja foram pegos acima
    fgets(texto, sizeof(texto), entrada);
    //percorre o arquivo ate encontrar o fim
    while (!feof(entrada))
    {
        //pega o texto de cada linha do arquivo
        fgets(texto, sizeof(texto), entrada);
        //percorre cada char do arquivo passando ele para minusculo
        for (int i = 0; i < strlen(texto); i++)
        {
            texto[i] = tolower(texto[i]);
        }
        //quebra o texto, retirando as pontuaçoes
        tokenPalavras = strtok(texto, pontuacao);
        while (tokenPalavras != NULL)
        {
            //percorre a string até o fim
            for (int u = 0; u < strlen(texto); u++)
            {
                //se o char da posicao u for '<' -> sinal que achamos uma pagina
                if (texto[u] == '<')
                {
                    //incrementa a pagina
                    contaPag++;
                }
            }
            //printf("%s\n", tokenPalavras);
            //copia a string token(texto sem a pontuaçao) para a texto
            strcpy(texto, tokenPalavras);
            //printf("pagina: %d\n", contaPag);
            //chama a funçao para pesquisar o elemento na arvore
            //caso ja tenha na arvore a funçao insere a pagina dela na lista
            pesquisaArvore(&raiz, texto, contaPag);
            tokenPalavras = strtok(NULL, pontuacao);
        }
    }
    //imprime a arvore no arquivo
    percursoEmOrdem(&raiz, saida);
    //imprime a lista no arquivo
    imprimirListaDinamica(&lista, saida);

    //destroi a arvore e libera a memoria
    destroiArvore(&raiz);
    //fecha os arquivos
    fclose(entrada);
    fclose(saida);
    return 0;
}
