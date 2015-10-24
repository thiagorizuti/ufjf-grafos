/*
 * ConstrutorGrafo.h
 *
 *  Created on: 09/12/2013
 *      Author: luã
 */

#ifndef CONSTRUTORGRAFO_H_
#define CONSTRUTORGRAFO_H_

#include <stdlib.h>
#include <stdio.h>
#include "MatrizAdjacencia.h"
#include "ListaAdjacencia.h"
#include "buffer.h"


GrafoAdj* IniMatrizAdj(FILE *entrada, int digrafo);
GrafoListAdj* IniListaAdj(FILE *entrada, int digrafo);


#endif /* CONSTRUTORGRAFO_H_ */
