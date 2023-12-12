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

  // Apply the filter
  for (j = 1; j < height - 1; j++) {
    for (i = 1; i < width - 1; i++) {
      int gx = -input[(j - 1) * width + i + 1] - 2 * input[j * width + i - 1] -
               input[(j + 1) * width + i - 1] + input[(j - 1) * width + i + 1] +
               2 * input[j * width + i + 1] + input[(j + 1) * width + i + 1];
      int gy = -input[(j - 1) * width + i - 1] -
               2 * input[(j - 1) * width + i] - input[(j - 1) * width + i + 1] +
               input[(j + 1) * width + i - 1] + 2 * input[(j + 1) * width + i] +
               input[(j + 1) * width + i + 1];

<<<<<<< HEAD
<<<<<<< HEAD

=======
>>>>>>> Skiable
=======
>>>>>>> 99a005bc47ac597c8fe5fe44559cbe574e79f300
      output[(j-1)*width + i] = fminf(sqrtf(gx * gx + gy * gy), 255);
    }
  }

  // Fill the left and right sides

int test=20;
  for (j = 0; j < height - 2; j++) {
    output[j * width] = 0;
    output[(j + 1) * width - 1] = 0;
  }
}
