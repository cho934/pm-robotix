/*
 * ia.c
 *
 *  Created on: 18 Apr 2014
 *      Author: pmx
 */
#include "ia.h"


void Imprimer (int n)
{
	int     aaa[N][N];
    int i, j;

    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j)
            printf ("%4d ", aaa[i][j]);
        printf ("\n");
    }
}





