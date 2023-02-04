#include "ant.h"

Ant::Ant(int vertex, int average_cost) : _alpha(1), _beta(1) {
  this->_vertex = vertex;
  this->_average_cost = average_cost;
  this->_visited_vertices.push_back(vertex);
}

std::vector<int> &Ant::getPath() { return this->_visited_vertices; }

bool comp(std::pair<int, double> &p1, std::pair<int, double> &p2) {
  return p1.second < p2.second;
}

void Ant::findPath(Graph &graph, double **feromons) {
  double sum, random;
  double path_attraction, amount_of_pheromone, probability;
  while (canMove(graph)) {
    sum = 0;
    std::vector<std::pair<int, double>> prob;
    for (int &to : this->_possible_vertices) {
      path_attraction = pow(static_cast<double>(this->_average_cost) /
                                graph.getMatrix()[this->_vertex][to],
                            this->_alpha);
      amount_of_pheromone = pow(feromons[this->_vertex][to], this->_beta);
      probability = path_attraction * amount_of_pheromone;
      sum += probability;
      prob.emplace_back(to, probability);
    }
    for (std::pair<int, double> &elem : prob) {
      elem.second = elem.second / sum;
    }
    std::sort(prob.begin(), prob.end(), comp);
    random = this->_randomInt(100) / static_cast<double>(100);
    for (int i = 0; i < static_cast<int>(prob.size()); ++i) {
      if (random < prob[i].second) {
        this->_visited_vertices.push_back(prob[i].first);
        this->_vertex = prob[i].first;
        break;
      } else if (i == static_cast<int>(prob.size()) - 1) {
        this->_visited_vertices.push_back(prob[i].first);
        this->_vertex = prob[i].first;
      }
    }
  }
  if (graph.getMatrix()[this->_visited_vertices.back()]
                       [this->_visited_vertices[0]] != 0 &&
      static_cast<int>(this->_visited_vertices.size()) == graph.getSize()) {
    this->_visited_vertices.push_back(_visited_vertices[0]);
  } else {
    this->_visited_vertices.clear();
  }
}

bool Ant::canMove(Graph &graph) {
  this->_possible_vertices.clear();
  for (int i = 0; i < graph.getSize(); ++i) {
    if (graph.getMatrix()[this->_vertex][i] != 0 &&
        !this->_containsVertex(i, this->_visited_vertices)) {
      this->_possible_vertices.push_back(i);
    }
  }
  return !this->_possible_vertices.empty();
}

int Ant::_randomInt(int number) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distribution{0, number};
  return distribution(gen);
}

bool Ant::_containsVertex(int vertex, std::vector<int> &vertices) {
  for (int &vertex_in : vertices) {
    if (vertex == vertex_in) {
      return true;
    }
  }
  return false;
}
