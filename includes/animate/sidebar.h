#ifndef SIDEBAR_H
#define SIDEBAR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../graph_info/graph_info.h"
using namespace std;


class Sidebar
{
public:
    Sidebar();
    Sidebar(float left, float width);
    ~Sidebar();
    void draw(sf::RenderWindow& window);
    sf::Text* operator [](int index);
    vector<sf::Text*> getItems(){
        return items;
    }
    void updateHistory(const string& input);
    void refresh();
    bool leftPressButton(const sf::Vector2f& mousepos, Graph_info* gi);
    bool rightPressButton(const sf::Vector2f mousepos);
    void wheelUp();
    void wheelDown();
    void resetPos();

private:
    sf::RectangleShape rect;            //sidebar rectangle
    vector<sf::Text*> items;               //strings to place on the sidebar

    sf::Font font;                      //used to draw text
    sf::Text sb_text;                   //used to draw strings on the window object
    float pos;
    float _left;
    float _width;

    bool removeFromHistory(int linendex);
};

#endif // SIDEBAR_H
