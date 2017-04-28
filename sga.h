#ifndef _sga_h_
#define _sga_h_
#include <stdio.h>

/*
 * PROBLEMA:
 * Maximizar la función: f(x,y) = 50 - (x - 5)² - (y - 5)²
 * para 0 <= x <= 10 y 0 <= y <= 10
 */

#define GEN_NUM         2
#define BITS_PER_GEN    10
#define POPULATION_SIZE 5

typedef struct {
  unsigned char *chromosom;   // Valor binario
  float         *value;       // Valor decimal
  unsigned int  *bitPerGen;   // Resolución de la solución.
  float         fitness;
} INDIVIDUO;

void InitializePopulation(INDIVIDUO* population);

#endif _sga_h_
