#include "system.h"

#include <iostream>

System::System(){

}
System::System(Graph_info* gi): graph(gi)
{
    _gi =gi;
    
}

void System :: set_info(Graph_info* gi){
    _gi = gi;
}

void System::Step(int command, Graph_info* graph_info){
    if (command == 4){
        _gi->panLeft();
    }
    else if (command == 6){
        _gi->panRight();
    }
    else if (command == 8){
        _gi->zoomIn();
    }
    else if (command == 9){
        _gi->zoomOut();
    }
    
    else if (command == 10){//resets
        _gi->_left = -10;
        _gi->_right = 10;
        _gi->_updown = 0;
    }
    else if(command == 11){
        _gi->panUp();
    }
    else if (command == 13){
        _gi->panDown();
    }
    graph.update(_gi);//updates graph info at end
}


void System::Draw(sf::RenderWindow& window){
    graph.draw(window);
}
