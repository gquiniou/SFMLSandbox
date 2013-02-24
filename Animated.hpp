/*
 * File:   Animated.h
 * Author: greg
 *
 * Created on 4 mars 2012, 18:53
 */

#ifndef ANIMATED_H
#define	ANIMATED_H

#include "GameObject.h"
#include <SFML/System.hpp>
#include <vector>
#include <memory>
#include <map>

struct frame {
  sf::IntRect rect;
  sf::Time duration;
  frame(sf::IntRect r, unsigned int d) : rect(r), duration(sf::milliseconds(d)) {}
};
typedef std::vector<std::unique_ptr<frame>>  framevector;
typedef std::map<std::string,std::unique_ptr<framevector>> animationmap;

class Animated : public GameObject {
public:
  Animated(sf::Sprite _sprite) : GameObject(_sprite) {}
  virtual ~Animated();
  void addFrame(std::string, sf::IntRect, int);
  void playanimation(std::string);
  void playanimation(std::string, int);
  virtual void update();

private:
  int remainingtime;
  framevector::iterator currentframe;
  framevector *currentanim;
  animationmap anims;
  sf::Clock clock;
};

#endif	/* ANIMATED_H */

