#include "graphs.h"

/**
 * graph_add_vertex - add a vertex to a graph
 * @graph: pointer to a graph
 * @str: strin to store at the node
 * Store a copy of the string on the node. If the value
 * already exists, fail.
 * Return: pointer to created vertex or NULL on failure.
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *new, *tmp;

	if (!graph || !str)
		return (NULL);

	tmp = graph->vertices;
/* loop to the last-1 element in list */
	while (tmp && tmp->next)
	{
		if (!strcmp(tmp->content, str))
			return (NULL);
		tmp = tmp->next;
	}
/* last element */
	if (tmp && !strcmp(tmp->content, str))
		return (NULL);
/* create a new vertex */
	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->content = strdup(str);
	if (!new->content)
	{
		free(new);
		return (NULL);
	}

	new->index = graph->nb_vertices++;
	new->nb_edges = 0;
	new->edges = 0;
	new->next = NULL;
	if (tmp)
		tmp->next = new;
	else
		graph->vertices = new;

	return (new);
}
