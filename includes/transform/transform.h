#ifndef GAVIN_TRANSFORM_H
#define GAVIN_TRANSFORM_H

#include "../graph_info/graph_info.h"
#include "../queue/MyQueue.h"

#include <vector>

#include <SFML/Graphics.hpp>

#include "../token/token.h"

class Transform{
public:
Transform(){

}

Transform(Graph_info* gi, vector<sf::Vector2f*> points):_gi(gi),_points(points){
}

Transform& operator = (const Transform& other){
    if (this == &other) return *this;
    _gi = other._gi;
    _points = other._points;
    return *this;
}


void operator()(vector<sf::Vector2f*> points){
    _points = points;
}

vector<sf::Vector2f*> get_screenpoints(){
    sf::Vector2f origin(_gi->_screenwidth /2,_gi->_screenheight /2);
        for (int i = 0; i<_points.size();i++){
            _screenpoints.push_back(new sf::Vector2f(origin.x + _points[i]->x*(_gi->_screenwidth / (_gi->_right - _gi->_left)), origin.y - _points[i]->y*(_gi->_screenwidth / (_gi->_right - _gi->_left))));
    }
    return _screenpoints;
}

private:
    Graph_info* _gi;
    vector<sf::Vector2f*>_points;
    vector<sf::Vector2f*> _screenpoints;
};


#endif