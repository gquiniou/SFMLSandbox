/*
 * ResourceManager.h
 *
 *  Created on: 23 janv. 2012
 *      Author: greg
 */

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include <memory>

namespace game {

  typedef std::map<std::string, std::unique_ptr<sf::Texture>> TextureMap;
  
  class ResourceManager {
  public:
    //ResourceManager();

    //virtual ~ResourceManager();
    
    static sf::Texture *getTexture(const std::string filename) {
      static TextureMap textures;

      TextureMap::iterator it = textures.find(filename);
      if (it == textures.end()) {
	std::unique_ptr<sf::Texture> temp(new sf::Texture); 
	if (temp->loadFromFile(filename)) {
	  auto x = textures.insert(it, std::pair<std::string, std::unique_ptr<sf::Texture>>(filename, std::move(temp))); 
	  return &(*(*x).second); 
	} else {
	  std::cout << "could not load texture" << std::endl;
	}
      } else {
	return it->second.get();
      }
      return nullptr;
    }

  };

} /* namespace game */
#endif /* RESOURCEMANAGER_H_ */
