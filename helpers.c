/*
 * @Author: Cristi Cretan
 * @Date:   09-04-2019 20:11:48
 * @Last Modified by:   Cristi Cretan
 * @Last Modified time: 17-04-2019 17:01:06
 */
#include "helpers.h"

/*
 * addAddress function adds all unique addreses
 * to a given parent node from a given child node
 * @param  parent [Parent node]
 * @param  child  [Child node]
 * @return        [Adress of the modified parent node]
 */
Tree addAddress(Tree parent, Tree child)
{
	if (!parent || !child)
		return NULL;

	int i, j, k = 0;

	for (i = 0; i < child->count; ++i)
	{
		bool ok = false;

		for (j = 0; j < parent->count; ++j)
			if (!strcmp(child->addr[i], parent->addr[j]))
			{
				ok = true;
				break;
			}

		if (!ok)
			k++;
	}

	int add = parent->count;

	parent->count += k;
	if (add != parent->count)
	{
		parent->capacity = parent->count;
		parent->addr = (char **)realloc(parent->addr, parent->count * sizeof(char *));

		if (!parent->addr)
		{
			fprintf(stderr, MEMERROR);
			exit(1);
		}

		for (i = 0; i < child->count; ++i)
		{
			bool ok = false;

			for (j = 0; j < parent->count - k; ++j)
				if (!strcmp(child->addr[i], parent->addr[j]))
				{
					ok = true;
					break;
				}

			if (!ok)
			{
				parent->addr[add] = strdup(child->addr[i]);

				if (!parent->addr[add])
				{
					fprintf(stderr, MEMERROR);
					exit(1);
				}

				add++;
			}
		}
	}

	return parent;
}

/*
 * printAddress function prints all the addresses
 * of a given root node in some given file
 * @param root [Root node]
 * @param f    [File pointer to print in]
 */
void printAddress(Tree root, FILE *f)
{
	if (!root)
		return;

	fprintf(f, "%d ", root->id);

	int i;

	for (i = 0; i < root->count; ++i)
		if (i < root->count - 1)
			fprintf(f, "%s ", root->addr[i]);
		else
			fprintf(f, "%s\n", root->addr[i]);
}

/*
 * alreadyexistsAddress check if an address exists
 * in a given root node.
 * @param  root [Root node]
 * @param  addr [Address to check for]
 * @return      [Returns true if found, false otherwise]
 */
bool alreadyExistsAddress(Tree root, char *addr)
{
	if (!root)
		return false;

	int i;

	for (i = 0; i < root->count; ++i)
		if (strcmp(root->addr[i], addr) == 0)
			return true;

	return false;
}

/*
 * deleteChild function frees the given root node
 * and appends all of the given root node's children
 * to it's parent
 * @param  root [Root node to delete]
 * @return      [The new root's node parent with all the children]
 */
Tree deleteChild(Tree root)
{
	if (!root)
		return NULL;

	Tree ret = root->parent;
	Tree iter = root->child;

	if (ret->child->id == root->id)
	{
		ret->child = root->sibling;

		int i;

		for (i = 0; i < root->capacity; ++i)
			free(root->addr[i]);

		free(root->addr);
		free(root);
	}
	else
	{
		Tree chg = ret->child;

		for (chg  = ret->child; chg; chg = chg->sibling)
			if (chg->sibling->id == root->id)
			{
				Tree tmp = chg->sibling;

				chg->sibling = chg->sibling->sibling;

				int i;

				for (i = 0; i < tmp->capacity; ++i)
					free(tmp->addr[i]);

				free(tmp->addr);
				free(tmp);

				break;
			}
	}

	Tree add = ret->child;

	while (iter)
	{
		iter->parent = ret;
		if (!add)
			ret->child = iter;
		else
			add->sibling = iter;

		add = iter;
		iter = iter->sibling;
	}

	return ret;
}

/*
 * uniteTrees function is making the given child's parent
 * the given parent node and appends to the parent node the given child
 * @param  child  [Child node]
 * @param  parent [Parent node]
 * @return        [Returns the new parent]
 */
Tree uniteTrees(Tree child, Tree parent)
{
	if (parent)
	{
		if (!parent->child)
			parent->child = child;
		else
		{
			Tree iter;

			for (iter = parent->child; iter->sibling; iter = iter->sibling);
			iter->sibling = child;
		}
	}

	return parent;
}

/*
 * uniteForest function takes a forest and the number of trees in it,
 * for every tree in the forest it creates "bounds"
 * between it's parents and childs using the uniteTrees function
 * @param  root   [Root node to unite all forest in it]
 * @param  forest [Tree array]
 * @param  n      [Number of trees]
 * @return        [Returns the new Tree]
 */
Tree uniteForest(Tree root, Tree *forest, int n)
{
	int i;

	for (i = 1; i < n; ++i)
		root = uniteTrees(forest[i], forest[i]->parent);
	root = forest[0];

	return root;
}

/*
 * solveQuery function takes the root node of the tree
 * find the coresponding server
 * from the users array then it goes up the tree
 * until it finds the wanted address
 * while printing the path. Also caching the address while traversing up.
 * @param root    [Tree's root node]
 * @param q       [Given query]
 * @param users   [Users array]
 * @param n_users [Number of users]
 * @param f       [File pointer to print in]
 */
void solveQuery(Tree root, Queries q, int *users, int n_users, FILE *f)
{
	Tree child = findChild(root, users[q.user]);
	bool ok = true;
	Tree iter = child;

	for (iter = child; iter && ok; iter = iter->parent)
	{
		int i;

		for (i = 0; i < iter->count; ++i)
		{
			if (strcmp(iter->addr[i], q.addr) == 0)
			{
				ok = false;
				break;
			}
		}

		if (!ok)
			fprintf(f, "%d", iter->id);
		else
			fprintf(f, "%d ", iter->id);

		if (iter && !alreadyExistsAddress(iter, q.addr))
		{
			if (iter->count == iter->capacity)
			{
				iter->capacity *= DOI;
				iter->addr = (char **)realloc(iter->addr, iter->capacity * sizeof(char *));

				if (!iter->addr)
				{
					fprintf(stderr, MEMERROR);
					exit(1);
				}

				int k;

				for (k = iter->count; k < iter->capacity; ++k)
					iter->addr[k] = NULL;
			}

			iter->addr[iter->count++] = strdup(q.addr);
		}
	}

	fprintf(f, "\n");
}
