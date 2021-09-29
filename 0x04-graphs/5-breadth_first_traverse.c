#include "graphs.h"
#include <stdio.h>

/**
 * breadth_first_traverse - traverse a graph by exploring sibling edges before
 * exploring child edges
 *
 * @graph: graph to traverse
 * @action: action to take on each vertex
 *
 * Return: depth of traversal
 */
size_t breadth_first_traverse(const graph_t *graph,
			      void (*action)(const vertex_t *v, size_t depth))
{
	size_t depth = 0, i, new_depth;
	vlist_t *v_and_d;
	visited_type_t *visited;
	vertex_t *vertex;
	queue_t queue = {NULL, NULL};
	edge_t *edge;

	if (graph == NULL || action == NULL)
		return (0);
	/* Initialize visited array to 0's */
	visited = malloc(sizeof(visited_type_t) * graph->nb_vertices);
	for (i = 0; i < graph->nb_vertices; i++)
		visited[i] = WHITE;
	if (graph->vertices == NULL ||
	    push(&queue, graph->vertices, depth) == NULL)
	{
		free(visited);
		return (0);
	}
	while ((v_and_d = pop(&queue)))
	{
		vertex = v_and_d->vertex;
		new_depth = v_and_d->depth;
		free(v_and_d);
		if (new_depth > depth && visited[vertex->index] == WHITE)
			depth = new_depth;
		if (vertex)
		{
			if (visited[vertex->index] == WHITE)
				action(vertex, depth);
			visited[vertex->index] = BLACK;
			for (edge = vertex->edges; edge != NULL; edge = edge->next)
			{
				if (edge->dest && visited[edge->dest->index] == WHITE)
					if (push(&queue, edge->dest, new_depth + 1) == NULL)
					{
						free(visited);
						return (0);
					}
			}
		}
	}
	free(visited);
	return (depth);
}

/**
 * push - push a vertex onto the queue
 *
 * @queue: queue to push onto
 * @vertex: vertex to push
 * @depth: depth of vertex in traversal
 *
 * Return: pointer to list node, or NULL on failure
 */
vlist_t *push(queue_t *queue, vertex_t *vertex, size_t depth)
{
	vlist_t *new_node;

	new_node = malloc(sizeof(vlist_t));
	if (new_node == NULL)
		return (NULL);
	new_node->vertex = vertex;
	new_node->depth = depth;
	new_node->prev = NULL;
	if (queue->head == NULL && queue->tail == NULL)
	{
		queue->head = new_node;
		queue->tail = new_node;
		new_node->next = NULL;
	}
	else
	{
		queue->head->prev = new_node;
		new_node->next = queue->head;
		queue->head = new_node;
	}
	return (new_node);
}

/**
 * pop - pop a node off of a queue tail
 *
 * @queue: queue to pop from
 *
 * Return: vertex of popped node
 */
vlist_t *pop(queue_t *queue)
{
	vlist_t *node;

	if (queue->tail == NULL)
		return (NULL);
	node = queue->tail;
	queue->tail = node->prev;
	if (queue->head == node)
		queue->head = NULL;

	return (node);
}
