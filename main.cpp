    /*
     * File:   main.cpp
     * Author: greg
     *
     * Created on 4 mars 2012, 09:14
     */

    #include "Animated.hpp"
    #include "ResourceManager.h"
#include <cmath>

    /*
     *
     */
    int main() {

      sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML Sandbox");
      App.setVerticalSyncEnabled(true);

      sf::Sprite s;
      s.setTexture(*game::ResourceManager::getTexture("breakout_sprites.png"));

      //Creating the sprites
      std::vector<Animated *> sprites;
      for (int i = 0; i < 160; i++) {
        Animated * an = new Animated(s);
        for (int j = 1; j < 16 ; j++) {
          sf::IntRect rec(j*24, 376, 24, 24);
          an->addFrame("myanim", rec, 60);
        }
        an->playanimation("myanim",i);
        sprites.push_back(an);
      }

      Animated a(s);
      a.getDrawable().setPosition(90,90);
      Animated a2(s);
      a2.getDrawable().setPosition(90,120);
      for (int i = 0; i < 16; i++) {
        sf::IntRect rec(i*24, 376, 24, 24);
        a.addFrame("myanim", rec, 1);
        a2.addFrame("myanim", rec, 150);
      }
      a.playanimation("myanim");
      a2.playanimation("myanim");

      double i = 0;

      while (App.isOpen()) {

        //processing events
        sf::Event Event;
        while (App.pollEvent(Event)) {
          if ((Event.type == sf::Event::Closed) || ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))) {
        return 0;
          }
        }
        //Updating animation  and sprite positions

        i+=0.2;
        double j=0;

        for (auto sprite : sprites) {
          j+=1;
          sprite->getDrawable().setPosition(385+ 380* sin(4*(i+j) * M_PI / 180), 285+280* cos(5*(i+j) * M_PI / 180));
          sprite->update();
        }
        a.update();
        a2.update();

        //Drawing
        App.clear();
        for (auto sprite : sprites) {
          App.draw(sprite->getDrawable());
        }
        App.draw(a.getDrawable());
        App.draw(a2.getDrawable());

        App.display();
      }

      for (auto sprite : sprites) {
        delete sprite;
      }
      App.close();
      return 0;
    }

