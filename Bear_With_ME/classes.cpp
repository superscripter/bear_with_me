//
//  classes.cpp
//  Bear_With_ME
//
//  Created by Bryan Josloff on 10/26/18.
//  Copyright © 2018 Bryan Josloff. All rights reserved.
//

#include "classes.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <cmath>
#define PI 3.14159265


using namespace std;
    //speed is a great thing, othe rattibutes like attack stuff will be good too.
Pawn::Pawn(string new_name, int new_height, int new_width, sf::Sprite new_player, int new_stamina){
    //player.setOrigin(sf::Vector2f(new_width/2, new_height/2));
    name = new_name;
    height = new_height;
    width = new_width;
    player = new_player;
    stamina = new_stamina;
}

string Pawn:: get_name() {
    return name;
}
int Pawn:: get_height() {
    return height;
}
int Pawn:: get_width() {
    return width;
}
sf::Sprite Pawn::get_sprite(){
    return  player;
}
void Pawn::set_Sprite(sf::Sprite change){
    player = change;
}

int Pawn:: get_stamina() {
    return stamina;
}

void Pawn:: change_stamina(int new_inc, Meter &new_meter){
    
    stamina += new_inc;
    if(stamina > new_meter.get_num()){
        stamina = new_meter.get_num();
    }
    if(stamina < 0){
        stamina = 0;
    }
    new_meter.set_fill(stamina);
}


//////////////////////// ACTOR, this is for all generic objects in the game \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/
Actor::Actor(string new_name, int new_height, int new_width, sf::Sprite new_actor, int new_xpos, int new_ypos, double new_push){
    new_actor.setPosition(new_xpos, new_ypos);
    name = new_name;
    height = new_height;
    width = new_width;
    actor = new_actor;
    xpos = new_xpos;
    ypos = new_ypos;
    push_back = new_push;
    
}
Actor::Actor(){
    xpos = 0;
    ypos = 0;
}
string Actor:: get_name() {
    return name;
}
int Actor:: get_height() {
    return height;
}
int Actor:: get_width() {
    return width;
}
int Actor:: get_xpos(){
    return xpos;
}
int Actor:: get_ypos(){
    return ypos;
}
const double Actor:: get_push(){
    return push_back;
}
sf::Sprite Actor::get_sprite(){
    return  actor;
}
void Actor::set_Sprite(sf::Sprite change){
    actor = change;
}



Meter::Meter(sf::Color new_color, int new_attrition, int new_priority, int new_fill, int new_num):size(11){
    color = new_color;
    attrition = new_attrition;
    priority = new_priority;
    fill = new_fill;
    num = new_num; // size is alawys num max + 1;
    lines = new sf::VertexArray[size*2];    // still need a deconstructo for the lines
    drawn = new sf::VertexArray[size*2];
}

Meter::Meter(){
    return;
}
Meter::~Meter(){
    //delete lines;
    //delete drawn;
    return;
}
sf::Color Meter::get_color(){
    return color;
}
int Meter::get_num(){
    return num;
}
int Meter::get_priority(){
    return priority;
}
int Meter::get_attrition(){
    return attrition;
}

int Meter::get_fill(){
    return fill;
}
void Meter::set_fill(int new_fill){
    fill = new_fill;
}


sf::VertexArray* Meter::get_meter(){
    return drawn;
}
sf::VertexArray* Meter::get_lines(){
    return lines;
}
