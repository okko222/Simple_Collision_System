#include <fstream>
#include <SFML/Graphics.hpp> 
#include <iostream>
#include <iomanip>
#include <string>
 
struct Rectangle {
    float xSpeed{}; 
    float ySpeed{};
    std::string name{};
    std::string type{};
    sf::Text text;
};
struct Circle{
    float xSpeed{};
    float ySpeed{};
    std::string name{}; 
    std::string type{};
    sf::Text text{};
};
struct Font {
    std::string name{};
    float size{};
    float R{}, G{}, B{};
};
//void collisionLogic(std::vector<sf::CircleShape>&, std::vector<Circle>&);
int main()
{    //--------display settings-------- 
     sf::ContextSettings settings;
     settings.antialiasingLevel = 10;
    //window.setFramerateLimit(60);
    //--------display settings-------- 
    //is there any usefull file functionalties that i missed
    std::ifstream inf("config.txt");
    std::vector<Rectangle> rectangles;
    std::vector<sf::RectangleShape>  rectangleShapes;
    std::vector<Circle> circles;
    std::vector<sf::CircleShape> circleShapes;
    std::vector<sf::Text> texts;
    

    //variable declaration and initi
    std::string type{}, name{};
    float xPos{}, yPos{}, xSpeed{}, ySpeed{}, R{}, G{}, B{}, width{}, height{}, radius{}, size{}, wHeight{}, wWidth{};
    //reading from the file 
    Font prop ;
    while (inf >> type)
    {

        if (type == "Rectangle")

        {
            Rectangle rectangle_structure;
            sf::RectangleShape rectangle_shape;
            inf >> name >> xPos >> yPos >> xSpeed >> ySpeed >> R >> G >> B >> width >> height;
            rectangle_shape.setPosition(xPos, yPos);
            rectangle_shape.setSize(sf::Vector2f(width, height));
            rectangle_shape.setFillColor(sf::Color(R, G, B));
            rectangle_structure.xSpeed = xSpeed;
            rectangle_structure.ySpeed = ySpeed;
            rectangle_structure.name = name;
            rectangle_structure.type = type;
            rectangles.push_back(rectangle_structure);
            rectangleShapes.push_back(rectangle_shape);
        }

        if (type == "Circle")
        {
            Circle circle_structure;
            sf::CircleShape circle_shape;
            inf >> name >> xPos >> yPos >> xSpeed >> ySpeed >> R >> G >> B >> radius;
            circle_shape.setPosition(xPos, yPos);
            circle_shape.setRadius(radius);
            circle_shape.setFillColor(sf::Color(R, G, B));
            circle_structure.xSpeed = xSpeed;
            circle_structure.ySpeed = ySpeed;
            circle_structure.name = name;
            circle_structure.type = type;
            circles.push_back(circle_structure);
            circleShapes.push_back(circle_shape);
            circles.push_back(circle_structure);
        }
        if (type == "Window")
        {
            inf >> wWidth >> wHeight;

        }
        if (type == "Font")
        {
            inf >> name >> size >> R >> G >> B;
            
            prop.name = name;
            prop.size = size;
            prop.R = R;
            prop.G = G;
            prop.B= B;

            
        }

       
    }
    
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "Simple Collision System", sf::Style::Default, settings);

    inf.close(); 
    //load a font so we can display some text 
   
   

   
    sf::Font font; 
    if (font.loadFromFile(prop.name))
    {

    }

  

  
    while (window.isOpen())
    {

        sf::Text text1;
        for (int i = 0; i < rectangleShapes.size(); ++i)
        {

            text1.setFont(font);
            rectangleShapes[i].setPosition(rectangleShapes[i].getPosition().x + rectangles[i].xSpeed, rectangleShapes[i].getPosition().y + rectangles[i].ySpeed);
            text1.setCharacterSize(prop.size);
            text1.setString(rectangles[i].name);
            text1.setFillColor(sf::Color(prop.R, prop.G, prop.B));
            text1.setOrigin(text1.getLocalBounds().width / 2, text1.getLocalBounds().height / 2);
            text1.setPosition(rectangleShapes[i].getPosition().x + rectangleShapes[i].getGlobalBounds().width / 2, rectangleShapes[i].getPosition().y + rectangleShapes[i].getGlobalBounds().height / 2);
            if (rectangleShapes[i].getGlobalBounds().top + rectangleShapes[i].getGlobalBounds().height > wHeight || rectangleShapes[i].getGlobalBounds().top < 0)
            {
                rectangles[i].xSpeed = rectangles[i].xSpeed;
                rectangles[i].ySpeed = -1 * rectangles[i].ySpeed;
                rectangleShapes[i].setPosition(rectangleShapes[i].getPosition().x + rectangles[i].xSpeed, rectangleShapes[i].getPosition().y + rectangles[i].ySpeed);
                text1.setPosition(rectangleShapes[i].getPosition().x + rectangleShapes[i].getGlobalBounds().width / 2, rectangleShapes[i].getPosition().y + rectangleShapes[i].getGlobalBounds().height / 2);

            }
            if (rectangleShapes[i].getGlobalBounds().left < 0 || rectangleShapes[i].getGlobalBounds().left + rectangleShapes[i].getGlobalBounds().width > wWidth)
            {
                rectangles[i].xSpeed = -1 * rectangles[i].xSpeed;
                rectangles[i].ySpeed = rectangles[i].ySpeed;
                rectangleShapes[i].setPosition(rectangleShapes[i].getPosition().x + rectangles[i].xSpeed, rectangleShapes[i].getPosition().y + rectangles[i].ySpeed);
                text1.setPosition(rectangleShapes[i].getPosition().x + rectangleShapes[i].getGlobalBounds().width / 2, rectangleShapes[i].getPosition().y + rectangleShapes[i].getGlobalBounds().height / 2);

            }
            rectangles[i].text = text1;


        }
        sf::Text text2;
        for (int i = 0; i < circleShapes.size(); ++i)
        {
            text2.setFont(font); //it should be readed from the file.
            text2.setCharacterSize(18);
            text2.setString(circles[i].name);
            text2.setFillColor(sf::Color(255, 255, 255));
            text2.setOrigin(text2.getLocalBounds().width / 2, text2.getLocalBounds().height / 2);

            circleShapes[i].setPosition(circleShapes[i].getPosition().x + circles[i].xSpeed, circleShapes[i].getPosition().y + circles[i].ySpeed);
            text2.setPosition(circleShapes[i].getPosition().x + circleShapes[i].getGlobalBounds().width / 2, circleShapes[i].getPosition().y + circleShapes[i].getGlobalBounds().height / 2);
            if (circleShapes[i].getGlobalBounds().top + circleShapes[i].getGlobalBounds().height > wHeight || circleShapes[i].getGlobalBounds().top < 0)
            {
                circles[i].xSpeed = circles[i].xSpeed;
                circles[i].ySpeed = -1 * circles[i].ySpeed;
                circleShapes[i].setPosition(circleShapes[i].getPosition().x + circles[i].xSpeed, circleShapes[i].getPosition().y + circles[i].ySpeed);
                text2.setPosition(circleShapes[i].getPosition().x + circleShapes[i].getGlobalBounds().width / 2, circleShapes[i].getPosition().y + circleShapes[i].getGlobalBounds().height / 2);
            }
            if (circleShapes[i].getGlobalBounds().left < 0 || circleShapes[i].getGlobalBounds().left + circleShapes[i].getGlobalBounds().width > wWidth)
            {
                circles[i].xSpeed = -1 * circles[i].xSpeed;
                circles[i].ySpeed = circles[i].ySpeed;
                circleShapes[i].setPosition(circleShapes[i].getPosition().x + circles[i].xSpeed, circleShapes[i].getPosition().y + circles[i].ySpeed);
                text2.setPosition(circleShapes[i].getPosition().x + circleShapes[i].getGlobalBounds().width / 2, circleShapes[i].getPosition().y + circleShapes[i].getGlobalBounds().height / 2);
            }


            circles[i].text = text2;
        }

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }



        window.clear(sf::Color::Black);
        //take in consideration to change to auto & 
        for (int i = 0; i < rectangleShapes.size(); ++i)
        {
            window.draw(rectangleShapes[i]);
            window.draw(rectangles[i].text);
        }
        for (int i = 0; i < circleShapes.size(); ++i)
        {
            window.draw(circleShapes[i]);
            window.draw(circles[i].text);
        }


        window.display();

    }
    return 0;
}
