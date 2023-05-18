#include "main.h"

/**
 * new_node - creats a new node
 * @type: enum with type node_type_e
 *
 * Return: the node on success, NULL if no new node
 */

struct node_s *new_node(enum node_type_e type)
{
	struct node_s *node = malloc(sizeof(struct node_s));

	if (!node)
	{
		return (NULL);
	}
	_memset(node, 0, sizeof(struct node_s));
	node->type = type;

	return (node);
}

/**
 * add_child_node - adds a chiled node to the list
 * @parent: parent struct of type node_s
 * @child: chiled structof type node_s
 *
 * Return: void
 */

void add_child_node(struct node_s *parent, struct node_s *child)
{
	struct node_s *sibling;

	if (!parent || !child)
	{
		return;
	}
	if (!parent->first_child)
	{
		parent->first_child = child;
	}
	else
	{
		sibling = parent->first_child;

		while (sibling->next_sibling)
		{
			sibling = sibling->next_sibling;
		}

		sibling->next_sibling = child;
		child->prev_sibling = sibling;
	}
	parent->children++;
}


/**
 * set_node_val_str - sets the value of a node
 * @node: struct node to access set variable
 * @val: char value to set to
 *
 * Return: void
 */

void set_node_val_str(struct node_s *node, char *val)
{
	char *val2;

	node->val_type = VAL_STR;
	if (!val)
	{
		node->val.str = NULL;
	}
	else
	{
		val2 = malloc(_strlen(val) + 1);

		if (!val2)
		{
			node->val.str = NULL;
		}
		else
		{
			_strcpy(val2, val);
			node->val.str = val2;
		}
	}
}


/**
 * free_node_tree - free's the old tree
 * @node: the node to free of type node
 *
 * Return: void
 */

void free_node_tree(struct node_s *node)
{
	struct node_s *child;
	struct node_s *next;

	if (!node)
	{
		return;
	}
	child = node->first_child;
	while (child)
	{
		next = child->next_sibling;
		free_node_tree(child);
		child = next;
	}
	if (node->val_type == VAL_STR)
	{
		if (node->val.str)
		{
			free(node->val.str);
		}
	}
	free(node);
}
