/*
 * @Author: Cristi Cretan
 * @Date:   09-04-2019 09:34:17
 * @Last Modified by:   Cristi Cretan
 * @Last Modified time: 19-04-2019 11:08:11
 */
#include "helpers.h"

/*
 * Print root's id and every child's id
 * then recursively call for every child
 * @param root [Tree's root or the subtree's root]
 * @param f    [Pointer to print in some file]
 */
void printParentChild(Tree root, FILE *f)
{
	if (root)
	{
		if (!root->child)
			fprintf(f, "%d\n", root->id);
		else
			fprintf(f, "%d ", root->id);

		Tree child;

		for (child = root->child; child; child = child->sibling)
			if (child->sibling)
				fprintf(f, "%d ", child->id);
			else
				fprintf(f, "%d\n", child->id);

		for (child = root->child; child; child = child->sibling)
			printParentChild(child, f);
	}
}

/*
 * For every child of root recursively call the function
 * then build your way up with the addresess from leaves
 * @param root [Tree's or subtree's root]
 */
void initHierarchy(Tree root)
{
	if (!root)
		return;

	Tree child;

	for (child = root->child; child; child = child->sibling) 
	{
		initHierarchy(child);
		root = addAddress(root, child);
	}
}

/*
 * For every query check for it's type
 * if it is a normal query solve it
 * using the solveQuery function
 * if it's a "fault" query
 * then destroy the child and append
 * all of it's children to it's parent.
 * @param root    [Tree's or subtree's root]
 * @param q       [Queries array]
 * @param users   [Users array]
 * @param n_users [Number of users]
 * @param f       [Pointer to print in some file]
 */
void solveQueries(Tree root, Queries *q, int *users, int n_users, FILE *f)
{
	int i, j;

	for (i = 0; i < q->size; ++i)
		if (q[i].type == 'q')
			solveQuery(root, q[i], users, n_users, f);
		else
		{
			Tree child = findChild(root, q[i].user);

			child = deleteChild(child);
			for (j = 0; j < n_users; ++j)
				if (users[j] == q[i].user)
					users[j] = child->id;
		}
}

/*
 * Reading the input from every file and building the tree
 * used for solving the queries.
 * And calling the right functions for solving the queries and
 * initialising the hierarchy.
 * (more details about how the tree is built in "README.md")
 */
int main(void)
{
	Tree DNS = NULL;
	int n, i, j;

	FILE *f = fopen(TREEFILE_IN, "r");

	if (!f)
	{
		perror(TREEFILE_IN);
		exit(1);
	}

	fscanf(f, "%d", &n);
	Tree *forest = (Tree *)malloc(n * sizeof(struct tree));

	for (i = 0; i < n; ++i)
		forest[i] = initTree(i, 0, NULL);

	int *parents = (int *)malloc(n * sizeof(int));

	for (i = 0; i < n; ++i)
	{
		int id, parent, count;

		fscanf(f, "%d %d %d ", &id,  &parent, &count);

		parents[i] = parent;

		char **addr = (char **)malloc(count * sizeof(char *));

		if (!addr)
		{
			fprintf(stderr, MEMERROR);
			exit(1);
		}

		for (j = 0; j < count; ++j)
		{
			int cap = CAP;
			char c;
			int k = 0;

			addr[j] = (char *)malloc(cap * sizeof(char));

			if (!addr[j])
			{
				fprintf(stderr, MEMERROR);
				exit(1);
			}

			while (true)
			{
				fscanf(f, "%c", &c);

				if (c == ' ' || c == '\n')
					break;
				if (k == cap)
				{
					addr[j] = (char *)realloc(addr[j], DOI * cap * sizeof(char));

					if (!addr[j])
					{
						fprintf(stderr, MEMERROR);
						exit(1);
					}

					cap *= DOI;
				}

				addr[j][k++] = c;
			}
			addr[j][k] = '\0';
		}

		forest[i]->capacity = count;
		forest[i]->count = count;
		forest[i]->addr = addr;
	}

	fclose(f);

	for (i = 0; i < n; ++i)
		if (parents[i] != -1)
			forest[i]->parent = forest[parents[i]];

	DNS = uniteForest(DNS, forest, n);
	free(parents);
	free(forest);


	f = fopen(TREEFILE_OUT, "w");
	printParentChild(DNS, f);
	fclose(f);

	f = fopen(HIERARCHY_OUT, "w");
	initHierarchy(DNS);

	for (i = 0; i < n; ++i)
	{
		Tree child = findChild(DNS, i);

		printAddress(child, f);
	}

	fclose(f);

	f = fopen(USERSFILE_IN, "r");

	if (!f)
	{
		perror(USERSFILE_IN);
		exit(1);
	}

	int n_users;

	fscanf(f, "%d", &n_users);
	int *users = (int *)malloc(n * sizeof(int));

	if (!users)
	{
		fprintf(stderr, MEMERROR);
		exit(1);
	}

	for (i = 0; i < n_users; ++i)
	{
		int x, y;

		fscanf(f, "%d %d", &x, &y);
		users[x] = y;
	}

	fclose(f);

	f = fopen(QUERIESFILE_IN, "r");

	if (!f)
	{
		perror(QUERIESFILE_IN);
		exit(1);
	}

	int n_queries;

	fscanf(f, "%d\n", &n_queries);

	Queries *q = (Queries *)malloc(n_queries * sizeof(struct queries));

	q->size = 0;

	for (i = 0; i < n_queries; ++i)
		q[i].addr = NULL;

	for (i = 0; i < n_queries; ++i)
	{
		q->size++;

		fscanf(f, "%c ", &q[i].type);

		if (q[i].type == 'q')
		{
			fscanf(f, "%d ", &q[i].user);

			int k = 0;
			int cap = CAP;
			char c;

			q[i].addr = (char *)malloc(cap * sizeof(char));

			fscanf(f, "%c", &c);
			while (true)
			{
				q[i].addr[k++] = c;
				if (k == cap)
				{
					cap *= DOI;
					q[i].addr = (char *)realloc(q[i].addr, cap * sizeof(char));

					if (!q[i].addr)
					{
						fprintf(stderr, MEMERROR);
						exit(1);
					}
				}

				fscanf(f, "%c", &c);

				if (c == '\n')
					break;
			}
			q[i].addr[k] = '\0';
		}
		else
			fscanf(f, "%d\n", &q[i].user);
	}

	fclose(f);

	f = fopen(QUERIESFILE_OUT, "w");

	solveQueries(DNS, q, users, n_users, f);

	fclose(f);

	free(users);
	for (i = 0; i < n_queries; i++)
		free(q[i].addr);
	free(q);
	DNS = freeTree(DNS);
	return 0;
}
