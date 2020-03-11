//
//  head.h
//  Bear_With_ME
//
//  Created by Bryan Josloff on 10/26/18.
//  Copyright © 2018 Bryan Josloff. All rights reserved.
//

#ifndef functions_h
#define functions_h
#include "classes.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

//////////////// Math Functions ////////////

double square(double num);

int distance (int x1, int y1, int x2, int y2);


///////////////// radno generator /////////
int random_generator(int tot);


/////////////////// Line filler functions ///////////////
void line_fillv(sf::VertexArray* &vert, int game_width, int game_height, int windowsize_x, int windowsize_y);
void line_fillh(sf::VertexArray* &vert, int game_width, int game_height, int windowsize_x, int windowsize_y);

/////////////////// Fill the map ///////////////
void fill_objects(Actor** &a, const sf::Sprite &obj, int num_obj, int offset, int game_width, int game_height, int windowsize_x, int windowsize_y, double bush_push);

 ///////////////////////////////// Invisble Walls///////////////////////
void walls(sf::View &view, int windowsize_x, int windowsize_y, int game_width, int game_height);

///////////////////////////////// Movement ///////////////////////
void movement (sf::View &view, bool rush, bool diagonal, bool up, bool down, bool left, bool right, double speed, double d_move, double rush_factor, double rotate);

///////////////////////////////// Drawing object array ///////////////////////
void draw_array (sf::RenderWindow &window, const sf::View &view, Actor** a, int num_bushes, int windowsize_x, int windowsize_y, int game_width, int game_height);

///////////////////////////////// colliosns of object array ///////////////////////
void collide_array (sf::View &view, Actor** a, int num_bushes, int windowsize_x, int windowsize_y, int game_width, int game_height, double d_move);

/////////////////////////////////\\\\\\\\\\\/\/\/\////////////////////////// METERS
void sort_meter(Meter meters[4], Meter& m0, Meter &m1, Meter &m2, Meter &m3);

void create_meters(Meter meters[4],const sf::View &view, int windowsize_x, int windowsize_y);


/////////////////////////////////\\\\\\\\\\\/\/\/\////////////////////////// METERS
#endif /* head_h */
