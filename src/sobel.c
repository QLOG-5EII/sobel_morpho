/*
        ============================================================================
        Name        : sobel.c
        Author      : kdesnos
        Version     : 1.2
        Copyright   : CECILL-C
        Description :
        ============================================================================
*/

#include "sobel.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

void sobel(int width, int height, unsigned char* input, unsigned char* output) {
    int i, j;

    // Apply mean/average filter (3x3 box blur)
    for (j = 1; j < height - 1; j++) {
        for (i = 1; i < width - 1; i++) {
            // Sum all 9 pixels in the 3x3 neighborhood
            int sum = input[(j - 1) * width + (i - 1)] +  // top-left
                      input[(j - 1) * width + i] +        // top-center
                      input[(j - 1) * width + (i + 1)] +  // top-right
                      input[j * width + (i - 1)] +        // middle-left
                      input[j * width + i] +              // center
                      input[j * width + (i + 1)] +        // middle-right
                      input[(j + 1) * width + (i - 1)] +  // bottom-left
                      input[(j + 1) * width + i] +        // bottom-center
                      input[(j + 1) * width + (i + 1)];   // bottom-right

            // Average by dividing by 9
            output[(j - 1) * width + i] = sum / 9;
        }
    }

    // Fill the left and right sides
    for (j = 0; j < height - 2; j++) {
        output[j * width] = 0;
        output[(j + 1) * width - 1] = 0;
    }
}
