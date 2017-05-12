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
    printf("\nVALUES\n");
    printf("x = %f\ty = %f\n", x, y);
  	population[i].fitness = 5000 - 100*(x*x-y)*(x*x-y)+(1-x)*(1-x);
    //printf("Individuo [%d], fitness = %f\n", i, population[i].fitness);
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
    //printf("\nProbabilidades de Individuo %d:\n", i);
    //printf("-> %f\n", probabilities[i]);
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

INDIVIDUO* Cross(INDIVIDUO* population, char* fathers)
{
	int i, j;
  int k;
  int p1;
  int p2;
	float numRand;
	int Px;
  unsigned char *chromosom1;
  unsigned char *chromosom2;
  unsigned char *chromosomAux;
	INDIVIDUO* GenerationNew;


	GenerationNew = AllocatePopulation(GenerationNew);

  for (i = 0; i < POPULATION_SIZE; i+=2) {
    Px = (CHROMOSOM_SIZE - 1)*((1.0*rand())/RAND_MAX) + 1; //calcula el punto de cruza de progenitores
    //printf("Punto de cruce: %d\n", Px);
    numRand = (1.0*rand())/RAND_MAX; //calcula el pc de progenitores
    p1 = *(fathers + i);
    p2 = *(fathers + i+1);
    //PrintFathers(population[p1], p1);
    //PrintFathers(population[p2], p2);
    if(numRand < PC) {
      for (j = 0; j < CHROMOSOM_SIZE; j++) {
        if(j < Px) {//si la interacion esta antes del punto de cruza
          GenerationNew[i].chromosom[j] = population[p1].chromosom[j];//hijo 1 toma el bit del padre 1 primera parte
          GenerationNew[i+1].chromosom[j] = population[p2].chromosom[j];//hijo 2 toma el bit del padre 2
        }
        else {
          GenerationNew[i].chromosom[j] = population[p2].chromosom[j];//hijo 1 toma el bit del padre 2 segunda parte
          GenerationNew[i+1].chromosom[j] = population[p1].chromosom[j];//hijo 2 toma el bit del padre 1
        }
      }
    }
    else {
      for (i = 0; i < POPULATION_SIZE; i+=2) {//si no se cruzan entonces los nuevos hijos son exactamente iguales a los padres
        for (j = 0; j <CHROMOSOM_SIZE ; j++) {
          GenerationNew[i].chromosom[j] = population[p1].chromosom[j];
          GenerationNew[i+1].chromosom[j] = population[p2].chromosom[j];
        }
      }
    }
  }

	return GenerationNew;
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
        printf("MUTANDO...\n");
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

int SetupBest(INDIVIDUO* population, unsigned int idbest) {
	unsigned int i;
	float best;

	best = population[idbest].fitness;
	for(i=0; i < POPULATION_SIZE; i++)
	{
		if (population[i].fitness > best)
		{
			best = population[i].fitness;
		}
	}
  return best;
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
    printf("\nIndividuo [%d]:", i);
    for(j = 0; j < GEN_NUM; j++) {
      printf("\n\tValor [%d] = %f", j, population[i].values[j]);
    }
    printf("\n\tFitness = %f\n", population[i].fitness);
  }
  printf("\n");
}

void PrintFathers(INDIVIDUO father, char index) {
  printf("Father: %d \t", index);
  printf("\n");
}
