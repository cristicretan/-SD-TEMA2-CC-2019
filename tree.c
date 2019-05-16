/*
 * @Author: Cristi Cretan
 * @Date:   09-04-2019 20:10:21
 * @Last Modified by:   Cristi Cretan
 * @Last Modified time: 17-04-2019 16:58:51
 */
#include "tree.h"

/*
 * Strdup function allocates memory for "ret"
 * and then copies the given string to ret
 * @param  c [Pointer to a string]
 * @return   [returns already allocated string]
 */
char *strdup(const char *c)
{
	char *ret = (char *)malloc((strlen(c) + 1) * sizeof(char) );

	if (!ret)
	{
		fprintf(stderr, MEMERROR);
		exit(1);
	}

	strcpy(ret, c);

	return ret;
}

/*
 * initTree function allocates memory for a new tree
 * sets all it's parameters to the given ones
 * and allocates memory for the addresses only if there exists some
 * @param  id    [The node id]
 * @param  count [Number of addresses]
 * @param  addr  [String array of addresses]
 * @return       [A new Tree with the given parameters]
 */
Tree initTree(int id, int count, char **addr)
{
	Tree root = (Tree)malloc(sizeof(struct tree));

	if (!root)
	{
		fprintf(stderr, MEMERROR);
		exit(1);
	}

	root->id = id;
	root->count = count;
	root->capacity = count;
	root->parent = NULL;
	root->child = NULL;
	root->sibling = NULL;

	if (root->count > 0)
	{
		root->addr = (char **)malloc(root->capacity * sizeof(char *));
		if (!root->addr)
		{
			fprintf(stderr, MEMERROR);
			exit(1);
		}

		int i;

		for (i = 0; i < root->count; ++i)
		{
			root->addr[i] = strdup(addr[i]);

			if (!root->addr[i])
			{
				fprintf(stderr, MEMERROR);
				exit(1);
			}
		}
	}

	return root;
}

/*
 * insertChild function inserts a child to the root node
 * given as a parameter with the given parameters.
 * @param  root  [The node to whom to add a child]
 * @param  id    [Id of the new node]
 * @param  count [Number of addresses]
 * @param  addr  [Addresses string array]
 * @return       [Returns the root node with the new child added]
 */
Tree insertChild(Tree root, int id, int count, char **addr)
{
	if (!root)
	{
		root = initTree(id, count, addr);
		return root;
	}

	Tree new = initTree(id, count, addr);

	new->parent = root;

	if (root->child)
	{
		Tree iter;

		for (iter = root->child; iter->sibling; iter = iter->sibling);

		iter->sibling = new;
	}
	else
		root->child = new;

	return root;
}

/*
 * getChild function searches for a specific child
 * in all the children of the given "root" node
 * @param  root [Given node to see if it has a specific child]
 * @param  id   [Child's id to search for]
 * @return      [Pointer to the child if it's found, NULL otherwise]
 */
Tree getChild(Tree root, int id)
{
	if (!root)
		return NULL;
	if (root->id == id)
		return root;

	Tree iter;

	for (iter = root->child; iter; iter = iter->sibling)
		if (iter->id == id) return iter;

	return NULL;
}

/*
 * findChild function searches for a specific child
 * in every subtree of the Tree given
 * It uses 2 recursive calls on the every child
 * and it's every sibling and every sibling's child
 * @param  root [Root of the Tree or subtree, respectively]
 * @param  id   [Id of the wanted node]
 * @return      [return the child if it's found]
 */
Tree findChild(Tree root, int id)
{
	if (!root)
		return NULL;
	if (root->id == id)
		return root;

	Tree child = findChild(root->child, id);

	if (!child)
		child = findChild(root->sibling, id);

	return child;
}

/*
 * freeTree function recursively calls itself
 * and frees every subTree of the root Tree given
 * and all of it's parameters
 * @param  root [Tree's root or subtree's root, respectively]
 * @return      [NULL]
 */
Tree freeTree(Tree root)
{
	if (!root)
		return NULL;

	Tree tmp = root->child;
	Tree temp = tmp;

	while (tmp)
	{
		temp = tmp->sibling;
		tmp = freeTree(tmp);
		tmp = temp;
	}

	int i;

	for (i = 0; i < root->capacity; ++i)
		free(root->addr[i]);
	free(root->addr);
	free(root);

	return NULL;
}
