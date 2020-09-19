#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

#define abs(val) val>=0?val:val*-1

int **criaMatriz(int nrows, int ncols, FILE *ilha) {
	/* Cria malha de inteiros representando a ilha */
	int i, j;
	int **mat = (int **) malloc((nrows+2)*sizeof(int*));
	if (!mat) {
		printf("--Erro de Alocação--\n");
		return NULL;
	}
	for (i=0; i<nrows+2; i++) {
		mat[i]=(int *) malloc((ncols+2)*sizeof(int));
			if (!mat[i]) {
				printf("--Erro de Alocação--\n");
				return NULL;
			}
	}
	/* Atribui p/ a matriz os dados do arquivo */
	for (i=1; i<nrows+1; i++) {
		for (j=1; j<ncols+1; j++) {
			fscanf(ilha, "%d ", &mat[i][j]);
		}
	}
	return mat;
}

float **concentIlha(int **mat, int nrows, int ncols) {
	/* Cria matriz da ilha poluída - Iteração inicial */
	int i, j;
	float **matPol = (float **) malloc((nrows+2)*sizeof(float*));
	if (!matPol) {
		printf("--Erro de Alocação--\n");
		return NULL;
	}
	for (i=0; i<nrows+2; i++) {
		matPol[i]=(float *) malloc((ncols+2)*sizeof(float));
			if (!matPol[i]) {
				printf("--Erro de Alocação--\n");
				return NULL;
			}
	}
	/* Atribui concentração inicial do poluente */
	for (i=1; i<nrows+1; i++) {
		for (j=1; j<ncols+1; j++) {
			if (mat[i][j] == 2) {
				matPol[i][j] = 100.0;
			}
			if (mat[i][j] == 0 || mat[i][j] == 1) {
				matPol[i][j] = 0.0;
			}
		}
	}
	return matPol;
}

int espalhaIlha(float **matPol, int **mat, int nrows, int ncols) {
	/* Cria matriz de atualização da poluição p/ realizar iterações */
	int i, j;
	float dif=0, maxdif, stp=10e-4;
	float **matTemp = (float **) malloc((nrows+2)*sizeof(float*));
	if (!matTemp) {
		printf("--Erro de Alocação--\n");
		return -1;
	}
	for (i=0; i<nrows+2; i++) {
		matTemp[i]=(float *) malloc((ncols+2)*sizeof(float));
			if (!matTemp[i]) {
				printf("--Erro de Alocação--\n");
				return -1;
			}
	}
	/* Calcula espalhamento */	
	int it = 1;
	do {
		maxdif = 0.f;
		for (i=1; i<nrows+1; i++) {
			for (j=1; j<ncols+1; j++) {
				if (mat[i][j] != 0) {
					printf("\n------ ITERAÇÃO %d ------\n", it);
					matTemp[i][j] = (matPol[i-1][j] + matPol[i+1][j] + matPol[i][j-1] + matPol[i][j+1]) / 4.f;
					imprimeMatriz(matTemp, nrows, ncols);
					dif = abs(matPol[i][j]-matTemp[i][j]);
					printf("\nVariação da [] = %08.5f \n\n", dif);					
					if (dif > maxdif) {	
						maxdif = dif;			
					}
					it++;
				}
			}
		}
		copiaMatriz(matTemp, matPol, nrows, ncols);
		limpaMatriz(matTemp, nrows);
	} while (maxdif > stp);
}

	/* Atualiza matriz de espalhamento */
void copiaMatriz(float **matTemp, float **matPol, int nrows, int ncols) {
	int i, j;
	for (i=0; i<nrows+2; i++) {
		for (j=0; j<ncols+2; j++) {
			matPol[i][j]=matTemp[i][j];
		}
	}
}

	/* Libera memória da matriz de atualização p/ nova iteração ou conclusão do cálculo */
void limpaMatriz(float **matTemp, int nrows) {
	int i;
	for (i=0; i<nrows+2; i++) {
		free(matTemp[i]);
	}
}

	/* Imprime matriz, acompanhamento dos passos de espalhamento */
void imprimeMatriz(float **matTemp, int nrows, int ncols) { 
	int i, j;
	for (i=1; i<nrows+1; i++) {
		for (j=1; j<ncols+1; j++) {
			printf("%08.5f ", matTemp[i][j]);
		}
		printf("\n");
	}
}
