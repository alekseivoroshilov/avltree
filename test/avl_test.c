#include "test.h"
#include "avltree.h"

void test() {

    struct Node *root = NULL;
    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 6);
    root = insert(root, 11);
    root = insert(root, -1);
    root = insert(root, 1);
    root = insert(root, 2);

    

    /*
            9
           /  \
          1    10
        /  \     \
       0    5     11
      /    /  \
     -1   2    6
    */

    printf("Порядок элементов: \n");
	int *initial = malloc(sizeof(int) * (9));
  int initial2[] = {9, 1, 0, -1, 5, 2, 6, 10, 11};
    //int *initial2 = malloc(sizeof(int) * 10);
  int counter = 0;
	preOrder(initial, root, counter);

    /*
            1
           /  \
          0    9
        /     /  \
       -1    5     11
           /  \
          2    6
    */


  int i;
  for(i = 0; i < 9; i++){
    assert_equals_int(initial2[i], initial[i]);
  }

  root = deleteNode(root, 10);
  free(initial);
  *initial = malloc(sizeof(int) * (8));
  int initial3[] = {1, 0, -1, 9, 5, 2, 6, 11};

    /*
            1
           /  \
          0    9
        /     /  \
       -1    5     11
           /  \
          2    6
    */

  printf("\nПорядок элементов дерева после удаления выбранного элемента \n");
  preOrder(initial, root, counter);
  for(i = 0; i < 8; i++){
    assert_equals_int(initial3[i], initial[i]);
  }
  assert_equals_int(contains(root, 6), 1);
  assert_equals_int(contains(root, 4), 0);
    printf("\nВыполнено \n");
}