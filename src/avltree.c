#include "avltree.h"
#include<stdio.h>
#include<stdlib.h>
#define max(a, b) (((a) > (b)) ? (a) : (b))
struct Node *root = NULL;

// Нод дерева
struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

void delete_tree(struct Node *tree) {
  if(tree!=NULL) {
    delete_tree(tree->left);
    delete_tree(tree->right);
    free(tree);
  }
}

int contains(struct Node *root, int key){
    if (root == NULL)
        return 0;

    if (key < root->key)
        return  contains(root->left, key);
    else if (key > root->key)
        return contains(root->right, key);
    else
        return 1;
}
// Функция, возвращающиая высоту, на которой находится данный нод
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
//Возвращает максимальное из двух чисел, понадобится для сравнения элементов
//int max(int a, int b){
//    return (a > b)? a : b;
//}

/* Новый нод. Изначально не имеет детей */
struct Node* newNode(int key)
{
    struct Node* node = (struct Node*)
                        malloc(sizeof(struct Node));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;
    return(node);
}
/*---------------------------------------------*/
// используется методами Insert и Delete для восстановления
// AVL-условий после операций вставки/удаления
// Поворот поддерева вправо
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Найдём местоположение
    x->right = y;
    y->left = T2;

    // Обновим высоту
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // Вернём новый корневой(root) нод
    return x;
}

// Поворот поддерева влево
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    return y;
}
/*---------------------------------------------*/

// Возвращает балансирующий фактор данного нода (разница высот левого и правого потомков)
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

/*
Рекурсивная функция.
Вставляет ключ, возвращает родительский узел
*/
struct Node* insert(struct Node* node, int key)
{
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;


    node->height = 1 + max(height(node->left),
                           height(node->right));

    /* Проверка балансирующего фактора */
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* вернётся указатель узла */
    return node;
}


/* Поиск и возврашение узла с минимальным значением */
struct Node * minValueNode(struct Node* node)
{
    struct Node* current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

// Удаление узла по ключу. Возвращает родителя.
struct Node* deleteNode(struct Node* root, int key)
{
    if (root == NULL)
        return root;

    // Если значение родителя больше значения удаляемого узла, то удаляемый элемент находится слева.
    if ( key < root->key )
        root->left = deleteNode(root->left, key);

    // иначе - справа
    else if( key > root->key )
        root->right = deleteNode(root->right, key);

    // если это значение корневого нода - его нужно удалить
    else
    {
        // если у нода один ребёнок
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct Node *temp = root->left ? root->left :
                                             root->right;

            // или детей нет
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
             *root = *temp;
            free(temp);
        }
        else
        {
            // у нода двое детей: тогда ищут переемника(меньшего в правом поддереве)
            struct Node* temp = minValueNode(root->right);

            // Копируют данные переемника
            root->key = temp->key;

            // Удалаяют
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // Если у дерева был один нод, то возвращаем его
    if (root == NULL)
      return root;

    // обновим высоту текущего нода
    root->height = 1 + max(height(root->left),
                           height(root->right));

    // проверка балансирующего фактора
    int balance = getBalance(root);

    // Если баланс нарушен то...

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


// возвращает указатели узлов, пока не встретит NULL
int preOrder(int *array, struct Node *root, int interator)
{
    if(root != NULL)
    {
        printf("%d ", array[0]);
        printf("%d ", array[1]);
        printf("%d ", array[2]);
        printf("%d ", array[3]);
        printf("%d ", array[4]);
        printf("%d ", array[5]);
        printf("%d ", array[6]);
        printf("%d ", array[7]);
        printf("%d ", array[8]);
        printf("%d ", array[9]);
        printf("            %d", interator);

        printf("\n");
        array[interator] = root->key;
        interator = preOrder(array, root->left, interator + 1); 
        interator = preOrder(array, root->right, interator + 1);
    }
    else interator = interator - 1;

    return interator;
}