#include "sga.h"

/*
 * PROBLEMA:
 * Maximizar la función: f(x,y) = 50 - (x - 5)² - (y - 5)²
 * para 0 <= x <= 10 y 0 <= y <= 10
 */

INDIVIDUO* AllocatePopulation(INDIVIDUO* population) {
  int i;

  population = (INDIVIDUO*)malloc(POPULATION_SIZE*sizeof(INDIVIDUO));
  for (i = 0; i < POPULATION_SIZE; i++) {
    population[i].chromosom = (unsigned char*)malloc(GEN_NUM*BITS_PER_GEN*sizeof(unsigned char*));
    population[i].values = (float*)malloc(GEN_NUM*sizeof(float));
    population[i].bitsPerGen = (unsigned int*)malloc(GEN_NUM*sizeof(unsigned int));
  }

  return population;
}

void InitializePopulation(INDIVIDUO* population) {
  int i;
  int j;
  int randNum;

  for (i = 0; i < POPULATION_SIZE; i++) {
    for (j = 0; j < CHROMOSOM_SIZE; j++) {
      randNum = 100*((1.0*rand())/RAND_MAX);
      if(randNum % 2)
        population[i].chromosom[j] = 0;
      else
        population[i].chromosom[j] = 1;
    }
    for (j = 0; j < GEN_NUM; j++) {
      population[i].bitsPerGen[j] = BITS_PER_GEN;
    }
  }
}

int BitsToInt(unsigned char *chromosom) {
  int i;
  unsigned int IntChromosom = 0;

  for(i = BITS_PER_GEN-1; i >= 0; i--) {
    if(chromosom[i] == 1){
        IntChromosom = IntChromosom + pow(2,BITS_PER_GEN - 1 - i);
    }
  }
  return IntChromosom;
}


void GenDecodification(INDIVIDUO* population) {
  int i;
  int j;
  int init;
  int intGen;
  int k;

  for(i = 0; i < POPULATION_SIZE; i++) {
    init = 0;
    for(j = 0; j < GEN_NUM; j++) {
      intGen = 0;
      for (k = init + BITS_PER_GEN - 1; k >= init; k--) {
        if(population[i].chromosom[k] == 1) {
            intGen = intGen + pow(2, BITS_PER_GEN - 1 - k + init);
        }
      }
      population[i].values[j] = ( (intGen / (pow(2,BITS_PER_GEN) - 1) )*(RANGE) ) + RANGE_MIN;
      init = init + BITS_PER_GEN;
    }
  }
}

void CalculateFitness(INDIVIDUO* population)
{
  int i;
  float x;
  float y;

  for (i = 0; i < POPULATION_SIZE; i++)
  {
  	x = population[i].values[0];
    y = population[i].values[1];
  	 population[i].fitness = 50 - (x-5) * (x-5) - (y-5) * (y-5);
     printf("Individuo [%d], fitness = %f\n", i, population[i].fitness);
  }
}


float* CalculateProbabilities(INDIVIDUO* population) {
  int i;
  float fitnessTotal;
  float* probabilities;

  probabilities = (float*)malloc(POPULATION_SIZE*sizeof(float));

  for (i = 0, fitnessTotal = 0; i < POPULATION_SIZE; i++) {
    fitnessTotal += population[i].fitness;
    printf("Fitness Total: %f\n", fitnessTotal);
  }

  for (i = 0; i < POPULATION_SIZE; i++) {
    probabilities[i] = population[i].fitness/fitnessTotal;
    probabilities[i] *= 100;
    printf("\nProbabilidades de Individuo %d:\n", i);
    printf("- %f\n", probabilities[i]);
  }

  return probabilities;
}

char* RouletteGame(INDIVIDUO* population) {
  char father;
  int i;
  float* probabilities;
  char* fathers;

  probabilities = (float*)malloc(POPULATION_SIZE*sizeof(float));
  fathers = (char*)malloc(POPULATION_SIZE*sizeof(char));

  probabilities = CalculateProbabilities(population);

  for (i = 0; i < POPULATION_SIZE; i++) {
    father = PlayRoulette(probabilities);
    PrintFathers(population[father], father);
    *(fathers + i) = father;
  }

  return fathers;
}

char PlayRoulette(float* probabilities) {
  char father;
  int i;
  float randNum;
  float incrementalRange;

  incrementalRange = 0;
  randNum = 100*((1.0*rand())/RAND_MAX);
  for (i = 0; i < POPULATION_SIZE; i++) {
    incrementalRange += probabilities[i];
    if(randNum < incrementalRange) {
      father = i;
      break;
    }
  }

  return father;
}

void Cross(INDIVIDUO father1, INDIVIDUO father2) {

}

//______________________________________________Development
void PrintChromosom(unsigned char *chromosom) {
  int i;

  for (i = 0; i < CHROMOSOM_SIZE; i++) {
    if (i == 10) {
      printf("-- ");
    }
    printf("|%d| ", chromosom[i]);
  }
  printf("\n");
}

void PrintPopulation(INDIVIDUO* population) {
  int i;

  for (i = 0; i < POPULATION_SIZE; i++) {
    printf("Individuo [%d]: ", i);
    PrintChromosom(population[i].chromosom);
    printf("\n");
  }
}

void PrintValues(INDIVIDUO* population) {
  unsigned int i;
  unsigned int j;

  for(i = 0; i < POPULATION_SIZE; i++) {
    for(j = 0; j < GEN_NUM; j++) {
      printf("\nIndividuo [%d] Valor [%d] = %f\n", i, j, population[i].values[j]);
    }
    printf("\n");
  }
}

void PrintFathers(INDIVIDUO father, char index) {
  printf("Father: %d \t", index);
  printf("\n");
}
