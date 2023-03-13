/**
* @file ED2021-1-AT01-ConversorD2B-Luiz Gustavo Pasini Abudi.c
* @author Luiz Gustavo Pasini Abudi
* @date 03-07-2021
* @brief Convers�o de decimal para bin�rio com pilhas

*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

#define MAX 50 //Valor maximo da pilha Est�tica

//===============Pilha Estatica===============//

typedef struct{
  int vetorPE[MAX]; //iniciando o tamanho da pilha Est�tica
  int topoPE; //variavel que auxilia na manipula�ao da pilha Est�tica
} pilhaEstatica;

//===============Pilha Din�mica===============//

// NoPilha* -> *PtrNoPilha
typedef struct NoPilha *PtrNoPilhaDinamica;

//NoPilha
typedef struct NoPilha{
  //int x (chave)
  int x;
  //ptr -> proximo
  PtrNoPilhaDinamica proximoPD;
} NoPilhaDinimica;

//Pilha Dinamica
typedef struct{
  //ponteiro para o elemento mais recente
  PtrNoPilhaDinamica topoPD;
  //contagem do nomero de elemetos dentro da pilha
  int qntElementosPD;
} pilhaDinamica;

//===============Fun��es Pilha Din�mica===============//

//Inicializar pilha Din�mica
void iniciaPilhaDinamica(pilhaDinamica *pd){
  //iniciando o ponteiro do topo para nulo
  pd->topoPD = NULL;
  //iniciar o contador para zero
  pd->qntElementosPD = 0;
}//void inicializar pilhaDinamica

int tamanhoPilhaDinamica(pilhaDinamica *pd){
  return(pd->qntElementosPD);
}// fun��o tamanho da pilha Dinamica

bool estaVaziaPilhaDinamica(pilhaDinamica *pd){
  //1. qnt de elementos == 0
  return(pd->qntElementosPD == 0);
}// fun��o estaVazia pilha Dinamica

//inserir elementos
void empilhaPilhaDinamica(pilhaDinamica *pd, int x){
  //1. Inser�ao em pilha vazia

  //criar novo n�, alocar memoria
  PtrNoPilhaDinamica aux;
  aux = (PtrNoPilhaDinamica)malloc(sizeof(NoPilhaDinimica));
  //copiar dado para o novo n�
  aux->x = x;
  //proximo do novo n�, aponta para o topo (nulo)
  aux->proximoPD = pd->topoPD;
  //topo aponta para o novo n�
  pd->topoPD = aux;
  //contador incrementa
  pd->qntElementosPD++;
}//void empilha pilha Dinamica

//remover elementos da pilha
int desempilhaPilhaDinamica(pilhaDinamica *pd){
  int ret = -1;
  //se nao estiver vazia = remover
  if(!estaVaziaPilhaDinamica(pd)){
    //Criar um ptr Auxiliar
    PtrNoPilhaDinamica aux;
    //aux recebe valor do topo
    aux = pd->topoPD;
    //copiar o valor a ser retornado
    ret = aux->x;
    //atualizar os ponteiros
    pd->topoPD = pd->topoPD->proximoPD;
    //desalocar a memoria
    free(aux);
    //decrementa contador
    pd->qntElementosPD--;
  }else{
    printf("N�o foi poss�vel remover\n");
  }//else

  return(ret);
}

//Inser�ao pilha Dinamica
void imprimePilhaDinamica(pilhaDinamica *pd){
  printf("Pilha = {");
  PtrNoPilhaDinamica temp;
  for(temp = pd->topoPD; temp != NULL; temp = temp->proximoPD){
    printf("%d ", temp->x);
  }//for
  printf("}\n");
}//void imprimir pilha Dinamica

//Destruindo a pilha Dinamica
void destroiPilhaDinamica(pilhaDinamica *pd) {
  PtrNoPilhaDinamica remover;
  while(pd->topoPD!= NULL) {
    remover = pd->topoPD;
    pd->topoPD = pd->topoPD->proximoPD;
    free(remover);
  }//while
}//void derstru��o

//transforma decimal para bin�rio
void DecToBinPilhaDinamica(FILE *ArqSaida, int valor){
  int resto;
  pilhaDinamica PilhaAux;

  //iniciando uma pilha adicional
  iniciaPilhaDinamica(&PilhaAux);
  //empilhar caso o valor seja 0
  if(valor == 0){
    empilhaPilhaDinamica(&PilhaAux, 0);
  }
  //criando um loop para dividir por 2 e obter o resto, e empilhando os resultados
  while(valor > 0){
    resto = valor%2;
    empilhaPilhaDinamica(&PilhaAux, resto);
    // printf("-----------%d------------\n", resto);
    // printf("%d\n", PilhaAux.topoPE);
    valor = valor/2;
  }//while
  while(!estaVaziaPilhaDinamica(&PilhaAux)){
    fprintf(ArqSaida, "%d", desempilhaPilhaDinamica(&PilhaAux));
  }//while
  fprintf(ArqSaida, "\n");

}//void Dec2Bin Pilha Est�tica


//===============Fun��es Pilha Est�tica===============//

//iniciando a Pilha Est�tica
void iniciaPilhaEstatica(pilhaEstatica *pe){
  pe->topoPE = 0; //definindo a posi�ao inicial da pilha
}

//tamanho da pilha (valor do topo)
int tamanhoPilhaEstatica(pilhaEstatica *pe){
  return(pe->topoPE);
}

//verifica se a pilha est� vazia
bool estaVaziaPilhaEstatica(pilhaEstatica *pe){
  return(pe->topoPE == 0);
}

//verifica se a pilha est� cheia
bool estaCheiaPilhaEstatica(pilhaEstatica *pe){
  return(pe->topoPE == MAX);
}

//inserindo um valor na pilha estatica
void empilharPilhaEstatica(pilhaEstatica *pe, int valor){
  if(!estaCheiaPilhaEstatica(pe)){
    pe->vetorPE[pe->topoPE] = valor;
    pe->topoPE++;
  }else{
    printf("Aviso: N�o foi poss�vel inserir pois a pilha est� Cheia\n");
  }
}

//imprimindo a Pilha Estatica
void imprimePilhaEstatica(pilhaEstatica *pe){
  printf("Pilha = { ");
  for(int i = 0; i < pe->topoPE; i++){
    printf("|%d| ", pe->vetorPE[i]);
  }
  printf("}\n");
}

//retirando um valor da pilha
int desempilhaPilhaEstatica(pilhaEstatica *pe){
  int x = -1; // valor de controle
  if(!estaVaziaPilhaEstatica(pe)){
    x = pe->vetorPE[pe->topoPE-1];
    pe->topoPE--;
  }else{
    printf("Aviso: A pilha est� Vazia\n");
  }
  return(x);
}// fun��o desempilhar pilha Estatica

//converte decimal para bin�rio
void DecToBinPilhaEstatica(FILE *ArqSaida, int valor){
  int resto;
  pilhaEstatica PilhaAux;

  //iniciando uma pilha adicional
  iniciaPilhaEstatica(&PilhaAux);

  //empilha caso o valor seja 0
  if(valor == 0){
    empilharPilhaEstatica(&PilhaAux, 0);
  }
  //criando um loop para dividir por 2 e obter o resto, e empilhando os resultados
  while(valor > 0){
    resto = valor%2;
    empilharPilhaEstatica(&PilhaAux, resto);
    // printf("-----------%d------------\n", resto);
    // printf("%d\n", PilhaAux.topoPE);
    valor = valor/2;
  }//while

  while(!estaVaziaPilhaEstatica(&PilhaAux)){
    fprintf(ArqSaida, "%d", desempilhaPilhaEstatica(&PilhaAux));
  }//while
  fprintf(ArqSaida, "\n");

}//void Dec2Bin Pilha Est�tica

//=============== MAIN ===============//

int main(int argc, char const *argv[]) {
  setlocale(LC_ALL, "");


  printf("Numero de parametros fornecidos: %d\n", argc);

  if(argc!= 3) {
    printf("Quantidade de parametros invalida\n");
    return 0;
  }

  for(int i = 0; i < argc; i++) {
    printf("argv[%d] = %s\n", i, argv[i]);
  }

  pilhaEstatica MinhaPilhaEstatica;
  pilhaDinamica MinhaPilhaDinamica;

  //iniciando a pilha estatica
  iniciaPilhaEstatica(&MinhaPilhaEstatica);

  //iniciando a pilha dinamica
  iniciaPilhaDinamica(&MinhaPilhaDinamica);

  //abrir os arquivos em modo leitura e escrita
  FILE *entrada = fopen(argv[1], "r");
  FILE *saida   = fopen(argv[2], "w");

  //Verificar se o arquivo de entrada � v�lido
  if(entrada == NULL) {
    printf("O arquivo de ENTRADA n�o pode ser aberto corretamente!\n");
    exit(1);
  }else{
    printf("O arquivo foi aberto com sucesso!\n\n");
  }
  //Verificar se o arquivo de sa�da � v�lido
  if(saida == NULL) {
    printf("O arquivo de SA�DA n�o pode ser criado corretamente!\n\n");
    exit(1);
  }else{
    printf("O arquivo foi criado com sucesso!\n");
  }//else

  char tipoPilha;
  //obter o primeiro caracter do arquivo de entrada
  fscanf(entrada, "%c", &tipoPilha);

  //Condi��o para saber se vai ser usado pilha Est�tica ou Din�mica
  if(tipoPilha == 'e'){
    printf("\nO arquivo iniciado � uma Pilha Est�tica\n");
  }else if(tipoPilha == 'd'){
    printf("\nO arquivo iniciado � uma Pilha Din�mica\n");
  }else{
    printf("\nErro: N�o foi reconhecido o tipo da pilha\n");
    return 0;
  }

  //caso a Pilha seja Estatica
  if(tipoPilha == 'e'){
    int valor;
    //obtendo os valores do arquivo
    while(true){
            //pegando os numeros do arquivo
      fscanf(entrada, "%d", &valor);
      //verificando o final do arquivo
      if(feof(entrada)){
        break;
      }//if
      //condi�ao para empilhar o numero
      if(valor >= 0){
        empilharPilhaEstatica(&MinhaPilhaEstatica, valor);
      }else{
        printf("\n");
        for(int z = 0; z < 80; z++){
          printf("#");
        }
        printf("\n");
        printf("Erro: O valor do n�mero do arquivo n�o � inteiro positivo!\n");
        return 0;
      }//else
    }//while

    //passando os valores da pilha estatica para a convers�o
    while (!estaVaziaPilhaEstatica(&MinhaPilhaEstatica)) {
      int aux;
      aux = desempilhaPilhaEstatica(&MinhaPilhaEstatica);
      DecToBinPilhaEstatica(saida, aux);
    }//while
  }//if

  //caso a Pilha seja Dinamica
  if(tipoPilha == 'd'){
    int valor;
    //obtendo os valores do arquivo
    while(true){
      //pegando os numeros do arquivo
      fscanf(entrada, "%d", &valor);
      //verificando o final do arquivo
      if(feof(entrada)){
        break;
      }
      if(valor >= 0){
        empilhaPilhaDinamica(&MinhaPilhaDinamica, valor);
      }else{
        printf("Erro: O valor do n�mero do arquivo n�o � inteiro positivo\n");
      }//else
    }//while

    //desempilhando item duplicado
    desempilhaPilhaDinamica(&MinhaPilhaDinamica);

    //passando os valores da pilha estatica para a convers�o
    while (!estaVaziaPilhaDinamica(&MinhaPilhaDinamica)) {
      int aux;
      aux = desempilhaPilhaDinamica(&MinhaPilhaDinamica);
      DecToBinPilhaDinamica(saida, aux);
    }
  }//if

  //destruindo a pilha dinamica
  destroiPilhaDinamica(&MinhaPilhaDinamica);

  fclose(entrada);
  fclose(saida);
  // chamar o destrutor da pilha dinamica
  return 0;
}
