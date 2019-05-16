/*
 * @Author: Cristi Cretan
 * @Date:   09-04-2019 20:10:05
 * @Last Modified by:   Cristi Cretan
 * @Last Modified time: 19-04-2019 11:07:08
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <string.h>

#define SIZE 200
#define MEMERROR "Memory was not correctly allocated.\n"
#define CAP 4
#define DOI 2
#define TREEFILE_IN "tree.in"
#define TREEFILE_OUT "tree.out"
#define USERSFILE_IN "users.in"
#define HIERARCHY_OUT "hierarchy.out"
#define QUERIESFILE_IN "queries.in"
#define QUERIESFILE_OUT "queries.out"

typedef struct tree
{
	int id;
	int count;
	int capacity;
	char **addr;
	struct tree *parent;
	struct tree *child;
	struct tree *sibling;
} *Tree;

char *strdup(const char *c);
Tree initTree(int id, int count, char **addr);
Tree insertChild(Tree root, int id, int count, char **addr);
Tree getChild(Tree root, int id);
Tree findChild(Tree root, int id);
Tree freeTree(Tree root);
