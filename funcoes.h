/* Protótipos das funções do módulo funcoes.c */

int **criaMatriz(int nrows, int ncols, FILE *ilha);

float **concentIlha(int **mat, int nrows, int ncols);

int espalhaIlha(float **matPol, int **mat, int nrows, int ncols);

void copiaMatriz(float **matTemp, float **matPol, int nrows, int ncols);

void limpaMatriz(float **matTemp, int nrows);

void imprimeMatriz(float **matTemp, int nrows, int ncols);
