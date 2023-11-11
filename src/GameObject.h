
#ifndef SPACEINVADERS_GAMEOBJECT_H
#define SPACEINVADERS_GAMEOBJECT_H
#include <SFML/Graphics.hpp>
#include "Vector2.h"

class GameObject
{
 public:
  GameObject();
  ~GameObject();

  bool initialiseSprite(sf::Texture &texture, std::string filename);
  sf::Sprite* getSprite();
  Vector2 direction;
  bool visibility = false;

 private:
  sf::Sprite* sprite = nullptr;
};

#endif // SPACEINVADERS_GAMEOBJECT_H
