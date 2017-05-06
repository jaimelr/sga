#ifndef _sga_h_
#define _sga_h_
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
 * PROBLEMA:
 * Maximizar la función: f(x,y) = 50 - (x - 5)² - (y - 5)²
 * para 0 <= x <= 10 y 0 <= y <= 10
 */

#define GEN_NUM         2
#define BITS_PER_GEN    10
#define POPULATION_SIZE 5
#define CHROMOSOM_SIZE GEN_NUM*BITS_PER_GEN
#define RANGE_MAX       10
#define RANGE_MIN       0
#define RANGE RANGE_MAX-RANGE_MIN

typedef struct {
  unsigned char *chromosom;    // Valor binario
  float         *values;       // Valores decimal de los genes
  unsigned int  *bitsPerGen;   // Vector de bits por gen en el cromosoma
  float         fitness;
} INDIVIDUO;

INDIVIDUO* AllocatePopulation(INDIVIDUO* population);
void InitializePopulation(INDIVIDUO* population);
float* CalculateProbabilities(INDIVIDUO* population);
int BitsToInt(unsigned char *chromosom);
void GenDecodification(INDIVIDUO* population);

//______________________________________________Mutacion
void Mutation(INDIVIDUO* population);


void FreeMemory(INDIVIDUO* population);

// ______________________________________________Development
void PrintChromosom(unsigned char *chromosom);
void PrintPopulation(INDIVIDUO* population);
void PrintValues(INDIVIDUO* population);

#endif
