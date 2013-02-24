/*
 * File:   main.cpp
 * Author: greg
 *
 * Created on 4 mars 2012, 09:14
 */

#include "Animated.hpp"
#include "ResourceManager.h"
#include <cstdlib>
#include <vector>
#include <SFML/Graphics.hpp>
/*
 *
 */
int main() {

  sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML Breakout");
  App.setVerticalSyncEnabled(true);

  sf::Sprite s;
  s.setTexture(*game::ResourceManager::getTexture("breakout_sprites.png"));
  Animated a(s);
  a.getDrawable().setPosition(100,100);
  Animated a2(s);
  a2.getDrawable().setPosition(100,130);

  std::vector<Animated *> sprites;
  for (int i = 0; i < 20; i++) {
    Animated * an = new Animated(s);
    for (int j = 1; j < 16 ; j++) {
      sf::IntRect rec(j*24, 376, 24, 24);
      an->addFrame("myanim", rec, 60);
    }
    an->playanimation("myanim",i);
    an->getDrawable().setPosition(200, i*24);
    sprites.push_back(an);
  }

  for (int i = 0; i < 16; i++) {
    sf::IntRect rec(i*24, 376, 24, 24);
    a.addFrame("myanim", rec, 1);
    a2.addFrame("myanim", rec, 150);
  }
  a.playanimation("myanim");
  a2.playanimation("myanim");

  while (App.isOpen()) {

    sf::Event Event;
    while (App.pollEvent(Event)) {
      if ((Event.type == sf::Event::Closed) || ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))) {
	return 0;
      }
    }

    //Updating animation state
    a.update();
    a2.update();
    for (auto sprite : sprites) {
      sprite->update();
    }

    App.clear();
    //Drawing
    App.draw(a.getDrawable());
    App.draw(a2.getDrawable());
    for (auto sprite : sprites) {
      App.draw(sprite->getDrawable());
    }

    App.display();
  }

  for (auto sprite : sprites) {
    delete sprite;
  }

  App.close();
  return 0;
}

