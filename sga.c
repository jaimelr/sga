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
    for(j = 0; j < GEN_NUM; j++) {
      population[i].bitsPerGen[j] = BITS_PER_GEN;
    }
  }
}

//Evaluation
int BitsToInt(unsigned char *chromosom) {
  int i;
  unsigned int IntChromosom = 0;

  for(i = BITS_PER_GEN-1; i >= 0; i--) {
    if(chromosom[i] == 1){
        IntChromosom = IntChromosom + pow(2,BITS_PER_GEN - 1 - i);
        //printf("\n%d\n", IntChromosom);
    }
    //printf("i = %d\n", i);
  }
  return IntChromosom;
}


void GenDecodification(INDIVIDUO* population) {
  //unsigned int i;
  //unsigned int j;
  //unsigned int init;
  //unsigned int IntGen;
  int i;
  int j;
  int init;
  int IntGen;
  int k;

  for(i = 0; i < POPULATION_SIZE; i++) {
    init = 0;
    for(j = 0; j < GEN_NUM; j++) {
      IntGen = 0;
      for (k = init + BITS_PER_GEN - 1; k >= init; k--) {
        if(population[i].chromosom[k] == 1) {
            IntGen = IntGen + pow(2, BITS_PER_GEN - 1 - k + init);
            //printf("\nPotencia = %d\n", BITS_PER_GEN - 1 - k + init);
            //printf("\nK = %d \t\tIntGen = %d\n", k, IntGen);
        }
      }
      population[i].values[j] = ( (IntGen / (pow(2,BITS_PER_GEN) - 1) )*(RANGE) ) + RANGE_MIN;
      init = init + BITS_PER_GEN;
      //printf("\nValue [%d] = %f\n", j, population[i].values[j]);
      //printf("\ninit = %d\n", init);
    }
  }
}


//______________________________________________Development
void PrintChromosom(unsigned char *chromosom) {
  int i;

  for (i = 0; i < CHROMOSOM_SIZE; i++) {
    printf("|%d| ", chromosom[i]);
  }
  printf("\n");
}

void PrintChromosoms(INDIVIDUO* population) {
  int i, j;
  for (i = 0; i < POPULATION_SIZE; i++) {
    printf("\n");
    for (j = 0; j < CHROMOSOM_SIZE; j++) {
      printf("|%d| ", population[i].chromosom[j]);
    }
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
