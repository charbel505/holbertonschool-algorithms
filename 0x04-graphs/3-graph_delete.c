#include "graphs.h"

/**
 * graph_delete - delete graph, including its edges, vertices and the graph
 * itself.
 *
 * @graph: graph to delete
 */
void graph_delete(graph_t *graph)
{
	vertex_t *tmp_vertex;
	edge_t *tmp_edge;

	if (graph == NULL)
		return;

	while (graph->vertices != NULL)
	{
		while (graph->vertices->edges != NULL)
		{
			tmp_edge = graph->vertices->edges;
			graph->vertices->edges = graph->vertices->edges->next;
			free(tmp_edge);
		}
		tmp_vertex = graph->vertices;
		graph->vertices = graph->vertices->next;
		free(tmp_vertex->content);
		free(tmp_vertex);
	}
	free(graph);
}
