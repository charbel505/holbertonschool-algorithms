#include "graphs.h"

/**
 * graph_add_edge - add an edge between two nodes in a graph
 *
 * @graph: graph to add edge in
 * @src: source vertex content
 * @dest: destination vertex content
 * @type: type of edge, can be undirected or directed
 *
 * Return: 1 for success, 0 for failure. In case of 0, no edge is made
 */
int graph_add_edge(graph_t *graph, const char *src, const char *dest,
		   edge_type_t type)
{
	vertex_t *vertex_1, *vertex_2;
	int ret = 0;

	if (graph == NULL || src == NULL || dest == NULL)
		return (0);
	/* Find vertices */
	vertex_1 = find_vertex(graph, src);
	vertex_2 = find_vertex(graph, dest);
	if (vertex_1 == NULL || vertex_2 == NULL)
		return (0);

	/* Add edges to vertices */
	if (type == UNIDIRECTIONAL)
	{
		ret = add_edge(vertex_1, vertex_2);
		if (ret)
			vertex_1->nb_edges++;
	}
	else if (type == BIDIRECTIONAL)
	{
		ret = add_two_edges(vertex_1, vertex_2);
		if (ret)
			vertex_2->nb_edges++;
	}

	return (ret);
}


/**
 * find_vertex - find a vertex in a graph, given it's content
 *
 * @graph: graph to search
 * @content: content of vertex
 *
 * Return: pointer to vertex struct
 */
vertex_t *find_vertex(graph_t *graph, const char *content)
{
	vertex_t *vertex;

	vertex = graph->vertices;
	while (vertex != NULL)
	{
		if (!strcmp(content, vertex->content))
			return (vertex);
		vertex = vertex->next;
	}

	return (vertex);
}

/**
 * add_edge - add an edge in a graph on vertex @src pointing to vertex @dest
 *
 * @src: source vertex
 * @dest: destination vertex
 *
 * Return: 1 for success, 0 for failure
 */
int add_edge(vertex_t *src, vertex_t *dest)
{
	edge_t *edge, *next_edge;

	/* Create edge */
	edge = malloc(sizeof(edge_t));
	if (edge == NULL)
		return (0);
	edge->dest = dest;
	edge->next = NULL;

	/* Add edge */
	if (src->edges == NULL)
		src->edges = edge;
	else
	{
		next_edge = src->edges;
		while (next_edge->next != NULL)
			next_edge = next_edge->next;
		next_edge->next = edge;
	}

	return (1);
}

/**
 * add_two_edges - add an undirected edge in a graph on vertex @src and @dest
 *
 * @src: source vertex
 * @dest: destination vertex
 *
 * Return: 1 for success, 0 for failure
 */
int add_two_edges(vertex_t *src, vertex_t *dest)
{
	edge_t *edge_1, *edge_2, *next_edge;

	/* Create edge */
	edge_1 = malloc(sizeof(edge_t));
	edge_2 = malloc(sizeof(edge_t));
	if (edge_2 == NULL || edge_2 == NULL)
		return (0);
	edge_1->dest = dest;
	edge_2->dest = src;
	edge_1->next = NULL;
	edge_2->next = NULL;

	/* Add edge_1 */
	if (src->edges == NULL)
		src->edges = edge_1;
	else
	{
		next_edge = src->edges;
		while (next_edge->next != NULL)
			next_edge = next_edge->next;
		next_edge->next = edge_1;
	}

	/* Add edge_1 */
	if (dest->edges == NULL)
		dest->edges = edge_2;
	else
	{
		next_edge = dest->edges;
		while (next_edge->next != NULL)
			next_edge = next_edge->next;
		next_edge->next = edge_2;
	}

	return (1);
}
