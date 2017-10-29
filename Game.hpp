#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Game{
	sf::RenderWindow& window;
public:
	Game(sf::RenderWindow& window);
	~Game();
	void draw();
};