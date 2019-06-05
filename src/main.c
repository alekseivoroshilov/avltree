#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"

int main(int argc, char **argv) {
  struct Node *root = NULL;
  FILE *S1, *S2;
  S1 = fopen(argv[1],"r+");
  S2 = fopen(argv[2], "w");

  int k,i;
  k = 0;
  int s;

  while ((fscanf(S1, "%d", &s)!=EOF))
  {
    if(!S1) break;    //чтобы не делал лишнего
    k += 1; //узнаем, сколько элементов
  }

  int *c = (int*) malloc(k * sizeof(int));  //должен быть динамическим
  rewind(S1);    //перематываем файл для повторного чтения

  for(i = 0; i < k; i++)
  {
    fscanf(S1, "%d",&c[i]);
    printf("c[%d]=%d  ", i, c[i]);
  }

  fclose(S1);
  for (i = 0; i < k; i++){
    root = insert(root, c[i]);
  }

  preOrder(c, root, 0);

  for(i = 0; i < k; i++) fprintf(S2, " %d", c[i]);

  fclose(S2);
  free(c); //убираем мусор, когда уже не нужен (но не раньше =))
  getchar();  //задержка консоли
  return 0;
}