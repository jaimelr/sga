#include "sga.h"

/*
 * PROBLEMA:
 * Maximizar la función: f(x,y) = 50 - (x - 5)² - (y - 5)²
 * para 0 <= x <= 10 y 0 <= y <= 10
 */

void InitializePopulation(INDIVIDUO* population) {
  int i;

  population = (INDIVIDUO*)malloc(POPULATION_SIZE*sizeof(INDIVIDUO))
  for (i = 0; i < POPULATION_SIZE; i++) {
    population[i]->chromosom = (unsigned char*)malloc(GEN_NUM*BITS_PER_GEN*sizeof(unsigned char*));
    population[i]->values = (float*)malloc(GEN_NUM*sizeof(float));
    population[i]->bitsPerGen = (unsigned int*)malloc(GEN_NUM*sizeof(unsigned int));
  }

}
