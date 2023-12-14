#ifndef GAVIN_GRAPH_H
#define GAVIN_GRAPH_H

#include "../graph_info/graph_info.h"
#include "../queue/MyQueue.h"

#include <vector>
#include <random>

#include <SFML/Graphics.hpp>
#include "../plot/plot.h"
#include "../token/token.h"
#include "../transform/transform.h"

class Graph{
    public:
    Graph(){
    }
    Graph(Graph_info* gi);
    Graph& operator = (const Graph& other){
    if (this == &other) return *this;
    _gi = other._gi;
    _dot = other._dot;
    _p = other._p;
    return *this;
}

    void set_info(Graph_info* gi);
    void draw(sf::RenderWindow& window);
    void update(Graph_info* gi);

    private:
    sf::CircleShape _dot;
    Graph_info* _gi;
    Plot _p;
    std::vector<sf::Vector2f> _screenpoints;


};

#endif