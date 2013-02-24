/*
 * File:   Animated.cpp
 * Author: greg
 *
 * Created on 4 mars 2012, 18:53
 */

#include "Animated.hpp"
#include <iostream>

template <typename T>
std::ostream& operator<<(std::ostream &os, sf::Rect<T> &r) {
  os << "left,top:" << r.Left << ", " << r.Top << " width,height:" << r.Width << ", " << r.Height << std::endl;
  return os;
}

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args ){
  return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}


Animated::~Animated() {
}

void Animated::update() {
  frame *current = (*currentframe).get();
  if (clock.getElapsedTime() >= current->duration) {
    currentframe++;
    if (currentframe == std::end(*currentanim))
      currentframe = std::begin(*currentanim);
    current = (*currentframe).get();
    clock.restart();
    sprite.setTextureRect(current->rect);
  }
}

void Animated::playanimation(std::string animname, int startframe) {
  playanimation(animname);
  startframe %= currentanim->size();
  std::advance(currentframe, startframe);
}

void Animated::playanimation(std::string animname) {
  animationmap::iterator it = anims.find(animname);
  if (it == anims.end()) {
    throw "unknown animation.";
  } else {
    currentanim = it->second.get();
    currentframe = currentanim->begin();
    clock.restart();
  }
}

void Animated::addFrame(std::string animName, sf::IntRect rect, int duration) {
  framevector *fv = nullptr;
  animationmap::iterator it = anims.find(animName);
  
  if (it == anims.end()) {
    it = anims.insert(anims.begin(), std::pair<std::string,std::unique_ptr<framevector>>(animName, make_unique<framevector>()));
  } 
  fv = it->second.get();
  fv->push_back(make_unique<frame>(rect, duration));
}
