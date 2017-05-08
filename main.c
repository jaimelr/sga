#include "sga.h"

/*
 * PROBLEMA:
 * Maximizar la función: f(x,y) = 50 - (x - 5)² - (y - 5)²
 * para 0 <= x <= 10 y 0 <= y <= 10
 */

int main(int argc, char const *argv[]) {
  INDIVIDUO *population;
  float* probabilities;
  srand(time(NULL));

  population = AllocatePopulation(population);
  InitializePopulation(population);
  PrintPopulation(population);
  GenDecodification(population);
  CalculateFitness(population);
  //PrintValues(population);

  printf("\n\nRoulette Game\n");
  RouletteGame(population);

  return 0;
}
