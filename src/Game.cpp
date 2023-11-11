
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window) : window(game_window)
{
  srand(time(NULL));
}

Game::~Game() {}

bool Game::init()
{
  // spawns ship
  ship.initialiseSprite(
    ship_texture, "Data/Images/Alien UFO pack/PNG/shipBeige_manned.png");
  ship.getSprite()->setScale(0.5, 0.5);
  ship.getSprite()->setPosition(
    window.getSize().x / 2 - ship.getSprite()->getGlobalBounds().width / 2,
    window.getSize().y / 1.2 - ship.getSprite()->getGlobalBounds().height / 2);

  // spawns 7 aliens
  for (int i = 0; i < 7; i++)
  {
    aliens[i].initialiseSprite(
      aliens_texture,
      "Data/Images/SpaceShooterRedux/PNG/Enemies/enemyBlack1.png");
    aliens[i].getSprite()->setScale(0.5, 0.5);
    if (i == 0)
    {
      aliens[0].getSprite()->setPosition(10, 10);
    }
    else
    {
      aliens[i].getSprite()->setPosition(
        aliens[i - 1].getSprite()->getPosition().x + 100, 10);
    }
  }

  // spawns shots
  for (int i = 0; i < 10; i++)
  {
    shot[i].initialiseSprite(
      shot_texture, "Data/Images/SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
    shot[i].getSprite()->setScale(0.5, 0.5);
    shot[i].visibility = false;
    shot[i].getSprite()->setPosition(
      ship.getSprite()->getPosition().x, ship.getSprite()->getPosition().y);
  }

  in_menu = true;

  // initialising background
  if (!background_texture.loadFromFile("Data/Images/SpaceShooterRedux/"
                                       "Backgrounds/blue.png"))
  {
    std::cout << "background did not load \n";
  }
  background.setTexture(background_texture);
  background.setScale(5, 5);

  // init menu text
  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "font did not load \n";
  }
  title_text.setString("SPACE INVADERS");
  title_text.setFont(font);
  title_text.setCharacterSize(70);
  title_text.setFillColor(sf::Color(255, 255, 255, 150));
  title_text.setPosition(
    window.getSize().x / 2 - title_text.getGlobalBounds().width / 2,
    window.getSize().y / 10 - title_text.getGlobalBounds().height / 2);

  // init menu text
  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "font did not load \n";
  }
  select_option.setString("Press enter to select an option");
  select_option.setFont(font);
  select_option.setCharacterSize(15);
  select_option.setFillColor(sf::Color(255, 255, 255, 120));
  select_option.setPosition(
    window.getSize().x / 2 - select_option.getGlobalBounds().width / 2,
    window.getSize().y / 5 - select_option.getGlobalBounds().height / 2);

  // init menu text
  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "font did not load \n";
  }
  play_option.setString("Play");
  play_option.setFont(font);
  play_option.setCharacterSize(20);
  play_option.setFillColor(sf::Color(255, 255, 255, 255));
  play_option.setPosition(
    window.getSize().x / 4 - play_option.getGlobalBounds().width / 2,
    window.getSize().y / 2 - play_option.getGlobalBounds().height / 2);

  // init menu text
  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "font did not load \n";
  }
  quit_option.setString("Quit");
  quit_option.setFont(font);
  quit_option.setCharacterSize(20);
  quit_option.setFillColor(sf::Color(255, 255, 255, 255));
  quit_option.setPosition(
    (window.getSize().x / 4 - quit_option.getGlobalBounds().width / 2) * 3,
    window.getSize().y / 2 - quit_option.getGlobalBounds().height / 2);

  return true;
}

void Game::update(float dt)
{
  // moves ship + stops ship from going past screen bounds
  if (
    ship.getSprite()->getPosition().x >=
    (window.getSize().x - ship.getSprite()->getGlobalBounds().width))
  {
    velocity = 0;
    ship.getSprite()->move(-1, 0);
  }
  if ((ship.getSprite()->getPosition().x <= 0))
  {
    velocity = 0;
    ship.getSprite()->move(1, 0);
  }

  ship.getSprite()->move(
    ship.direction.x * velocity * dt, ship.direction.y * velocity * dt);

  // stops aliens from going past screen bounds
  if (
    (aliens[6].getSprite()->getPosition().x +
       aliens[6].getSprite()->getGlobalBounds().width >
     window.getSize().x) or
    (aliens[0].getSprite()->getPosition().x < 0))
  {
    alienv = -alienv;
  }

  for (int i = 0; i < 7; i++)
  {
    aliens[i].getSprite()->move(alienv, 0);
    if (
      (aliens[6].getSprite()->getPosition().x +
         aliens[6].getSprite()->getGlobalBounds().width >
       window.getSize().x) or
      (aliens[0].getSprite()->getPosition().x < 0))
    {
      aliens[i].getSprite()->setPosition(
        aliens[i].getSprite()->getPosition().x,
        aliens[i].getSprite()->getPosition().y + 20);
    }
  }

  // shot visibility + if off screen + moves
  for (int i = 0; i < 10; i++)
  {
    if (shot[i].visibility)
    {
      shot[i].getSprite()->move(0, -5);

      if (
        shot[i].getSprite()->getPosition().y +
          shot[i].getSprite()->getGlobalBounds().height <
        0)
      {
        shot[i].visibility = false;
      }
    }
  }
}

void Game::render()
{
  // rendering game sprites / textures / text
  if (in_menu)
  {
    window.draw(background);
    window.draw(title_text);
    window.draw(select_option);
    window.draw(play_option);
    window.draw(quit_option);
  }
  else
  {
    window.draw(background);
    window.draw(*ship.getSprite());
    for (int i = 0; i < 7; i++)
    {
      window.draw(*aliens[i].getSprite());
    }
    for (int i = 0; i < 10; i++)
    {
      if (shot[i].visibility)
      {
        window.draw(*shot[i].getSprite());
      }
    }
  }
}

void Game::mouseClicked(sf::Event event)
{
  // get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
}

void Game::keyPressed(sf::Event event)
{
  // registering key presses
  if (
    (event.key.code == sf::Keyboard::Left) ||
    (event.key.code == sf::Keyboard::Right))
  {
    play_selected = !play_selected;
    if (play_selected)
    {
      play_option.setString("Play <");
      quit_option.setString("Quit");
    }
    else
    {
      play_option.setString("Play");
      quit_option.setString("Quit <");
    }
  }

  if (event.key.code == sf::Keyboard::Enter)
  {
    if (play_selected)
    {
      in_menu = false;
    }
    else
    {
      window.close();
    }
  }

  if (event.key.code == sf::Keyboard::Escape)
  {
    window.close();
  }

  if (event.key.code == sf::Keyboard::Right)
  {
    velocity = 500;
  }
  if (event.key.code == sf::Keyboard::Left)
  {
    velocity = -500;
  }

  if (event.key.code == sf::Keyboard::Space)
  {
    shot[cshot].visibility = true;
    shot[cshot].getSprite()->setPosition(
      ship.getSprite()->getPosition().x, ship.getSprite()->getPosition().y);
    if (cshot == 9)
    {
      cshot = 0;
    }
    else
    {
      cshot++;
    }
  }
}

void Game::keyReleased(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Right)
  {
    velocity = 0;
  }
  if (event.key.code == sf::Keyboard::Left)
  {
    velocity = 0;
  }
}

bool detectCollision(sf::Sprite aliens, sf::Sprite shot)
{
  if (
    shot.getPosition().x > aliens.getPosition().x &&
    shot.getPosition().x <
      aliens.getPosition().x + aliens.getGlobalBounds().width &&
    shot.getPosition().x >
      aliens.getPosition().x - aliens.getGlobalBounds().height)
  {

  }
}