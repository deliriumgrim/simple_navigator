#ifndef GRAPHS_S21_GRAPH_ALGORITHMS_H
#define GRAPHS_S21_GRAPH_ALGORITHMS_H

#include <math.h>

#include <vector>

#include "../containers/simple_queue/simple_queue.h"
#include "../containers/simple_stack/simple_stack.h"
#include "../graph/s21_graph.h"

struct TsmResult {
  std::vector<int> vertices;
  double distance;
};

class GraphAlgorithms {
 public:
  int *depthFirstSearch(Graph &graph, int startVertex);
  int *breadFirstSearch(Graph &graph, int startVertex);
  int getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  int **getShortestPathsBetweenAllVertices(Graph &graph);
  int **getLeastSpanningTree(Graph &graph);
  TsmResult solveTravelingSalesmanProblem(Graph &graph);

 private:
  class IncorrectVertexException : public std::exception {
   public:
    const char *what() const noexcept;
  };

  class EmptyGraphException : public std::exception {
   public:
    const char *what() const noexcept;
  };
};
#endif
