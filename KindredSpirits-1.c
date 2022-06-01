#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "KindredSpirits.h"

typedef struct Node
{
    int values;
    struct Node* next;

} Node;

void PreOrder(node* a, int* ArrayA, int* i);
void PostOrder(node* b, int* ArrayB, int* i);
int count_nodes(node *root);

int isReflection(node *a, node *b)
{
    if(a == NULL && b == NULL) return 1;

    if(a == NULL ^ b == NULL) return 0;

    if(a->data != b->data) return 0;

    isReflection(a->left, b->right);
    isReflection(a->right, b->left);
}

node* makeReflection(node* root)
{
    node* root_reflection;
    root_reflection = malloc(sizeof(node));

    if(root_reflection == NULL) return NULL;

    if(root == NULL)
    {
        free(root_reflection);
        return NULL;
    }

    root_reflection->data = root->data;
    root_reflection->right = makeReflection(root->left);
    root_reflection->left = makeReflection(root->right);

    return root_reflection;
}

int Spirits(node* a, node* b)
{
    int *ArrayA = NULL, *ArrayB = NULL, i = 0;

    if (count_nodes(a) != count_nodes(b)) return 0;

    ArrayA = malloc(count_nodes(a) * sizeof(node));
    ArrayB = malloc(count_nodes(b) * sizeof(node));

    PreOrder(a, ArrayA, &i);
    i = 0;
    PostOrder(b, ArrayB, &i);

    for(i = 0; i < count_nodes(a); i++)
    {
        if(ArrayA[i] != ArrayB[i])
        {
            if (ArrayA != NULL) free(ArrayA);
            if (ArrayB != NULL) free(ArrayB);

            return 0;
        }
    }

    if (ArrayA != NULL) free(ArrayA);

    if (ArrayB != NULL) free(ArrayB);

    return 1;
}

int kindredSpirits(node* a, node* b)
{
  return (Spirits(a, b) || Spirits(b, a));
}

void PreOrder(node* a, int* ArrayA, int* i)
{
    if(a == NULL) return;

    ArrayA[(*i)++] = a->data;
    PreOrder(a->left, ArrayA, i);
    PreOrder(a->right, ArrayA, i);
}

void PostOrder(node* b, int* ArrayB, int* i)
{
    if(b == NULL) return;

    PostOrder(b->left, ArrayB, i);
    PostOrder(b->right, ArrayB, i);
    ArrayB[(*i)++] = b->data;
}

int count_nodes(node *root)
{
    if (root == NULL) return 0;

    return 1 + count_nodes(root->left) + count_nodes(root->right);
}
