#ifndef SRC_ANT_HPP
#define SRC_ANT_HPP

#include <algorithm>
#include <cmath>
#include <random>
#include <vector>

#include "../graph/s21_graph.h"

class Ant {
 public:
  Ant(int vertex, int average_cost);
  Ant() = delete;

  void findPath(Graph &graph, double **feromons);
  std::vector<int> &getPath();
  bool canMove(Graph &graph);

 private:
  bool _containsVertex(int vertex, std::vector<int> &vertices);
  int _randomInt(int number);
  int _vertex;
  int _average_cost;
  double _alpha;
  double _beta;
  std::vector<int> _visited_vertices;
  std::vector<int> _possible_vertices;
};

#endif
