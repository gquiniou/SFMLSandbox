/*
 * GameObject.h
 *
 *  Created on: 8 janv. 2012
 *      Author: greg
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <SFML/Graphics.hpp>


class GameObject {

public:

	GameObject() : destroyrequest(false) {}

	GameObject(sf::Sprite _sprite) : destroyrequest(false), sprite(_sprite) {}

	virtual ~GameObject() {}

	virtual void update() = 0;

	sf::Sprite &getDrawable() {
		return sprite;
	}

	sf::Vector2f getCenter() {
		sf::FloatRect r = sprite.GetGlobalBounds();
		return sf::Vector2f(r.Left + r.Height /2, r.Top + r.Height / 2);
	}

	sf::FloatRect getRect() const {
		return sprite.GetGlobalBounds();
	}

	bool destroyRequest() {
		return destroyrequest;
	}

protected:
	bool destroyrequest;
	sf::Sprite sprite;
};


#endif /* GAMEOBJECT_H_ */
