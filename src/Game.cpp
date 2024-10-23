
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{
	delete[] animals;
	delete[] passports;
	delete character;
	delete passport; 
}

bool Game::init()
{
	//background
	if (!background_texture.loadFromFile("../Data/WhackaMole Worksheet/background.png"))
	{
		std::cout << "background texture did not load \n";
	}
	background.setTexture(background_texture);

	//animals
	character = new sf::Sprite;

	if (!animals[0].loadFromFile("../Data/Critter Crossing Customs/moose.png"))
	{
		std::cout << "Error loading character texture \n";
		return false;
	}

	if (!animals[1].loadFromFile("../Data/Critter Crossing Customs/penguin.png"))
	{
		std::cout << "Error loading character texture \n";
		return false;
	}

	if (!animals[2].loadFromFile("../Data/Critter Crossing Customs/elephant.png"))
	{
		std::cout << "Error loading character texture \n";
		return false;
	}

	int animal_index = rand() % 3;
	character->setTexture(animals[animal_index], true);
	character->setScale(1.8, 1.8);
	character->setPosition(window.getSize().x / 12, window.getSize().y / 12);

	//passport
	passport = new sf::Sprite;

	if (!passports[0].loadFromFile("../Data/Critter Crossing Customs/moose passport.png"))
	{
		std::cout << "Error loading character texture \n";
		return false;
	}

	if (!passports[1].loadFromFile("../Data/Critter Crossing Customs/penguin passport.png"))
	{
		std::cout << "Error loading character texture \n";
		return false;
	}

	if (!passports[2].loadFromFile("../Data/Critter Crossing Customs/elephant passport.png"))
	{
		std::cout << "Error loading character texture \n";
		return false;
	}

	int passport_index = rand() % 3;

	passport->setTexture(passports[passport_index]);
	passport->setScale(0.6, 0.6);
	passport->setPosition(window.getSize().x / 2, window.getSize().y / 3);

  return true;
}

void Game::update(float dt)
{
	dragSprite();
}

void Game::render()
{
	window.draw(background);
	window.draw(*character);
	window.draw(*passport);
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);

}

void Game::mouseButtonPressed(sf::Event event)
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i click = sf::Mouse::getPosition(window);
		sf::Vector2f clickf = static_cast<sf::Vector2f>(click);

		if (passport->getGlobalBounds().contains(clickf))
		{
			dragged = passport; 
		}
	}
}

void Game::mouseButtonReleased(sf::Event event)
{
	dragged = nullptr;

}

void Game::keyPressed(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Escape)
	{
		window.close();
	}
}

void Game::newAnimal()
{
	passport_accepted = false;
	passport_rejected = false;

	int animal_index = rand() % 3;
	int passport_index = rand() % 3;

	if (animal_index == passport_index)
	{
		should_accept = true;
	}
	else
	{
		should_accept = false;
	}

}

void Game::dragSprite()
{
	sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
	sf::Vector2f mouse_positionf = static_cast<sf::Vector2f>(mouse_position);

	if (dragged != nullptr)
	{
		
		dragged->move(mouse_positionf.x - cursor.x, mouse_positionf.y - cursor.y);

		//sf::Vector2f drag_position = mouse_positionf - drag_offset;
		//sprite->setPosition(drag_position.x, drag_position.y);
	}
	cursor = mouse_positionf;

}
