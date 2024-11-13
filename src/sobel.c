/*
        ============================================================================
        Name        : sobel.c
        Author      : kdesnos
        Version     : 1.2
        Copyright   : CECILL-C
        Description :
        ============================================================================
*/

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "sobel.h"

void sobel(int width, int height, unsigned char *input, unsigned char *output) {
int kernel_size = 3;  // Filtre 3x3
int sum, i, j, k, l;

    // Parcourir tous les pixels de l'image
    for (i = 1; i < height - 1; i++) {
        for (j = 1; j < width - 1; j++) {
            sum = 0;
            
            // Appliquer le filtre moyenneur (3x3)
            for (k = -1; k <= 1; k++) {
            	for (l = -1; l <= 1; l++) {
                    sum += input[(i + k) * width + (j + l)];
                }
            }

            // Calculer la moyenne et appliquer au pixel de sortie
            output[i * width + j] = sum / (kernel_size * kernel_size);
        }
    }
  }


