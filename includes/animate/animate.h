#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <fstream>
#include "../graph/graph.h"
#include "../graph_info/graph_info.h"

#include "../plot/plot.h"
#include "../system/system.h"
#include "../graph/graph.h"
#include "../token/function.h"
#include "../token/operator.h"
#include "../token/integer.h"
#include "../token/leftparen.h"
#include "../token/rightparen.h"

#include "./sidebar.h"
class animate{
public:
    animate();
    void run();
    void processEvents();
    void update();
    void render();
    void Draw();
private:
    Graph_info* _gi;
    sf::RenderWindow window;
    sf::CircleShape mousePoint;
    Graph _g;
    int command;
    sf::Font font;
    sf::Text myTextLabel;
    sf::Text EqText;
    sf::Text left;
    sf::Text right;
    bool mouseIn;
    string userInput;
    Queue<Token*> _postfix;
    System system;
    Plot _p;
    sf::RectangleShape hor;
    sf::RectangleShape ver;
    Sidebar sidebar;
    vector<sf::Text*> listoffunction;
    sf::RectangleShape background;
};

string mouse_pos_string(sf::RenderWindow& window);

#endif // GAME_H
