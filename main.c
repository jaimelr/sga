#include "sga.h"

/*
 * PROBLEMA:
 * Maximizar la función: f(x,y) = 50 - (x - 5)² - (y - 5)²
 * para 0 <= x <= 10 y 0 <= y <= 10
 */

int main(int argc, char const *argv[]) {
  INDIVIDUO *population;
  float* probabilities;

  population = AllocatePopulation(population);
  InitializePopulation(population);
  PrintPopulation(population);
  GenDecodification(population);
  PrintValues(population);

  Mutation(population);
  PrintPopulation(population);

  FreeMemory(population);
  free(population);

  return 0;
}
