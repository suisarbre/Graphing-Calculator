#include "graph.h"


Graph:: Graph(Graph_info* gi):_p(gi){
    _gi = gi;
    _dot = sf::CircleShape(1);
    _dot.setFillColor(sf::Color(217, 106, 106));
}

void Graph::set_info(Graph_info* gi){
    _gi = gi;
    _p.set_info(gi);
}

void Graph::draw(sf::RenderWindow& window){


    for (int i = 0; i<_screenpoints.size();i++){
        _dot.setPosition(_screenpoints[i]);
        window.draw(_dot);
    }
}

void Graph::update(Graph_info* gi){
    Plot temp(_gi);
    _screenpoints = temp();
    temp.transform(_screenpoints);

}