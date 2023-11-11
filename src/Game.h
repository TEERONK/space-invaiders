
#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "GameObject.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);
  bool detectionCollision(sf:: Sprite ship);
  bool detectCollision(sf::Sprite aliens, sf::Sprite shot);

 private:
  sf::RenderWindow& window;
  GameObject ship;
  sf::Texture ship_texture;
  sf::Font font;
  sf::Sprite background;
  sf::Texture background_texture;
  GameObject shot [10];
  sf::Texture shot_texture;

  GameObject aliens[7];
  sf::Texture aliens_texture;
  int cshot = 0;

  bool in_menu;
  sf::Text title_text;
  sf::Text play_option;
  sf::Text quit_option;
  sf::Text select_option;
  bool play_selected = true;

  int alienv = 1;

  float velocity;
};

#endif // SPACEINVADERS_GAME_H
