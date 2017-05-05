#include "sga.h"

/*
 * PROBLEMA:
 * Maximizar la función: f(x,y) = 50 - (x - 5)² - (y - 5)²
 * para 0 <= x <= 10 y 0 <= y <= 10
 */

int main(int argc, char const *argv[]) {
  INDIVIDUO *population;
  //int num=0;

  population = AllocatePopulation(population);
  InitializePopulation(population);
  //PrintChromosom(population[0].chromosom);
  PrintChromosoms(population);
  //num=BitsToInt(population[0].chromosom);
  //printf("\n\n%d\n", num);
  GenDecodification(population);
  PrintValues(population);

  return 0;
}
