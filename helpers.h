/*
 * @Author: Cristi Cretan
 * @Date:   09-04-2019 20:11:24
 * @Last Modified by:   Cristi Cretan
 * @Last Modified time: 17-04-2019 15:05:09
 */
#include "tree.h"

typedef struct queries
{
	char type;
	int user;
	int size;
	char *addr;
} Queries;

Tree addAddress(Tree parent, Tree child);
void printAddress(Tree root, FILE *f);
bool alreadyExistsAddress(Tree root, char *addr);
Tree deleteChild(Tree root);
Tree uniteTrees(Tree child, Tree parent);
Tree uniteForest(Tree root, Tree *forest, int n);
void solveQuery(Tree root, Queries q, int *users, int n_users, FILE *f);
