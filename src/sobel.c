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

#include <stdlib.h>

void sobel(int width, int height, unsigned char *input, unsigned char *output) {
    int i, j;

    // Parcours de l'image sauf les bords
    for (j = 1; j < height - 1; j++) {
        for (i = 1; i < width - 1; i++) {
            unsigned char voisin[9];
            int k = 0;

            // Récupérer les 9 pixels voisins (fenêtre 3x3)
            for (int y = -1; y <= 1; y++) {
                for (int x = -1; x <= 1; x++) {
                    voisin[k++] = input[(j + y) * width + (i + x)];
                }
            }

            // Trier les 9 valeurs pour trouver la médiane
            for (int a = 0; a < 9; a++) {
                for (int b = a + 1; b < 9; b++) {
                    if (voisin[a] > voisin[b]) {
                        unsigned char temp = voisin[a];
                        voisin[a] = voisin[b];
                        voisin[b] = temp;
                    }
                }
            }

            // La médiane est la 5e valeur après tri
            output[j * width + i] = voisin[4];
        }
    }

    // Mettre les bords à 0 (noir)
    for (i = 0; i < width; i++) {
        output[i] = 0;
        output[(height - 1) * width + i] = 0;
    }
    for (j = 0; j < height; j++) {
        output[j * width] = 0;
        output[j * width + (width - 1)] = 0;
    }
}

