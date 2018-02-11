#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics/CircleShape.hpp>
using namespace std;

int width = 1000;
int height = 1000;

int spikes = 4;
float ratio = 0.25;
int up_down = 1;
int c_x = width / 2; int  c_y = height / 2;
int S = (min(width,height))/2;

const double pi = 3.1415926535897;


int main()
{
	sf::RenderWindow window(sf::VideoMode(width, height), "Hypocycloid");
	sf::CircleShape c;
	sf::RectangleShape rect(sf::Vector2f(1,1));
	sf::Clock clock;
	rect.setFillColor(sf::Color::Black);
	rect.setPosition(sf::Vector2f(width/2, height/2));
	c.setRadius(S);
	c.setOrigin(sf::Vector2f(width / 2, height / 2));

	while (window.isOpen())
	{
		float bigradius = S / (ratio + 1.0);
		float smallradius = S - bigradius;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		window.clear(sf::Color::White);
		
		for (double i = 0.0; i < 2.0 * pi; i += 0.0001) {
			float big_y = sin(i) * bigradius;
			float big_x = cos(i) * bigradius;
				
			float other_y = sin(-(spikes - 1.0) * i) * smallradius;
			float other_x = cos(-(spikes - 1.0) * i) * smallradius;
			
			//cout << other_x << " " << other_y << endl;
			rect.setPosition(c_x + big_x + other_x, c_y + big_y + other_y);
			window.draw(rect);
		}
		
		
		if (ratio > 4)
			up_down = 0;

		if (ratio < 1)
			up_down = 1;

		if (up_down == 0) {
			ratio -= 0.03;
			spikes -= 1;
		}

		if (up_down == 1) {
			ratio += 0.03;
			spikes += 1;
		}
		window.display();
		
	}
	return 0;
}