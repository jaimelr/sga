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
    for (j = 0; i < GEN_NUM; i++) {
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


float* CalculateProbabilities(INDIVIDUO* population) {
  int i;
  float fitnessTotal;
  float* probabilities;

  probabilities = (float*)malloc(POPULATION_SIZE*sizeof(float));

  for (i = 0, fitnessTotal = 0; i < POPULATION_SIZE; i++) {
    fitnessTotal += population[i].fitness;
  }

  for (i = 0; i < POPULATION_SIZE; i++) {
    probabilities[i] = population[i].fitness/fitnessTotal;
    probabilities[i] *= 100;
  }

  return probabilities;
}


void Mutation(INDIVIDUO* population) {
  int i;
  int j;
  int randNum;

  for (i = 0; i < POPULATION_SIZE; i++) {
    for (j = 0; j < CHROMOSOM_SIZE; j++) {
      //randNum = 1000*((1.0*rand())/RAND_MAX);
      randNum = rand() % 1000 + 1;
      if(randNum == 1) {
        if(population[i].chromosom[j] == 0) {
          population[i].chromosom[j] = 1;
        }
        else {
          population[i].chromosom[j] = 0;
        }
      }
    }
  }
}

void FreeMemory(INDIVIDUO* population) {
  int i;

  for (i = 0; i < POPULATION_SIZE; i++) {
    free(population[i].chromosom);
    free(population[i].values);
    free(population[i].bitsPerGen);
  }
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
