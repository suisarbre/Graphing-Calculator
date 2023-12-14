#include "animate.h"
// #include "constants.h"
#include <iostream>
using namespace std;

#include <string>

animate::animate() : sidebar(SCREENWIDTH - SIDEBARWIDTH, SIDEBARWIDTH)
{
    userInput = "";
    _gi = new Graph_info("x^3",SCREENWIDTH,SCREENHEIGHT - SIDEBARWIDTH,-10,10);
    system = System(_gi);
    cout << "animate CTOR: TOP" << endl;
    window.create(sf::VideoMode(_gi->_screenwidth, _gi->_screenheight), "SFML window!");
    // VideoMode class has functions to detect screen size etc.
    // RenderWindow constructor has a third argumnet to set style
    // of the window: resize, fullscreen etc.

    // System will be implemented to manage a vector of objects to be animated.
    //   at that point, the constructor of the System class will take a vector
    //   of objects created by the animate object.
    //   animate will
    // _postfix.push(new Function("X"));
    // _postfix.push (new Integer(3));
    // _postfix.push(new Operator('+'));
    // _postfix.push(new Integer(-1));
    // _postfix.push(new Operator('^'));
    // _postfix.push (new Integer(2));
    // _postfix.push (new Operator('+'));
    // p = Plot(_gi,_postfix);
    // g = Graph(_gi,p.get_points());
    system = System(_gi);
    window.setFramerateLimit(60);

    mouseIn = true;

    mousePoint = sf::CircleShape();
    mousePoint.setRadius(5.0);
    mousePoint.setFillColor(sf::Color::Red);
    hor.setSize(sf::Vector2f(_gi->_screenwidth-SIDEBARWIDTH,1));
    ver.setSize(sf::Vector2f(1,_gi->_screenheight));
    hor.setPosition(sf::Vector2f(0,_gi->_screenheight/2));
    ver.setPosition(sf::Vector2f(_gi->_screenwidth/2,0));
    hor.setFillColor(sf::Color(88, 106, 106));
    ver.setFillColor(sf::Color(88, 106, 106));
    listoffunction = sidebar.getItems();
    cout << "Geme CTOR. preparing to load the font." << endl;
    //--- FONT ----------
    // font file must be in the "working directory:
    //      debug folder
    // Make sure working directory is where it should be and not
    //  inside the app file:
    //  Project->RUN->Working Folder
    //
    // font must be a member of the class.
    //  Will not work with a local declaration
    if (!font.loadFromFile("arial.ttf"))
    {
        cout << "animate() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }
    myTextLabel = sf::Text("Type here : ", font);
    myTextLabel.setCharacterSize(20);
    myTextLabel.setStyle(sf::Text::Bold);
    myTextLabel.setFillColor(sf::Color(88, 106, 106));
    myTextLabel.setPosition(sf::Vector2f(10, _gi->_screenheight - myTextLabel.getLocalBounds().height - 5));
    EqText = sf::Text(_gi->_equation, font);
    EqText.setCharacterSize(20);
    EqText.setStyle(sf::Text::Bold);
    EqText.setFillColor(sf::Color(88, 106, 106));
    EqText.setPosition(sf::Vector2f(10, _gi->_screenheight - EqText.getLocalBounds().height - 30));

    left = sf::Text(to_string(_gi->_left), font);
    left.setCharacterSize(20);
    left.setStyle(sf::Text::Bold);
    left.setFillColor(sf::Color(88, 106, 106));
    left.setPosition(sf::Vector2f(10, 0));
    
    right = sf::Text(to_string(_gi->_right), font);
    right.setCharacterSize(20);
    right.setStyle(sf::Text::Bold);
    right.setFillColor(sf::Color(88, 106, 106));
    right.setPosition(sf::Vector2f(_gi->_screenwidth - right.getLocalBounds().width  - SIDEBARWIDTH - 10, 0));
    background.setSize(sf::Vector2f(_gi->_screenwidth,_gi->_screenheight));
    background.setFillColor(sf::Color(184, 178, 208));//DAD4EF Lavender
    cout << "animate instantiated successfully." << endl;

}

void animate::Draw()
{
    window.draw(background);
    // Look at the data and based on the data, draw shapes on window object.
    system.Draw(window);
    if (mouseIn)
    {
        window.draw(mousePoint);
    }

    
    //- - - - - - - - - - - - - - - - - - -
    // getPosition() gives you screen coords, getPosition(window) gives you window coords
    // cout<<"mosue pos: "<<sf::Mouse::getPosition(window).x<<", "<<sf::Mouse::getPosition(window).y<<endl;
    //- - - - - - - - - - - - - - - - - - -
    // drawing Test: . . . . . . . . . . . .
    // This is how you draw text:)
    window.draw(myTextLabel);
    window.draw(EqText);
    window.draw(left);
    window.draw(right);
    window.draw(hor);
    window.draw(ver);
    //. . . . . . . . . . . . . . . . . . .
    sidebar.draw(window);
}

void animate::update()
{
    // cause changes to the data for the next frame
    system.Step(command,_gi);
    // if (command == 4){
    //     ver.move(sf::Vector2f((_gi->_right - _gi->_left)/100,0));

    // }
    // if(command == 6)
    ver.setPosition(sf::Vector2f((_gi->_screenwidth -SIDEBARWIDTH)/ 2 - ((_gi->_left + _gi->_right) / 2)*(((_gi->_screenwidth - SIDEBARWIDTH)/(_gi->_right - _gi->_left))),0));
    hor.setPosition(sf::Vector2f(0,_gi->_screenheight / 2 - _gi->_updown * (_gi->_screenwidth-SIDEBARWIDTH)/(_gi->_right - _gi->_left)));
    command = 0;
    if (mouseIn)
    {
        // mousePoint red dot:
        mousePoint.setPosition(sf::Mouse::getPosition(window).x - 5,
                               sf::Mouse::getPosition(window).y - 5);

        // mouse location text for sidebar:
        // sidebar[SB_MOUSE_POSITION] = mouse_pos_string(window);
    }
}

void animate::render()
{
    window.clear();
    Draw();
    window.display();
}

void animate::processEvents()
{
    sf::Event event;
    float mouseX, mouseY;
    while (window.pollEvent(event)) // or waitEvent
    {
        // check the type of the event...
        switch (event.type)
        {
        // window closed
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::TextEntered://Takes user input
            if (event.text.unicode < 128) { // Basic ASCII check
                char entered = static_cast<char>(event.text.unicode);
                if (entered == '\b' && !userInput.empty()) { // Handle backspace
                    userInput.pop_back();
                } else if (entered >= 32 && entered <= 126) { // Printable characters
                userInput += entered;
                }
                myTextLabel.setString("Type here : " + userInput);
            }
            break;

        // key pressed
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
            case sf::Keyboard::Left:
                // sidebar[SB_KEY_PRESSED] = "LEFT ARROW";
                command = 4;
                
                break;

            case sf::Keyboard::Right:
                // sidebar[SB_KEY_PRESSED] = "RIGHT ARROW";
                command = 6;
                
                break;

            case sf::Keyboard::Up:
                command = 8;
                break;

            case sf::Keyboard::Down:
                command = 9;
                break;

            case sf::Keyboard::PageUp:
                command = 11;
                break;

            case sf::Keyboard::PageDown:
                command = 13;
                break;
            case sf::Keyboard::Escape:
                // sidebar[SB_KEY_PRESSED] = "ESC: EXIT";
                window.close();
                break;
            case sf::Keyboard::F5:
                command = 10;
                break;
            }
            case sf::Keyboard::Enter:
                if (event.key.code == sf::Keyboard::Enter) {
                    // _gi->_equation = userInput;
                    if(_gi->setEq(userInput)){// if input is correct
                        sidebar.updateHistory(userInput);
                        EqText.setString(_gi->_equation);
                    }
                    else{
                        // EqText.setString("Invalid input!");
                    }
                    userInput.clear();
                }
            break;
        case sf::Event::MouseEntered:
            mouseIn = true;
            break;

        case sf::Event::MouseLeft:
            mouseIn = false;
            break;

        case sf::Event::MouseMoved:
            mouseX = event.mouseMove.x;
            mouseY = event.mouseMove.y;
            // Do something with it if you need to...
            break;
        case sf::Event::MouseButtonReleased:{
            sf::Vector2f clickPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if(event.mouseButton.button==sf::Mouse::Left){
                    if(sidebar.leftPressButton(clickPosition,_gi)){
                        EqText.setString(_gi->_equation);
                    }
                }
            }
            else if (event.mouseButton.button == sf::Mouse::Right){
                sidebar.rightPressButton(clickPosition);
            }
            else if (event.mouseButton.button == sf::Mouse::Middle){
                sidebar.resetPos();
            }

            break;
        }
        case sf::Event::MouseWheelScrolled:
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel){
                if(event.mouseWheelScroll.delta>0){
                    sidebar.wheelUp();
                }
                else if(event.mouseWheelScroll.delta<0){
                    sidebar.wheelDown();
                }
            }
            break;

        default:
            break;
        }
            left.setString(to_string(_gi->_left));
            right.setString(to_string(_gi->_right));
    }
}
void animate::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render(); // clear/draw/display
    }
    cout << endl
         << "-------ANIMATE MAIN LOOP EXITING ------------" << endl;
}

string mouse_pos_string(sf::RenderWindow &window)
{
    return "(" +
           to_string(sf::Mouse::getPosition(window).x) +
           ", " +
           to_string(sf::Mouse::getPosition(window).y) +
           ")";
}
