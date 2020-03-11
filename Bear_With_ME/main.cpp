// Bryan Josloff, October 2018, BEAR WITH ME

// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "ResourcePath.hpp" // Here is a small helper for you! Have a look.

#include "functions.h"
#include "classes.h"
#define PI 3.14159265

using namespace std;



int main()  {
    srand((int)time(0));
    const double conv = 180/(2*PI); // goes from radians to degrees
   
    

    //////////////////////////////// GAME VARIBLES \\\\\\\\\\\\\\\\\\\\/
    const int game_width = 5;
    const int game_height = 5;
    
    const int windowsize_x = 2200;
    const int windowsize_y = 1300;
    const int window_center_x = windowsize_x/2;
    const int window_center_y = windowsize_y/2;
    
    bool rush = false;
  
    sf::Clock game_clock;
    sf::Clock rush_clock;
    int time_holder = -1;
    int rush_holder = -1; // we use this to ignore an imeadite gain in stamina after ending rush mode
    //////////////////////////////////////////////////////////////////meter objects
    int max_num = 10; //// max number of triangles allowed is 10 /
    // if you want to add more youll have to change the size intilaizer in the cosntructor of meter and the offset in the function for creating the lines.
    sf::Color  c_cold(0,255,255,255);
    sf::Color  c_hunger(255,171,0,255);
    sf::Color  c_stamina(255,255,21.255);
    sf::Color  c_health(255,0,0.255);
   
    Meter meter_stamina(c_stamina, 5, 0, 0, 6); // attrition, priotirty, fill, number of triganles
    Meter meter_hunger(c_hunger, 5, 1, 0, 6);
    Meter meter_cold(c_cold, 5, 2, 0, 6);
    Meter meter_health(c_health, 5, 3, 0, 6);
    Meter meters[4];
    ///////////////////////////////// GAME VARIBLES \\\\\\\\\\\\\\\\\\\\/
    
    
    ///////////////// Window
    sf::RenderWindow window(sf::VideoMode(2200, 1300), "Bear With Me");
    ///////////////// Window
    
    ////////////////////////////// Icon \\\\\\\\\\\\\\\\\\\\/
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "why.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    ////////////////////////////// Icon \\\\\\\\\\\\\\\\\\\\/
    
    ////////////////////////////// Background \\\\\\\\\\\\\\\\\\\\/   //||\\ background shoul be a vecotr array rectangle
    sf::View view(sf::Vector2f(windowsize_x, windowsize_y), sf::Vector2f(windowsize_x, windowsize_y));
    sf::Texture texture_background;                     // loads texture for backgroud
    if (!texture_background.loadFromFile(resourcePath() + "background.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite background(texture_background); // creates background sprite from that texture
    background.setOrigin(sf::Vector2f(window_center_x, window_center_y));
    ////////////////////////////// Background \\\\\\\\\\\\\\\\\\\\/
    
    
    ////////////////////////////// Bush \\\\\\\\\\\\\\\\\\\\/
    sf::Texture texture_bush;                     // sprite stuff for bush
    if (!texture_bush.loadFromFile(resourcePath() + "bush.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite bush(texture_bush);
    ////////////////////////////// Bush\\\\\\\\\\\\\\\\\\\\/
    
    /////////////////////////////////////// Lots of Bushes ///////////////////////////////////////
    int num_bushes = 7; //number of bushes per tile
    int bush_width = 300; //full width of a bush
    int tile_num = game_width*game_height;
    double bush_push = 1;
    
    Actor** a = new Actor*[tile_num];
    
    for(int i =0; i < tile_num; i++){
        a[i] = new Actor[num_bushes];
    }
    
    // imovibale objects should have a push equal to player_sped
    fill_objects(a, bush, num_bushes, bush_width, game_width, game_height, windowsize_x, windowsize_y, bush_push);
    /////////////////////////////////////// Lots of Bushes ///////////////////////////////////////
    
    
    //////////////////////////////////// Grid Lines//////////////////////////////////
    sf::VertexArray* vert = new sf::VertexArray[game_width + 1];
    line_fillv(vert, game_width, game_height, windowsize_x, windowsize_y);
    
    sf::VertexArray* horz = new sf::VertexArray[game_height + 1];
    line_fillh(horz, game_width, game_height, windowsize_x, windowsize_y);
    //////////////////////////////////// Grid Lines //////////////////////////////////
    
    
    
    
    
    //@/////////////////////////////////// PLAYER //////////////////////////////////
    //////////////////////////////////// PLAYER //////////////////////////////////
    sf::Texture texture_stand;                  // loads texture for the player stadning
    if (!texture_stand.loadFromFile(resourcePath() + "bear.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite player(texture_stand);     // creates sprite with that texture
    
    
    sf::Texture texture_claw;                     // sprite stuff for bush
    if (!texture_claw.loadFromFile(resourcePath() + "claw.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite claw(texture_claw);
    
    
    
    Pawn Player ("player", 242, 272, player, 6); // 6 is stamina for now
    
    
    
    player.setOrigin(sf::Vector2f(Player.get_width()/2, Player.get_height()/2));
    
    claw.setOrigin(sf::Vector2f(Player.get_width()/2, Player.get_height()/2));  //
    int inc = 1;
    // so the claw has its own atrributes like swing speed.
    
        // this code is good ebcuase we dont change the sprite of the palyer jsut the texture!
        //might need to change this as well when we become new animals or even in rush mode or even for turning radius
    
    
    
    //////////////////////////////////// PLAYER VARIABLES //////////////////////////////////
    
    /////////////////////////////////// PLAYER //////////////////////////////////
    
    
    
    
    
    //////////////////////////////////// RUsh PLayer //////////////////////////////////
    sf::Texture texture_rush;           // creates texture for when the player is in rush mode
    if (!texture_rush.loadFromFile(resourcePath() + "bear_rush.jpg")) {
        return EXIT_FAILURE;
    }
   //////////////////////////////////// RUsh PLayer //////////////////////////////////
    
    
    ///////////////////////// FONTS AND TEXT \\\\\\\\\\\\\\\\\/
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    ///////////////////////// FONTS AND TEXT \\\\\\\\\\\\\\\\\/
 
    
    ///////////////////////////////// MUSIC SOUNDS \\\\\\\\\\\\\\\\\/
    /*
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "pump.ogg")) {
        return EXIT_FAILURE;
    }

    // Play the music
    music.play();
     */
    ///////////////////////////////// MUSIC SOUNDS \\\\\\\\\\\\\\\\\/
   
    bool swipe = false;
    bool reverse = false;
    
    while (window.isOpen()) // game loop starts
    {
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // left click...
        {
            swipe = true;
        }
    
        sf::Time time_elapsed = game_clock.getElapsedTime();
        sf::Time rush_elapsed = rush_clock.getElapsedTime();
        
        
        ///////////////////////////////// Process events \\\\\\\\\\\\\\\\\/
        window.setKeyRepeatEnabled(false);
        
        sf::Event event;
        while (window.pollEvent(event))             // remeber oinly one event can be valid at a timme!
        {
            if (event.type == sf::Event::Closed)
            window.close();
           
            if (event.type == sf::Event::KeyPressed)
            {
                
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                
                
                
                if (  (event.key.code == sf::Keyboard::E) && rush) {
                    rush = false; // then we are rushing
                    player.setTexture(texture_stand);
                    break; // this is here so the next if statmetn doesnt get tripped by accident
                }
                if (  (event.key.code == sf::Keyboard::E) && Player.get_stamina() >= 4) { // 4 is the min triangles needed to rush
                    rush = true; // then we are rushing
                    player.setTexture(texture_rush);
                    }
                }
            }
            ///////////////////////////////// Process events \\\\\\\\\\\\\\\\\/
        
        /////////////////// Changing player if running ///////
       
        if (Player.get_stamina() == 0){ //this sets us abck to stadning when re run out of juice
            rush = false;
            player.setTexture(texture_stand);
        }
         /////////////////// Changing player if running ///////
        
        ///////////////////////////// Rotation \\\\\\\\\\\\\\\\\\\\\\/
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
        
        double tany = -1*(localPosition.y - window_center_y);
        double tanx = localPosition.x - window_center_x;
        double rotate = (atan2(tany, tanx)) * (180 / PI);
       
        if(rotate < 0)
        {
            rotate = 360 - (-rotate);
        }
        player.setRotation(-1 * rotate);
        
        
        double rotate1 = rotate + inc;
        
        if(swipe){      // animate funtion
            
            if(inc == 45) {reverse = true;}
            if(inc == 0) { reverse = false; swipe = false;}
            if(reverse){
                inc--;
            }
            else{
            inc ++;
            }
        }
        
        
        claw.setRotation(-1*rotate1);
        
        ///////////////////////////// Rotation \\\\\\\\\\\\\\\\\\\\\\/
        
    
        
        ///////////////////////////////// Movement ////////////////////////
        double speed = 4;  //player_speed // belongs at 2
        double d_move = .707;
        double rush_factor = 2;
        
        bool up = (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W));
        bool down = (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S));
        bool left = (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A));
        bool right = (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D));
        bool diagonal = false;
        
        movement (view,rush,diagonal, up,down, left, right, speed, d_move, rush_factor, rotate);
         ///////////////////////////////// Movement ///////////////////////\
        
        
        ///////////////////////////////// Invisble Walls////////////////////////
        walls(view,windowsize_x,windowsize_y,game_width,game_height);
        ///////////////////////////////// Invisble Walls////////////////////////
        
        
        /////////////////////////////// COLLISIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\/
         collide_array(view, a, num_bushes, windowsize_x, windowsize_y,  game_width, game_height, d_move);
        /////////////////////////////// COLLISIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\/
        
        
        ///////////////////////////////// Invisble Walls////////////////////////
        walls(view,windowsize_x,windowsize_y,game_width,game_height);
        ///////////////////////////////// Invisble Walls///////////////////////
        
        
        ///////////////////////////////// Status Meters \\\\\\\\\\\\\\\\\\\\\\\\/
        
        ////////////////////////// STAMINA UPDATE
     
        if(rush){
            // i want it to degrae at one triagnle at every half a second, well maybe sounds complicated, we will wait
            if( ( ((int)time_elapsed.asSeconds() % 1 == 0 ) &&  (int)time_elapsed.asSeconds() != time_holder  )){ // 1 second as interval
                Player.change_stamina(-1, meter_stamina);
                rush_clock.restart();
            }
        }
        else if((((int)rush_elapsed.asSeconds() % meter_stamina.get_attrition()) == 0)&&(int)rush_elapsed.asSeconds()!= rush_holder){
            Player.change_stamina(1, meter_stamina);
        }
        rush_holder = (int)rush_elapsed.asSeconds();  // with these two clocks, stamian regerntes wihtin 1 second of perfection
        time_holder = (int)time_elapsed.asSeconds();        // which is good enough for sure
        
        
        // for the cool color effect and swtitch the meters, I dont have to change any colors, all i gotta do is change their priorty, the code is there and things will be arranged correctly no problem, then I just gotta call an aniamte funciton that does a cute aniamtion of what ever color is in spot 1. thats it
        
       
        
        
        ////////// then we will have afunction that will assgin priority, maybe update meters can do that too?
    
        
        sort_meter(meters, meter_cold, meter_stamina, meter_health, meter_hunger); // then we sort the meters and the array will be ready for use
        
        create_meters(meters, view, windowsize_x, windowsize_y); // then everything is ready for drawing
        // meters also have the code for length, cool, but now since we arent spinning them or whatever, they dont need em, Ill wait but you can take them out and length can be assigned through priiototy
        

        
         ///////////////////////////////// Status Meters \\\\\\\\\\\\\\\\\\\\\\\\/
        
        //////////////////////////////// rush timer clock message \\\\\\\\\\\\\\\\\\\\\\\\/
            string mess = to_string(rush_elapsed.asSeconds()); //tag
            sf::Text text(mess, font, 50);
            text.setFillColor(sf::Color::Black);
            text.setPosition(view.getCenter().x - windowsize_x/2, view.getCenter().y  - windowsize_y/2);
        //////////////////////////////// rush timer clock message \\\\\\\\\\\\\\\\\\\\\\\\
            
        
        ////////////////// DRAWING PHASE \\///////////////////////// DRAWING PHASE \\\\\\\\\\\\\\\\\/
        
        window.clear(); ///////////////// Clear screen

        /////////////////// afix player and background
        player.setPosition(sf::Vector2f(view.getCenter().x, view.getCenter().y));
        claw.setPosition(sf::Vector2f(view.getCenter().x, view.getCenter().y));
        background.setPosition(sf::Vector2f(view.getCenter().x, view.getCenter().y));

        
        window.draw(background);  // we are just gonna cheese the drawing and fade the color of the rectange by whre we are

        
        /////////////////////////////////// drawing ghe grid lines
        for(int i = 0; i < game_width + 1; i++){
            window.draw(vert[i]);
        }
        for(int i = 0; i < game_height + 1; i++){
            window.draw(horz[i]);
        }
        //////////////////////////////// drawing ghe grid lines
        
        
        //////////////////////////  DRAW THE PLAYER
       
        window.draw(claw);
        window.draw(player);
        
        /////////////////////////////////////  Draw Array Bush Object /////////////////
        draw_array(window, view, a, num_bushes, windowsize_x, windowsize_y,  game_width, game_height);
        /////////////////////////////////////  Draw Array Bush Object /////////////////
        
        window.draw(text);   // Draw the string message text
        
        /////////////////////////////////  drawing Status Meters
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < (max_num +1)*2; j++){ // deal with the whole num max thing
                window.draw( *(meters[i].get_meter() + j));
            }
        }

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < (max_num +1)*2; j++){
                window.draw( *(meters[i].get_lines() + j));
            }
        }
        
       
        ////////////// the delte functions in the ~meter function are commented out caus ethye cause error at and of running
        // becuae of this I think they are automatically called at the end of the program
        // we just goota look up an exmaple of using a deconstructor with a new array
        /*
        for(int i = 0; i < 4; i ++){
          meters[i].~Meter();
        }
        */
        
        //view.setSize(game_width*windowsize_x, game_height*windowsize_y);  // mag lense
        window.setView(view); // Curate View
    
        window.display();  // Update the window
  
      
}
    delete[] a;
    delete[] vert;
    delete[] horz;
    
    return EXIT_SUCCESS;

}

