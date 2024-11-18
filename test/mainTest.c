#include <../include/morph.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Déclaration des fonctions à tester
void dilation(int height, int width, const int window, unsigned char *input,
              unsigned char *output);
void erosion(int height, int width, const int window, unsigned char *input,
             unsigned char *output);

// Fonction utilitaire pour comparer deux tableaux
int compare_arrays(unsigned char *a, unsigned char *b, int size) {
  for (int i = 0; i < size; i++) {
    if (a[i] != b[i]) {
      return 0; // Différence trouvée
    }
  }
  return 1; // Identiques
}

// Test pour la fonction dilation
void test_dilation() {
  const int height = 5, width = 5, window = 1;
  unsigned char input[25] = {0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0};
  unsigned char output[25] = {0};
  unsigned char expected_output[25] = {0, 0, 0,   0,   0, 255, 255, 255, 0,
                                       0, 0, 255, 255, 0, 0,   0,   0,   0,
                                       0, 0, 0,   0,   0, 0,   0};

  dilation(height, width, window, input, output);

  CU_ASSERT_TRUE(compare_arrays(output, expected_output, 25));
}

// Test pour la fonction erosion
void test_erosion() {
  const int height = 5, width = 5, window = 1;
  unsigned char input[25] = {255, 255, 255, 255, 255, 255, 0,   255, 255,
                             255, 255, 255, 255, 255, 255, 255, 255, 255,
                             255, 255, 255, 255, 255, 255, 255};
  unsigned char output[25] = {0};
  unsigned char expected_output[25] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  erosion(height, width, window, input, output);

  CU_ASSERT_TRUE(compare_arrays(output, expected_output, 25));
}

// Configuration des tests
int main() {
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  CU_pSuite pSuite = CU_add_suite("Image Processing Tests", NULL, NULL);
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if ((NULL == CU_add_test(pSuite, "test_dilation", test_dilation)) ||
      (NULL == CU_add_test(pSuite, "test_erosion", test_erosion))) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
