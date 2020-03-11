//
//  head.cpp
//  Bear_With_ME
//
//  Created by Bryan Josloff on 10/26/18.
//  Copyright © 2018 Bryan Josloff. All rights reserved.
//

#include "functions.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#
#define PI 3.14159265
#include <iostream>  // delete me

using namespace std;

double square(double num) {
    return num*num;
    
}

int distance (int x1, int y1, int x2, int y2){
    return sqrt(square(x1-x2) + square (y1-y2));
    }


///////////////////////// random number generator
int random_generator(int tot){
    
    int rando;
    rando = rand() % tot; // top - bottom + 1 is the best form
    
    return rando;
}



///////////////////////// Mkaes vertical grid lines
void line_fillv(sf::VertexArray* &vert, int game_width, int game_height, int windowsize_x, int windowsize_y){
    
    int x = 0;              // these varibles exit in case we make windowsizes not global
    int y = windowsize_y;
    
    for(int i = 0; i < game_width + 1; i++) {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(x, 0);
        line[1].position = sf::Vector2f(x, game_height*y);
        line[0].color = sf::Color::White;
        line[1].color = sf::Color::White;
        if(i == 1 || i == game_width -1){
            line[0].color = sf::Color::Red;
            line[1].color = sf::Color::Red;
        }
        vert[i] = line;
        x += windowsize_x;
    }
    return;
}

///////////////////////// Mkaes horizontal grid lines
void line_fillh(sf::VertexArray* &horz, int game_width, int game_height, int windowsize_x, int windowsize_y){
    
    int x = windowsize_x;
    int y = 0;
    
        for(int i = 0; i < game_height + 1; i++) {
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = sf::Vector2f(0, y);
            line[1].position = sf::Vector2f(game_width*x, y);
            line[0].color = sf::Color::White;
            line[1].color = sf::Color::White;
            if(i == 1 || i == game_height -1){
                line[0].color = sf::Color::Red;
                line[1].color = sf::Color::Red;
            }
            *(horz + i) = line;
            y += windowsize_y;
        
        }
    return;
}


void fill_objects(Actor** &a, const sf::Sprite &obj, int num_obj, int offset, int game_width, int game_height, int windowsize_x, int windowsize_y, double bush_push){
    
    int rand = 1;
    int start_y = 0;
    int start_x = 0;
    int tile_num = game_width*game_height;
    
    for(int i = 0; i < tile_num; i++){
        int delta_x = 0;
        for(int j = 0; j < num_obj; j++){
            rand = random_generator(5); // to make the bushes more shuffeld up make rands a double
            if(rand >= 0 && rand <=3){
                a[i][j] = Actor("bush",300,300,obj,start_x + delta_x,start_y + rand*offset,bush_push);
            }
            else{
                a[i][j] =  Actor();
            }
            delta_x += offset;
        }
        start_x += windowsize_x;
        if(start_x == game_width*windowsize_x){
            start_x = 0;
            start_y += windowsize_y;
        }
    }
    return;
}



 ///////////////////////////////// Invisble Walls///////////////////////
void walls(sf::View &view, int windowsize_x, int windowsize_y, int game_width, int game_height){
    
    if( (windowsize_y - view.getCenter().y) >= 0){                  // top wall
        view.move(0,(windowsize_y - view.getCenter().y));
    }
    if( ((game_height-1)*windowsize_y) - view.getCenter().y  <= 0){     // bottom wall
        view.move(0,((game_height-1)*windowsize_y) - view.getCenter().y);
    }
    if( ( ((game_width-1)*windowsize_x) - view.getCenter().x) <= 0){      // right wall
        view.move( (((game_width-1)*windowsize_x) - view.getCenter().x),0);
    }
    if( windowsize_x - view.getCenter().x >= 0){                        //left wall
        view.move((windowsize_x - view.getCenter().x),0);
    }
    
    return;
}


///////////////////////////////// Movement ///////////////////////

void movement (sf::View &view, bool rush, bool diagonal, bool up, bool down, bool left, bool right, double speed, double d_move, double rush_factor, double rotate){
    
    
    if(!rush){
        /////////////// Here we check to make sure we are not rushing
        if(up && left){
            view.move(sf::Vector2f(-d_move*speed , -d_move*speed ));
            diagonal = true;
        }
        if(up && right){
            view.move(sf::Vector2f(d_move*speed , -d_move*speed ));
            diagonal = true;
        }
        if(down && left){
            view.move(sf::Vector2f(-d_move*speed , d_move*speed ));
            diagonal = true;
        }
        if(down && right){
            view.move(sf::Vector2f(d_move*speed , d_move*speed ));
            diagonal = true;
        }
        
        if(!diagonal){                  //////// if we are not mvoing diagnaolly we move through here
            
            if (up)
            {
                view.move(sf::Vector2f(0 , -speed ));
            }
            if (down)
            {
                view.move(sf::Vector2f(0, speed ));
            }
            if (left)
            {
                view.move(sf::Vector2f(-speed,0));
            }
            if (right)
            {
                view.move(sf::Vector2f(speed, 0));
            }
            
        }
        
    }
    
    else {      ///if we are infact rushing this code is activated
        
        if (up)
        {
            view.move(sf::Vector2f(rush_factor*speed*cos(rotate*(PI/180)), -rush_factor*speed*sin(rotate*(PI/180)) ));
        }
        else if (down)
        {
            view.move(sf::Vector2f(-speed*cos(rotate*(PI/180)), speed*sin(rotate*(PI/180)) ));
        }
        else if (left)
        {
            view.move(sf::Vector2f(-(1/rush_factor)*speed*sin(rotate*(PI/180)), -(1/rush_factor)*speed*cos(rotate*(PI/180))));
        }
        else if (right)
        {
            view.move(sf::Vector2f((1/rush_factor)*speed*sin(rotate*(PI/180)), (1/rush_factor)*speed*cos(rotate*(PI/180))));
        }
        
    }
    return;
}

///////////////////////////////// Drawing object array ///////////////////////
void draw_array (sf::RenderWindow &window,const sf::View &view, Actor** a, int num_bushes, int windowsize_x, int windowsize_y, int game_width, int game_height){
    int xx = view.getCenter().x /windowsize_x;
    int yy = view.getCenter().y /windowsize_y;
    
    if(view.getCenter().x == (game_width-1)*windowsize_x){ //fixes bug of right most invisible wall
        --xx;
    }
    if(view.getCenter().y == (game_height-1)*windowsize_y){ //fixes bug of bottom most invisible wall
        --yy;
    }
    
    int move = 0;
    
    for(int k = 0; k < 3; k ++){
        for(int i = (xx + game_width*yy + move - (game_width+1)); i < (xx + game_width*yy + - (game_width-2) + move); i++){
            for(int j = 0; j < num_bushes; j++){
                window.draw(a[i][j].get_sprite());
            }
        }
        move += game_width;
    }
    return;
}

///////////////////////////////// collisions of object array ///////////////////////
void collide_array (sf::View &view, Actor** a, int num_bushes, int windowsize_x, int windowsize_y, int game_width, int game_height, double d_move){
    
    int xx = view.getCenter().x /windowsize_x;
    int yy = view.getCenter().y /windowsize_y;
    
    if(view.getCenter().x == (game_width-1)*windowsize_x){ //fixes bug of right most invisible wall
        --xx;
    }
    if(view.getCenter().y == (game_height-1)*windowsize_y){ //fixes bug of bottom most invisible wall
        --yy;
    }
    int move = 0;
    
    int critical_d =  200;
    for(int k = 0; k < 3; k ++){
        for(int i = (xx + game_width*yy + move - (game_width+1)); i < (xx + game_width*yy + - (game_width-2) + move); i++){
            for(int j = 0; j < num_bushes; j++){
                if( (distance(a[i][j].get_xpos() + a[i][j].get_width()/2, a[i][j].get_ypos() + a[i][j].get_width()/2,view.getCenter().x,view.getCenter().y ) <= critical_d)) {
                    double x_mov =0;
                    double y_mov =0;
                    
                    if( view.getCenter().x > (a[i][j].get_xpos() + a[i][j].get_width()/2)){
                        x_mov += a[i][j].get_push()*d_move;
                    }
                    else{
                         x_mov -= a[i][j].get_push()*d_move;
                    }
                    if( view.getCenter().y > ( a[i][j].get_ypos() + a[i][j].get_width()/2)){
                        y_mov += a[i][j].get_push()*d_move;
                    }
                    else{
                        y_mov -= a[i][j].get_push()*d_move;
                    }
                    view.move(x_mov,y_mov);
                }
                
            }
            
        }
        move += game_width;
    }
    return;
}


///////////////////////////////// sorting meters ///////////////////////
void sort_meter(Meter meters[4], Meter &m0, Meter &m1, Meter &m2, Meter &m3){
    meters[m0.get_priority()] = m0;
    meters[m1.get_priority()] = m1;
    meters[m2.get_priority()] = m2;
    meters[m3.get_priority()] = m3;
}

///////////////////////////////// this meter function is gonna be one chunky boy
void create_meters(Meter meters[4],const sf::View &view, int windowsize_x, int windowsize_y){ // still need a deconstructo for the lines
 
    
    int pdif_x;
    int pdif_y;
    int length_high = 100;
    double to_rotate = 0;           // remove me most liekly
    double conv = 180/(2*PI);
    
    for(int i =0; i < 4; i++){
        int length = 100;
        int num = (meters + i)->get_num();
        sf::Color color_n = (meters + i)->get_color();
        
        if(i == 0){     //blue for tests
            pdif_x = -1.5*length*.866*.25;
            pdif_y = length*.8;
            to_rotate = 0;//(1/conv)*( (360/(meters + i)->get_num() - 45) / 2) ; //radian degree to rotate
        }
        
        if(i == 1){     //orage for tests
            pdif_x = 1.5*length*.866;
            pdif_y = -length*.5;
            length = .5*length;
            to_rotate = 0;
        }
        
        if(i == 2){     //yellow for tests
            pdif_x = 1.5*length*.866;
            pdif_y = length*.5;
            length = .5*length;
            to_rotate = 0;
        }
        
        if(i == 3){     // red for tests
            pdif_x = 1.5*length*.866;
            pdif_y = 3*length*.5;
            length = .5*length;
            to_rotate = 0;
        }
        
        int center_x =  view.getCenter().x +  windowsize_x/2 - 2*length_high + pdif_x;
        int center_y =  view.getCenter().y + windowsize_y/2 - 2*length_high + pdif_y;
        
        
        
        double theta = 0;
        double theta_d = (360/ ((double)num) );
        
        
        sf::VertexArray stat(sf::TriangleFan, 3 );
        
        sf::Color blank_color(151,70,0.255);
        sf::Color color_u = blank_color;
        
        for(int j = 0; j < num ; j ++){

            stat[0].position = sf::Vector2f(center_x ,center_y );
            
            stat[1].position = sf::Vector2f( center_x + cos( (1/conv)*theta + to_rotate )*length,
                                            center_y +  sin( (1/conv)*theta + to_rotate )*length);
            
             theta += theta_d/2;
            
            stat[2].position = sf::Vector2f( center_x + cos( (1/conv)*theta + to_rotate )*length,
                                            center_y +  sin( (1/conv)*theta + to_rotate )*length);
            
            
            if(j < (meters + i)->get_fill()){
               color_u = color_n;
            }
            else{
                color_u = blank_color;
            }
            
            if((meters + i)->get_fill() == 0){
                color_u = blank_color;
            }
            stat[0].color = color_u;
            stat[1].color = color_u;
            stat[2].color = color_u;
            
           
            
            *(meters[i].get_meter() + j) = stat;
        }
        
    theta = 0;
        
             for(int j = 0; j < num; j ++){
                 sf::VertexArray new_line(sf::Lines, 2);
                 sf::VertexArray new_line2(sf::Lines, 2);
                 
            new_line[0].position = sf::Vector2f(center_x, center_y);
                 
            new_line[1].position = sf::Vector2f( center_x + cos( (1/conv)*theta + to_rotate )*length,
                                                center_y +  sin( (1/conv)*theta + to_rotate )*length);
                

            
            new_line2[0].position = sf::Vector2f( center_x + cos( (1/conv)*theta + to_rotate )*length,
                                                 center_y +  sin( (1/conv)*theta + to_rotate )*length);
            
            theta += theta_d/2;
            
            new_line2[1].position = sf::Vector2f( center_x + cos( (1/conv)*theta + to_rotate )*length,
                                                 center_y +  sin( (1/conv)*theta + to_rotate )*length);
            
            new_line[0].color = sf::Color::Black;
            new_line[1].color = sf::Color::Black;
            new_line2[0].color = sf::Color::Black;
            new_line2[1].color = sf::Color::Black;
            
            *(meters[i].get_lines() + j) = new_line;
            *(meters[i].get_lines() + j + 11) = new_line2; // that eleven is the max + 1
        }
        
    }
}

