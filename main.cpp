/*
 * File:   main.cpp
 * Author: greg
 *
 * Created on 4 mars 2012, 09:14
 */

#include "Animated.h"
#include "ResourceManager.h"
#include <cstdlib>
#include <vector>
#include <SFML/Graphics.hpp>
/*
 *
 */
int main() {

    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML Breakout");
	App.EnableVerticalSync(true);

    sf::Sprite s;
    s.SetTexture(*game::ResourceManager::getTexture("breakout_sprites.png"));
    Animated a(s);
    a.getDrawable().SetPosition(100,100);
    Animated a2(s);
    a2.getDrawable().SetPosition(100,130);

    std::vector<Animated *> sprites;
    for (int i = 0; i < 20; i++) {
        Animated * an = new Animated(s);
        for (int j = 1; j < 16 ; j++) {
            sf::IntRect rec(j*24, 376, 24, 24);
            an->addFrame("myanim", rec, 60);
        }
        an->playanimation("myanim",i);
        an->getDrawable().SetPosition(200, i*24);
        sprites.push_back(an);
    }

    for (int i = 0; i < 16; i++) {
        sf::IntRect rec(i*24, 376, 24, 24);
        a.addFrame("myanim", rec, 120);
        a2.addFrame("myanim", rec, 30);
    }
    a.playanimation("myanim");
    a2.playanimation("myanim");

	while (App.IsOpened()) {

		sf::Event Event;
		while (App.PollEvent(Event)) {
			if ((Event.Type == sf::Event::Closed) || ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Escape))) {
				return 0;
			}
        }

        a.update();
        a2.update();

        for (auto it = sprites.begin(); it != sprites.end(); it++ ) {
            (*it)->update();
        }

        App.Clear();
        App.Draw(a.getDrawable());
        App.Draw(a2.getDrawable());
        for (auto it = sprites.begin(); it != sprites.end(); it++ ) {
            App.Draw((*it)->getDrawable());
        }

        App.Display();
    }

    for (auto it = sprites.begin(); it != sprites.end(); it++ ) {
        delete *it;
    }

    App.Close();
    return 0;
}

