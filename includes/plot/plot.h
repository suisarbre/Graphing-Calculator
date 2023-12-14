#ifndef GAVIN_PLOT_H
#define GAVIN_PLOT_H

#include "../graph_info/graph_info.h"
#include "../queue/MyQueue.h"

#include <vector>
#include "../shunting_yard/shunting_yard.h"
#include <SFML/Graphics.hpp>

#include "../token/token.h"
#include "../token/leftparen.h"
#include "../token/rightparen.h"
#include "../rpn/rpn.h"
#include "../constants.h"


class Plot{
    public:
    Plot(){
    }
    Plot(Graph_info* gi);
    void set_info(Graph_info* gi);
    vector<sf::Vector2f> operator()();//this returns the points
    void Tokenizer();
    void transform(vector<sf::Vector2f>& screenpoints);

    private:
    Graph_info* _gi;
    Queue<Token*> _postfix;
};



#endif