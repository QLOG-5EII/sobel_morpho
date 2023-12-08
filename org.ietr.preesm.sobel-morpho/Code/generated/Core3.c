/**
 * @file Core3.c
 * @generated by CPrinter
 * @date Fri Dec 01 11:00:16 CET 2023
 *
 * Code generated for processing element Core3 (ID=3).
 */

#include "preesm_gen.h"
// Core Global Declaration
extern pthread_barrier_t iter_barrier;
extern int preesmStopThreads;

extern char *const explode_Split_0_output__Sobel_2__0; // explode_Split_0_output > Sobel_2 size:= 537600*char defined in Core0
extern uchar *const output_2__input__0; // explode_Split_0_output_output_2 > Sobel_2_input size:= 537600*uchar defined in Core0
extern uchar *const output__y_2__0;  // Erosion_2_output > implode_display_0_y_y_2 size:= 518400*uchar defined in Core0
extern char *const Erosion_2__implode_display_0_y__0; // Erosion_2 > implode_display_0_y size:= 518400*char defined in Core0

// Core Global Definitions
char Core3[1059840]; //  size:= 1059840*char
char *const Sobel_2__Dilation_2__0 = (char*) (Core3 + 0);  // Sobel_2 > Dilation_2 size:= 533760*char
char *const Dilation_2__Erosion_2__0 = (char*) (Core3 + 533760);  // Dilation_2 > Erosion_2 size:= 526080*char
uchar *const output__input__5 = (uchar*) (Core3 + 0);  // Sobel_2_output > Dilation_2_input size:= 533760*uchar
uchar *const output__input__6 = (uchar*) (Core3 + 533760);  // Dilation_2_output > Erosion_2_input size:= 526080*uchar

void* computationThread_Core3(void *arg) {
  if (arg != NULL) {
    printf("Warning: expecting NULL arguments\n");
    fflush (stdout);
  }

  // Initialisation(s)

  // Begin the execution loop
  pthread_barrier_wait(&iter_barrier);
#ifdef PREESM_LOOP_SIZE // Case of a finite loop
	int index;
	for(index=0;index<PREESM_LOOP_SIZE && !preesmStopThreads;index++){
#else // Default case of an infinite loop
  while (!preesmStopThreads) {
#endif
    // loop body
    receiveStart(); // Core0 > Core3
    receiveEnd(0, 3); // Core0 > Core3
    sobel(1920/*width*/, 280/*height*/, output_2__input__0, output__input__5); // Sobel_2

    dilation(278/*height*/, 1920/*width*/, 2/*window*/, output__input__5, output__input__6); // Dilation_2

    erosion(274/*height*/, 1920/*width*/, 2/*window*/, output__input__6, output__y_2__0); // Erosion_2

    sendStart(3, 0); // Core3 > Core0
    sendEnd(); // Core3 > Core0
    // loop footer
    pthread_barrier_wait(&iter_barrier);

  }

  return NULL;
}
