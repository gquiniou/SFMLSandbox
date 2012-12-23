/*
 * File:   Animated.cpp
 * Author: greg
 *
 * Created on 4 mars 2012, 18:53
 */

#include "Animated.h"
#include <iostream>

template <typename T>
std::ostream& operator<<(std::ostream &os, sf::Rect<T> &r) {
	os << "left,top:" << r.Left << ", " << r.Top << " width,height:" << r.Width << ", " << r.Height << std::endl;
	return os;
}

Animated::~Animated() {
}

void Animated::update() {
    frame *current = (*currentframe).get();
    //std::cout <<clock.GetElapsedTime() <<std::endl;
    if (clock.getElapsedTime() >= current->duration) {
        currentframe++;
        if (currentframe == std::end(*currentanim))
            currentframe = std::begin(*currentanim);
        current = (*currentframe).get();
        clock.restart();
        //std::cout << current->rect << std::endl;
        sprite.setTextureRect(current->rect);
        //std::cout << "The distance is: " << distance(first,last) << endl;

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
        currentframe = it->second.get()->begin();
        currentanim = it->second.get();
        clock.restart();
    }
    //sprite.SetPosition(100,100);
}


void Animated::addFrame(std::string animName, sf::IntRect rect, int duration) {
    framevector *fv = nullptr;
    animationmap::iterator it = anims.find(animName);

    if (it == anims.end()) {
        //std::unique_ptr<framevector> fvptr(new framevector());
        //anims.insert(std::pair<std::string,std::unique_ptr<framevector>>(animName, std::move(fvptr)));
        it = anims.insert(anims.begin(), std::pair<std::string,std::unique_ptr<framevector>>(animName, std::unique_ptr<framevector>(new framevector())));
        //fv = fvptr.get();
        fv = it->second.get();
    } else
        fv = it->second.get();
    std::unique_ptr<frame> myframe(new frame(rect, duration));
    //myframe.get()->rect = rect;
    //myframe.get()->duration = duration;
    //fv->push_back(std::move(myframe));
    fv->push_back(std::unique_ptr<frame>(std::move(myframe)));
}
