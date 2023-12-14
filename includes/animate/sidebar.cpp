#include "sidebar.h"

    const double VERTICAL_LINE_SPACING = 30;
    const double LEFT_MARGIN = 10.0;

Sidebar::Sidebar()
{
}
Sidebar::~Sidebar() {
    for (sf::Text* textItem : items) {
        delete textItem;
    }
}
Sidebar::Sidebar(float left, float width) : _left(left), _width(width)
{
    cout << "Sidebar CTOR: TOP" << endl;
    items.reserve(50);

    // set up the sidebar rectangle:
    rect.setFillColor(sf::Color(88, 106, 106));
    rect.setPosition(sf::Vector2f(left, 0));
    rect.setSize(sf::Vector2f(width, 1000));
    cout << "Sidebar CTOR: about to load font." << endl;

    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // the font file must be in the "working directory"
    //  check projects->run->working directory
    //       [Make sure it's not pointing to the app file]

    if (!font.loadFromFile("Roboto-Thin.ttf"))
    {
        cout << "Sidebar() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }
    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    cout << "Sidebar CTOR: loaded font." << endl;

    //. . . . . text / font problems: . . . . . . . .
    // initializing text object in this way caused problems
    // (hangs!)
    // only when sb_text was a private member and worked fine
    // when it was a public member. Probably not releavant,
    // but still strange!
    //
    // sb_text = sf::Text("Initial String for myTextLabel", font);
    //
    //. . . . . . . . . . . . . . . . . . . . . . . . .
    cout << "Sidebar CTOR: Text object initialized." << endl;
    sb_text.setFont(font);
    sb_text.setCharacterSize(20);
    sb_text.setStyle(sf::Text::Bold);
    sb_text.setFillColor(sf::Color::Yellow);
    pos = 0;



    ifstream f;
    f.open("../../History.txt");
    if (f.fail()){
        cout<<"History.txt failed to load"<<endl;
        exit(1);
    }
    string line;
    float height = 10;
    while (getline(f, line)) {
        sf::Text* textItem = new sf::Text(line, font);
        textItem->setCharacterSize(20);
        textItem->setFillColor(sf::Color(218, 212, 239)); // Set the color as needed
        textItem->setPosition(sf::Vector2f(_left + LEFT_MARGIN, height));
        textItem->setStyle(sf::Text::Bold);
        items.push_back(textItem);
        height += VERTICAL_LINE_SPACING;
    }
    
    // Fill the items vector with empty strings so that we can use [] to read them:
    f.close();
    cout << "Sidebar: CTOR: Exit." << endl;
}

void Sidebar::draw(sf::RenderWindow &window)
{


    window.draw(rect);
    for (sf::Text* textItem : items) {
        textItem->move(sf::Vector2f(0,pos));//moves to the desired pos and then draw
        window.draw(*textItem);
        textItem->move(sf::Vector2f(0,-pos));//after draw move back to original pos
    }
}

sf::Text* Sidebar::operator[](int index)
{
    return items[index];
}



void Sidebar::updateHistory(const string& input){
    ofstream f;
    f.open("../../History.txt",ios::app);
    if (f.fail()){
        cout<<"History.txt failed to load"<<endl;
        exit(1);
    }
    f << input <<endl;
    f.close();

    refresh();
}

void Sidebar::refresh() {
    // Clear existing items
    for (sf::Text* textItem : items) {
        delete textItem;
    }
    items.clear();

    // Read the updated history and repopulate items
    ifstream f;
    f.open("../../History.txt");
    if (f.fail()) {
        cout << "History.txt failed to load" << endl;
        exit(1);
    }

    string line;
    float height = 10;
    while (getline(f, line)) {
        sf::Text* textItem = new sf::Text(line, font);
        textItem->setCharacterSize(20);
        textItem->setFillColor(sf::Color(218, 212, 239));
        textItem->setPosition(sf::Vector2f(_left + LEFT_MARGIN, height));
        textItem->setStyle(sf::Text::Bold);
        items.push_back(textItem);
        height += VERTICAL_LINE_SPACING;
    }
    f.close();
}


bool Sidebar::leftPressButton(const sf::Vector2f& mousepos, Graph_info* gi){
    for (int i = 0; i<items.size();i++){
        if (items[i]->getGlobalBounds().contains(mousepos)){
            gi->setEq(items[i]->getString());
            return 1;
        }
    }
    return false;
}

bool Sidebar::rightPressButton(const sf::Vector2f mousepos){//Credit to Natalie for the idea :D
    int clickedItemIndex = -1;
    for (int i = 0; i < items.size(); i++) {
        if (items[i]->getGlobalBounds().contains(mousepos)) {
            clickedItemIndex = i;
            cout<<clickedItemIndex<<endl;
            break;
        }
    }

    if (clickedItemIndex == -1) {
        return false; // No item was clicked
    }

    if (!removeFromHistory(clickedItemIndex)) {
        return false; // Failed to update the history file
    }

    // Refresh the sidebar
    refresh();
    return true;
}

bool Sidebar::removeFromHistory(int lineIndex) {
    vector<string> lines;
    string line;
    ifstream inf("../../History.txt");
    if (inf.fail()) {
        cerr << "Failed to open History.txt for reading." << endl;
        return false;
    }

    // Read all lines into the vector
    while (getline(inf, line)) {
        lines.push_back(line);
    }
    inf.close();

    // Check if lineIndex is valid
    if (lineIndex < 0 || lineIndex >= lines.size()) {
        return false;
    }

    // Remove the specified line
    lines.erase(lines.begin() + lineIndex);

    // Write the updated content back to the file
    ofstream of("../../History.txt");
    if (of.fail()) {
        cout << "History.txt failed to load" << endl;
        return false;
    }

    for (int i = 0; i<lines.size();i++) {
        of << lines[i] << endl;
    }

    return true;
}

void Sidebar::wheelUp(){
    pos += 10;
    if (pos >0) pos = 0;
}
void Sidebar::wheelDown(){
    pos -= 10;
    
}
void Sidebar::resetPos(){
    pos = 0;
}