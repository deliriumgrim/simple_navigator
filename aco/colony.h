#ifndef GRAPHS_COLONY_HPP
#define GRAPHS_COLONY_HPP

#include <vector>

#include "../aco/ant.h"
#include "../graph_algorithms/s21_graph_algorithms.h"

class Colony {
 public:
  Colony() = delete;
  Colony(Graph &graph);
  ~Colony();

  void createAnts(int numOfAnts);
  void findPath();
  void updateFeromon();
  void updateResult(TsmResult &result);

 private:
  int findPathCost(std::vector<int> &path);
  Graph &_graph;
  int _vertexes;
  int _average_cost;
  double **_pheromons;
  double _pheromon_remains;
  std::vector<Ant> _ants;
};
#endif
