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
  int i, j;

  // Apply the filter THIS FILTER IS BAD
  /*for (j = 1; j < height - 1; j++) {
    for (i = 1; i < width - 1; i++) {
      int gx = -input[(j - 1) * width + i + 1] - 2 * input[j * width + i - 1] -
               input[(j + 1) * width + i - 1] + input[(j - 1) * width + i + 1] +
               2 * input[j * width + i + 1] + input[(j + 1) * width + i + 1];
      int gy = -input[(j - 1) * width + i - 1] -
               2 * input[(j - 1) * width + i] - input[(j - 1) * width + i + 1] +
               input[(j + 1) * width + i - 1] + 2 * input[(j + 1) * width + i] +
               input[(j + 1) * width + i + 1];

      output[(j-1)*width + i] = fminf(sqrtf(gx * gx + gy * gy), 255);
    }
  }*/
  // My filter is BETTER
  for (j = 1; j < height - 1; j++) {
    for (i = 1; i < width - 1; i++) {
      int sum = 0;
      // Calculer la somme des pixels voisins
      for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
          sum += input[(j + y) * width + (i + x)];
        }
      }
      // Calculer la valeur moyenne
      output[(j-1) * width + i] = sum / 9; // Division par 9 car on additionne 9 pixels
    }
  }

  // Fill the left and right sides
  for (j = 0; j < height - 2; j++) {
    output[j * width] = 0;
    output[(j + 1) * width - 1] = 0;
  }
}
