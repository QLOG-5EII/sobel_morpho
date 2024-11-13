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

  // Apply the averaging filter (3x3)
  for (j = 1; j < height - 1; j++) {
    for (i = 1; i < width - 1; i++) {
      // Sum the values of the 3x3 neighborhood
      int sum = 0;
      for (int dj = -1; dj <= 1; dj++) {
        for (int di = -1; di <= 1; di++) {
          sum += input[(j + dj) * width + (i + di)];
        }
      }

      // Compute the average
      output[j * width + i] = sum / 9; // 3x3 filter, so divide by 9
    }
  }

  // Fill the left and right sides with 0 (padding for the borders)
  for (j = 0; j < height; j++) {
    output[j * width] = 0;                  // Left border
    output[j * width + width - 1] = 0;      // Right border
  }

  // Fill the top and bottom sides with 0 (padding for the borders)
  for (i = 0; i < width; i++) {
    output[i] = 0;                          // Top border
    output[(height - 1) * width + i] = 0;   // Bottom border
  }
}
