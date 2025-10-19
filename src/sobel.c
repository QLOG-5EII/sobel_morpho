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
            int sum = 0;
            for (int y = -1; y <= 1; y++) {
                for (int x = -1; x <= 1; x++) {
                    sum += input[(j + y) * width + (i + x)];
                }
            }
            output[j * width + i] = sum / 9; // moyenne
        }
    }
    
  // Fill the left and right sides
  for (j = 0; j < height - 2; j++) {
    output[j * width] = 0;
    output[(j + 1) * width - 1] = 0;
  }
  
  for (i = 0; i < width; i++) {
        output[i] = 0;
        output[(height - 1) * width + i] = 0;
    }
}
