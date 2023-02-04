#include "colony.h"

Colony::~Colony() {
  if (this->_pheromons) {
    for (int i = 0; i < this->_graph.getSize(); ++i) {
      delete[] this->_pheromons[i];
    }
    delete[] this->_pheromons;
    this->_pheromons = nullptr;
  }
}

Colony::Colony(Graph &graph) : _graph(graph), _pheromon_remains(0.8) {
  this->_vertexes = graph.getSize();
  this->_pheromons = new double *[graph.getSize()];
  for (int i = 0; i < graph.getSize(); ++i) {
    this->_pheromons[i] = new double[graph.getSize()];
  }
  for (int i = 0; i < graph.getSize(); ++i) {
    for (int j = 0; j < graph.getSize(); ++j) {
      this->_pheromons[i][j] = 1;
    }
  }
  this->_average_cost = 0;
  for (int i = 0; i < graph.getSize(); ++i) {
    for (int j = 0; j < graph.getSize(); ++j) {
      this->_average_cost += graph.getMatrix()[i][j];
    }
  }
  this->_average_cost /= graph.getSize() * graph.getSize() - graph.getSize();
}

void Colony::createAnts(int numOfAnts) {
  this->_ants.clear();
  for (int i = 0; i < numOfAnts; i++) {
    this->_ants.push_back(Ant(i, this->_average_cost));
  }
}

void Colony::findPath() {
  for (Ant &ant : this->_ants) {
    ant.findPath(this->_graph, this->_pheromons);
  }
}

void Colony::updateFeromon() {
  for (Ant &ant : this->_ants) {
    std::vector<int> &path = ant.getPath();
    int cost = findPathCost(path);
    double addPheromone = static_cast<double>(this->_average_cost) *
                          static_cast<double>(this->_vertexes) /
                          static_cast<double>(cost);
    for (int i = 1; i < static_cast<int>(path.size()); ++i) {
      this->_pheromons[path[i - 1]][path[i]] += addPheromone;
    }
  }
  for (int i = 0; i < this->_graph.getSize(); ++i) {
    for (int j = 0; j < this->_graph.getSize(); ++j) {
      this->_pheromons[i][j] *= this->_pheromon_remains;
    }
  }
}

int Colony::findPathCost(std::vector<int> &path) {
  int res = 0;
  for (int i = 1; i < static_cast<int>(path.size()); ++i) {
    res += this->_graph.getMatrix()[path[i - 1]][path[i]];
  }
  return res;
}

void Colony::updateResult(TsmResult &result) {
  for (Ant &ant : this->_ants) {
    std::vector<int> &path = ant.getPath();
    int cost = findPathCost(path);
    if (cost && result.distance > static_cast<double>(cost)) {
      result.distance = static_cast<double>(cost);
      result.vertices = path;
    }
  }
}