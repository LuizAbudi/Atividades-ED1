/**
* @file ED20202-AT04-AVLs-LuizGustavoPasiniAbudi.c
* @author Luiz Gustavo Pasini Abudi
* @date 20-08-2021
* @brief Atividade Prática 04 - Manipulação de AVLs

*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

//---------------------------------------------------
// Tipos
//---------------------------------------------------

typedef struct NoAVL *PtrNoAVL;

typedef struct NoAVL
{
    int chave;
    PtrNoAVL dir;
    PtrNoAVL esq;
    //fator de balanceamento
    int altura;
} NoAVL;

//---------------------------------------------------
//                     FUNÇÕES
//---------------------------------------------------

//----------------------------------------------------
//                  INICIA ARVORE
//----------------------------------------------------
void iniciaAVL(PtrNoAVL *node)
{
    *node = NULL;
}

void emOrdem(PtrNoAVL *node)
{
    if ((*node) == NULL)
        return;
    emOrdem(&(*node)->esq);
    printf("%d ", (*node)->chave);
    emOrdem(&(*node)->dir);
}
//---------------------------------------------------
//          VERIFICA SE ESTA VAZIA ARVORE
//---------------------------------------------------

bool estaVaziaAVL(PtrNoAVL *node)
{
    return ((*node) == NULL);
}
//---------------------------------------------------
//              ALTURA ARVORE AVL
//---------------------------------------------------

int alturaArvoreAVL(PtrNoAVL node)
{
    if (node == NULL)
    {
        return 0;
    }
    else
    {
        return ((node)->altura);
    }
}

// -------------------------------
// -------------------------------
int atualizaAltura(PtrNoAVL esq, PtrNoAVL dir)
{

    int AltEsq = alturaArvoreAVL(esq);
    int AltDir = alturaArvoreAVL(dir);

    if (AltEsq > AltDir)
    {
        return (AltEsq + 1);
    }
    else
    {
        return (AltDir + 1);
    }
}
//---------------------------------------------------
//          ROTAÇAO AVL
//---------------------------------------------------

void rotacaoSimplesDireita(PtrNoAVL *node)
{

    PtrNoAVL u = (*node)->esq;
    (*node)->esq = u->dir;
    u->dir = (*node);

    //atualizar a altura dos nÃ³s modificados (node, u)
    (*node)->altura = atualizaAltura((*node)->esq, (*node)->dir);
    u->altura = atualizaAltura(u->esq, u->dir);

    //autualizacao da referencia do node
    (*node) = u;
}
// -------------------------------
// -------------------------------

void rotacaoSimplesEsquerda(PtrNoAVL *node)
{

    PtrNoAVL u = (*node)->dir;
    (*node)->dir = u->esq;
    u->esq = (*node);

    //atualizar a altura dos nÃ³s modificados (node, u)
    (*node)->altura = atualizaAltura((*node)->esq, (*node)->dir);
    u->altura = atualizaAltura(u->esq, u->dir);

    //autualizacao da referencia do node
    (*node) = u;
}
// -------------------------------
// -------------------------------

void rotacaoDuplaEsquerda(PtrNoAVL *node)
{

    PtrNoAVL u, v;
    u = (*node)->dir;
    v = u->esq;

    (*node)->dir = v->esq;
    u->esq = v->dir;
    v->esq = (*node);
    v->dir = u;

    //atualizar a altura dos nÃ³s modificados (node, u, v)
    (*node)->altura = atualizaAltura((*node)->esq, (*node)->dir);
    u->altura = atualizaAltura(u->esq, u->dir);
    v->altura = atualizaAltura(v->esq, v->dir);

    //autualizacao da referencia do node
    (*node) = v;
}
// -------------------------------
// -------------------------------

void rotacaoDuplaDireita(PtrNoAVL *node)
{

    PtrNoAVL u, v;
    u = (*node)->esq;
    v = u->dir;

    (*node)->esq = v->dir;
    u->dir = v->esq;

    v->dir = (*node);
    v->esq = u;

    //atualizar a altura dos nÃ³s modificados (node, u, v)
    (*node)->altura = atualizaAltura((*node)->esq, (*node)->dir);
    u->altura = atualizaAltura(u->esq, u->dir);
    v->altura = atualizaAltura(v->esq, v->dir);

    //autualizacao da referencia do node
    (*node) = v;
}

//---------------------------------------------------
//          APLICA AS ROTAÇOES
//---------------------------------------------------
void AplicarRotacoes(PtrNoAVL *node)
{

    int AltDir = alturaArvoreAVL((*node)->dir);

    int AltEsq = alturaArvoreAVL((*node)->esq);

    // Verificar se é rotacao para direita
    if (AltEsq > AltDir)
    {
        //Variavel para auxiliar -> para esq
        PtrNoAVL temp = (*node)->esq;
        int temp_ad = alturaArvoreAVL(temp->dir);
        int temp_ae = alturaArvoreAVL(temp->esq);
        // temp_ae > ou >= temp_ad
        if (temp_ae >= temp_ad)
        {
            rotacaoSimplesDireita(&(*node));
        }
        else
        {
            rotacaoDuplaDireita(&(*node));
        }
    }
    // Senao é rotacao para esquerda
    else
    { //(ad > ae)
        PtrNoAVL tmp2 = (*node)->dir;
        int tmp2_ad = alturaArvoreAVL(tmp2->dir);
        int tmp2_ae = alturaArvoreAVL(tmp2->esq);
        if (tmp2_ad >= tmp2_ae)
        {
            rotacaoSimplesEsquerda(&(*node));
        }
        else
        {
            rotacaoDuplaEsquerda(&(*node));
        }
    }
}
//---------------------------------------------------
//          INSERIR ARVORE AVL
//---------------------------------------------------
bool InserirAVL(PtrNoAVL *node, int x)
{

    //1. condicao final da recusao (positiva)
    if ((*node) == NULL)
    {
        (*node) = (PtrNoAVL)malloc(sizeof(NoAVL));
        (*node)->dir = (*node)->esq = NULL;
        (*node)->chave = x;
        (*node)->altura = 1;
        return true;
    }

    //2. elemento ja existe
    if ((*node)->chave == x)
        return false;

    bool aux;

    // 3. LaÃ§o de chamadas recusivas
    if (x < (*node)->chave)
    {
        aux = InserirAVL(&(*node)->esq, x);
    }
    else
    {
        aux = InserirAVL(&(*node)->dir, x);
    }

    // 4. Se o auxiliar for falso, nao houve mudança na arvore
    if (aux == false)
        return (false);

    // Se houve modificacao na arvore
    // Precisamos checar o desbalanceamento
    int AltEsq; // altura da sub-arvore da esquerda
    int AltDir; // altura da sub-arvore da direita

    // 5. Calculando as alturas das sub-arvores
    AltEsq = alturaArvoreAVL((*node)->esq);
    AltDir = alturaArvoreAVL((*node)->dir);

    // 6. Verificando desbalanceamento
    if ((AltDir - AltEsq) == +2 || (AltDir - AltEsq) == -2)
    {
        // desbalancemaneto
        AplicarRotacoes(&(*node));
    }

    //7. ajuste da altura do no corrente
    (*node)->altura = atualizaAltura((*node)->esq, (*node)->dir);

    return (true);
}
//---------------------------------------------------
//          PEGAR MAIOR VALOR
//---------------------------------------------------
PtrNoAVL getMaxAux(PtrNoAVL *node)
{

    PtrNoAVL ret;
    // caso base da recursao
    // se filho direita do node == NULL => maior elemento achado
    if ((*node)->dir == NULL)
    {
        ret = (*node);
        (*node) = (*node)->esq;
        return (ret);
    }
    return (getMaxAux(&(*node)->dir));
}
//---------------------------------------------------
//          PEGAR MENOR VALOR
//---------------------------------------------------
PtrNoAVL getMinAux(PtrNoAVL *node)
{

    PtrNoAVL ret;
    // criterio de parada da recursao
    // se filho direita do node == NULL => menor elemento achado
    if ((*node)->esq == NULL)
    {
        ret = (*node);
        // ajuste para remocao funcionar
        // remover o elemento da sub-arvore de node
        (*node) = (*node)->dir;
        return (ret);
    }
    return (getMaxAux(&(*node)->esq));
}

//---------------------------------------------------
//           NIVEL DE DESBALANCIAMENTO
//---------------------------------------------------
void qualNivel(PtrNoAVL *node, int nivel, FILE *arq2)
{
    //caso base da recursao
    if ((*node) == NULL)
        return;
    //caso o nivel seja 1
    if (nivel == 1)
    {
        //recebe a altura da esquerda
        int AltEsq = alturaArvoreAVL((*node)->esq);
        //recebe a altura da direita
        int AltDir = alturaArvoreAVL((*node)->dir);
        //faz a diferença para saber o nivel
        int diferenca = 0;
        diferenca = AltDir - AltEsq;
        //printa no arquivo o nivel da chave
        fprintf(arq2, "%d (%d), ", (*node)->chave, diferenca);
    }
    else if (nivel > 1)
    {
        //se for maior q 1 chama a recursão
        qualNivel(&(*node)->esq, nivel - 1, arq2);
        qualNivel(&(*node)->dir, nivel - 1, arq2);
    }
}
//---------------------------------------------------
//              IMPRIME O NIVEL
//---------------------------------------------------
void imprimeNivel(PtrNoAVL *node, FILE *arq2)
{

    for (int i = 1; i < (1 + (*node)->altura); i++)
    {
        //chama a funçao para saber o nivel e printar no arquivo
        qualNivel(&(*node), i, arq2);
        //quebra a linha no arquivo
        fprintf(arq2, "\n");
    }
}

//---------------------------------------------------
//              REMOVE AVL
//---------------------------------------------------
bool remocaoAVL(PtrNoAVL *node, int valor, char z)

{
    //1.Se o node é nulo
    if ((*node) == NULL)
        return (false);

    //2.se node->chave existe
    if ((*node)->chave == valor)
    {
        PtrNoAVL tmp = (*node);
        //2.1 verifica se é sub-arvore da esquerda
        if ((*node)->esq == NULL)
        {
            (*node) = (*node)->dir;
        }
        //2.2verifica se é sub-arvore da direita
        else if ((*node)->dir == NULL)
        {
            (*node) = (*node)->esq;
        }
        //2.3 Nó intermediario, nem folha nem raiz -> meio
        else
        {
            //verifica se qual operaçao fazer 'e' ou 'd'
            if (z == 'e')
            {
                //se for 'e' pega o maior valor
                tmp = getMaxAux(&(*node)->esq);
            }
            else
            {
                //se for 'd' pega o menor valor
                tmp = getMinAux(&(*node)->dir);
            }
            //node = tmp
            (*node)->chave = tmp->chave;
        }
        free(tmp);
        return (true);
    }
    //variavel T ou F para auxiliar
    bool aux;
    //3. Se valor < node->elemento
    if (valor < (*node)->chave)
    {
        aux = remocaoAVL(&(*node)->esq, valor, z);
    }
    else
    {
        aux = remocaoAVL(&(*node)->dir, valor, z);
    }
    //4.Se o auxiliar for falso, nao houve mudança na arvore
    if (aux == false)
        return (false);

    // 5. Calculando as alturas das sub-arvores
    int AltEsq = alturaArvoreAVL((*node)->esq);
    int AltDir = alturaArvoreAVL((*node)->dir);
    // 6. Verificando desbalanceamento
    if ((AltEsq - AltDir) >= +2 || (AltEsq - AltDir) <= -2)
    {
        AplicarRotacoes(&(*node));
    }
    //7. ajuste da altura do no corrente
    (*node)->altura = atualizaAltura((*node)->dir, (*node)->esq);
    return (true);
}
//---------------------------------------------------
//              DESTROI AVL
//---------------------------------------------------
void destroiAVL(PtrNoAVL *node)
{
    // percurso
    //percorrer a arvore e desalocar memoria de traz p frente
    if ((*node) != NULL)
    {
        destroiAVL(&(*node)->esq);
        destroiAVL(&(*node)->dir);
        free(*node);
        (*node) = NULL;
    }
}

//---------------------------------------------------
//                  MAIN
//---------------------------------------------------
int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "");

    /*printf("Numero de parametros fornecidos: %d\n", argc);

    if (argc != 3)
    {
        printf("Quantidade de parametros invalida\n");
        return 0;
    }

    for (int i = 0; i < argc; i++)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
    }*/

    //abrir os arquivos em modo leitura e escrita
    FILE *entrada = fopen(/*"entrada3.txt"*/ argv[1], "r");
    FILE *saida = fopen(/*"saidateste.txt" */argv[2], "w");

    //Verificar se o arquivo de entrada é válido
    if (entrada == NULL)
    {
        printf("O arquivo de ENTRADA não pode ser aberto corretamente!\n");
        exit(1);
    }
    else
    {
        printf("O arquivo foi aberto com sucesso!\n\n");
    }
    //Verificar se o arquivo de saída é válido
    if (saida == NULL)
    {
        printf("O arquivo de SAÍDA não pode ser criado corretamente!\n\n");
        exit(1);
    }
    else
    {
        printf("O arquivo foi criado com sucesso!\n");
    } //else

    //inicia a arvore
    PtrNoAVL raizAVL;
    iniciaAVL(&raizAVL);
    //variavel tipo da arvore para pegar a chave
    NoAVL x;

    //variaveis para pegar o texto
    char linha1[100];
    char linha2[100];
    int tipoarq;

    //pegando o texto do arquivo de entrada
    fscanf(entrada, "%s\n", linha1);
    //printf("L1:%s\n", linha1);
    fscanf(entrada, "%s\n", linha2);
    //printf("L2:%s\n", linha2);
    //pegando o tipo do arquivo
    tipoarq = getc(entrada);
    printf("TIPO DO ARQ: %c\n", tipoarq);

    //variavel token para quebrar o texto
    char *token = NULL;

    //verifica se o arquivo tem os tipos válidos
    if ((tipoarq == 'e') || (tipoarq == 'd'))
    {
        //quebra as virgulas
        token = strtok(linha1, ",");

        //variavel do num a ser inserido
        int numInsert = 0;

        while (token != NULL)
        {
            //converte os numeros para valores inteiros
            numInsert = atoi(token);
            //passando o valor do numero do arq para a AVL
            x.chave = numInsert;
            //printf("chaves: %d\n", x.chave);
            //inserindo o numero na AVL
            InserirAVL(&raizAVL, x.chave);
            token = strtok(NULL, ",");
        }
        //printando o padrao do arquivo de saida
        fprintf(saida, "[*]antes\n");
        //chamada da funçao para imprimir o nivel da arvore
        imprimeNivel(&raizAVL, saida);

        //variavel do num a ser removido
        int numRemove = 0;

        //variavel token para quebrar o texto
        char *token2 = NULL;
        //quebra as virgulas
        token2 = strtok(linha2, ",");

        while (token2 != NULL)
        {
            //converte os numeros para valores inteiros
            numRemove = atoi(token2);
            //passando o valor do numero do arq para a AVL
            x.chave = numRemove;
            remocaoAVL(&raizAVL, x.chave, tipoarq);
            token2 = strtok(NULL, ",");
        }

        fprintf(saida, "\n[*]depois\n");
        imprimeNivel(&raizAVL, saida);
    }
    else
    {
        //mensagem de erro no arquivo
        fprintf(saida, "Arquivo Inválido");
        destroiAVL(&raizAVL);
        fclose(entrada);
        fclose(saida);
        return 0;       
    }

    destroiAVL(&raizAVL);
    fclose(entrada);
    fclose(saida);

    return 0;
}