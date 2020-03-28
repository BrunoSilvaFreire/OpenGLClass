#include <unnecessary/graphs/graph.h>

#include <utility>
#include <iostream>

struct DummyVertex {
private:
    int weight;
public:
    DummyVertex() = default;

    explicit DummyVertex(int weight) : weight(weight) {}

    int getWeight() const {
        return weight;
    }
};

struct DummyEdge {
private:
    std::string label;
public:

    DummyEdge() = default;

    explicit DummyEdge(std::string label) : label(std::move(label)) {}

    const std::string &getLabel() const {
        return label;
    }
};

int main() {
    un::MatrixGraph<DummyVertex, DummyEdge> graph;
    auto firstIndex = graph.emplaceVertex(0);
    auto secondIndex = graph.emplaceVertex(20);
    std::cout << firstIndex << ", " << secondIndex << std::endl;
    auto edgeIndex = graph.connect(firstIndex, secondIndex, "hello");
    std::cout << "Vertices connected @ " << edgeIndex;
}