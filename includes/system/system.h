#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "../graph/graph.h"
#include "../graph_info/graph_info.h"

class System
{
public:
    System();
    System(Graph_info* gi);
    void set_info(Graph_info* gi);
    void Step(int command, Graph_info* gi);
    void Draw(sf::RenderWindow& window);
private:
//    vector<Particle> system;
    Graph graph;
    Graph_info* _gi;
};

#endif // SYSTEM_H
