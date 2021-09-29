#include "graphs.h"

/**
 * depth_first_traverse - traverse a graph by going to the deepest untouched
 * vertex first before traversing sibling edges
 *
 * @graph: graph to traverse
 * @action: action to take when visiting each vertex
 *
 * Return: depth of the deepest traversal
 */
size_t depth_first_traverse(const graph_t *graph,
			    void (*action)(const vertex_t *v, size_t depth))
{
	size_t depth = 0, i;
	visited_type_t *visited;

	if (graph == NULL || action == NULL)
		return (0);
	/* Initialize visited array to 0's */
	visited = malloc(sizeof(visited_type_t) * graph->nb_vertices);
	for (i = 0; i < graph->nb_vertices; i++)
		visited[i] = WHITE;

	if (graph->vertices == NULL)
	{
		free(visited);
		return (depth);
	}

	depth = depth_first_traverse_r(graph->vertices, action, visited, 0);
	free(visited);

	return (depth);
}

/**
 * depth_first_traverse_r - recursively traverse a graph's edges, depth-first
 *
 * @vertex: vertex we're visiting
 * @action: action to take on each node
 * @visited: array of integers defining whether we've visited a node before
 * @depth: current depth of recursion
 *
 * Return: The maximum depth reached by the traversal
 */
size_t depth_first_traverse_r(vertex_t *vertex, void (*action)
			      (const vertex_t *v, size_t depth),
			      visited_type_t visited[], size_t depth)
{
	edge_t *next_edge;
	size_t next_depth, deepest_depth;

	next_depth = deepest_depth = 0;
	if (vertex == NULL || visited[vertex->index] == BLACK)
		return (0);

	action(vertex, depth);
	visited[vertex->index] = BLACK;
	for (next_edge = vertex->edges; next_edge; next_edge = next_edge->next)
	{
		next_depth = depth_first_traverse_r(
			next_edge->dest,
			action,
			visited,
			depth + 1);
		if (next_depth > deepest_depth)
			deepest_depth = next_depth;
	}
	visited[vertex->index] = BLACK;
	if (depth > deepest_depth)
		deepest_depth = depth;
	return (deepest_depth);
}
