//
//  classes.hpp
//  Bear_With_ME
//
//  Created by Bryan Josloff on 10/26/18.
//  Copyright © 2018 Bryan Josloff. All rights reserved.
//

#ifndef classes_h
#define classes_h

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>


using namespace std;

//////////////////////// METER, this is for all status meters in the game \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/
class Meter {
    
public:
    
    Meter(sf::Color new_color, int new_attrition, int new_priority, int new_fill, int new_num);
    Meter();
    ~Meter();
    
    sf::Color get_color(); // still need a deconstructo for the lines
    int get_num();
    int get_priority();
    int get_attrition();
    
    int get_fill();
    void set_fill(int new_fill);
    
    sf::VertexArray* get_meter();
    sf::VertexArray* get_lines();
    
    
private:
    sf::Color color;
    int attrition;
    int priority;
    int fill;
    int num;
    int status;
    int size;
    sf::VertexArray* drawn;
    sf::VertexArray* lines;
};

class Pawn{
    
public:
    
    Pawn(string new_name, int new_height, int new_width, sf::Sprite new_player, int new_stamina);
                                // so I want to pass an array of all the goodies but for now just stamina is fine
    string get_name();
    int get_height();
    int get_width();
    sf::Sprite get_sprite();
    void set_Sprite(sf::Sprite change);
    
    int get_stamina();
    void change_stamina(int new_inc, Meter &new_meter);
    
private:
    string name;
    int height;
    int width;
    int stamina;
    sf::Sprite player;
};

class Actor{
    
public:
    
    Actor(string new_name, int new_height, int new_width, sf::Sprite new_actor, int new_xpos, int new_ypos, double new_push);
    Actor();
    string get_name();
    int get_height();
    int get_width();
    int get_xpos();
    int get_ypos();
    const double get_push();
    sf::Sprite get_sprite();
    void set_Sprite(sf::Sprite change);
    
private:
    string name;
    int height;
    int width;
    int xpos;
    int ypos;
    double push_back;
    sf::Sprite actor;
};




#endif
