#include "sga.h"

/*
 * PROBLEMA:
 * Maximizar la función: f(x,y) = 50 - (x - 5)² - (y - 5)²
 * para 0 <= x <= 10 y 0 <= y <= 10
 */

int main(int argc, char const *argv[]) {
  INDIVIDUO *population;
  char* fathers;
  unsigned int  idGbest = 0;
  float error;
  float* probabilities;
  srand(time(NULL));

  error = 1;
  population = AllocatePopulation(population);
  InitializePopulation(population);
  PrintPopulation(population);
  GenDecodification(population);
  CalculateFitness(population);
  while (error < 100) {
    fathers = RouletteGame(population);
    population = Cross(population, fathers);
    PrintPopulation(population);
    Mutation(population);
    idGbest = SetupBest(population, idGbest);
    GenDecodification(population);
    CalculateFitness(population);
    //PrintValues(population);
    printf("Global best: %f\n", population[idGbest].fitness);
    error++;
  }
  FreeMemory(population);
  free(population);

  return 0;
}
