#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"

int main(void) {
	char arquivo[31]; /* Nome do arq contendo a matriz ilha */
	FILE *ilha; /* Ponteiro para arq de entrada - Ilha */
	int nrows, ncols, i, j; /* Linhas e colunas */
	int **mat; /* Matriz estrutura da ilha */
	float **matPol; /* Matriz de concentração poluente */

	/* Abre arquivo */
	printf("Digite o nome do arquivo de entrada: ");
	scanf("%30s", arquivo);
	ilha = fopen(arquivo, "rt");
	if (!ilha) {
		printf("-- Erro na abertura do arquivo --\n");
		return 0;
	}
	/* Recebe número de linhas e colunas do arquivo para alocação da matriz */
	fscanf(ilha, "%d\n", &nrows);
	fscanf(ilha, "%d\n", &ncols);
	printf("--- Tamanho da Matriz --- \n%d %d\n\n", nrows, ncols); /* Imprime números recebidos */

	/* Cria matriz de inteiro - Estrutura da ilha */
	mat = criaMatriz(nrows, ncols, ilha);
	if (!mat) {
		printf("- Erro na criação da Matriz -\n");
		return 0;
	}
	/* Imprime ilha - Matriz de inteiros */
	printf("--- Estrutura da Ilha -> 0:Água 1:Solo 2:Bomba --- \n");
	for (i=1; i<nrows+1; i++) {
		for (j=1; j<ncols+1; j++) {
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	/* Cria matriz de float - Concentrações do poluente pela ilha */
	matPol = concentIlha(mat, nrows, ncols); 
	if (!matPol) {
		printf("- Erro na criação da Matriz -\n");
		return 0;
	}
	/* Imprime ilha com concentração inicial - Matriz de float */
	printf("--- Arranjo Inicial das Concentrações do Poluente (%%) --- \n");
	for (i=1; i<nrows+1; i++) {
		for (j=1; j<ncols+1; j++) {
			printf("%05.2f ", matPol[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
	printf("--- Início do Espalhamento ---\n");

	/* Calcula espalhamento do poluente */
	espalhaIlha(matPol, mat, nrows, ncols);
	
	/* Libera memória */
	for (i=0; i<nrows+2; i++) {
		free(mat[i]);
	}
	limpaMatriz(matPol, nrows);

	/* Fecha arquivo */
	fclose(ilha);
}
