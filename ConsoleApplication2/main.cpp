#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/CircleShape.hpp>
using namespace std;

int width = 800;
int height = 1000;

int spikes = 4;
float ratio = 0.25;
int up_down = 1;
int c_x = width / 2; int  c_y = min(width / 2, height / 2);
int S = (min(width,height))/2;
float ratio_coeff = 0.05;
bool anim_stop = false;

const double pi = 3.1415926535897;


int main()
{
	sf::RenderWindow window(sf::VideoMode(width, height), "Hypocycloid");
	sf::RectangleShape rect(sf::Vector2f(1,1));
	sf::Text txt;
	sf::Font font;
	font.loadFromFile("RobotoSlab-Regular.ttf");
	txt.setFont(font);
	rect.setFillColor(sf::Color::Black);
	rect.setPosition(sf::Vector2f(S, S));


	txt.setString("Increase/decrease ratio coefficient with right/left arrow keys\nS to stop the animation. A to continue the animation ");
	
	txt.setPosition(20, 2 * S+20);
	txt.setCharacterSize(24);
	txt.setStyle(sf::Text::Regular);
	txt.setFillColor(sf::Color::Black);


	while (window.isOpen())
	{
		float bigradius = S / (ratio + 1.0);
		float smallradius = S - bigradius;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				
				//Stop the animation
				if (event.key.code == sf::Keyboard::S) {
					anim_stop = true;
				}

				//Control it manually
				if (anim_stop and event.key.code == sf::Keyboard::Right and ratio < 4) {
					ratio += 0.05;
					spikes++;
				}
				if (anim_stop and event.key.code == sf::Keyboard::Left and ratio > 0) {
					ratio -= 0.05;
					spikes--;
				}


				//Start the animation
				if (event.key.code == sf::Keyboard::A)
					anim_stop = false;

				//Ratio Increase
				if (event.key.code == sf::Keyboard::Right and ratio_coeff < 0.4 and ratio < 4) {
					ratio_coeff += 0.05;
					spikes++;
				}

				//Ratio Decrease 
				if (event.key.code == sf::Keyboard::Left and ratio_coeff > 0.01 and ratio > 1) {
					ratio_coeff -= 0.05;
					spikes--;
				}
			}
		}

		window.clear(sf::Color::White);


		for (double i = 0.0; i < 2.0 * pi; i += 0.0001) {

			//Function for the bigger radius
			float big_y = sin(i) * bigradius;
			float big_x = cos(i) * bigradius;

			//Function for the smaller radius
			float other_y = sin(-(spikes - 1.0) * i) * smallradius;
			float other_x = cos(-(spikes - 1.0) * i) * smallradius;

			rect.setPosition(c_x + big_x + other_x, c_y + big_y + other_y);
			window.draw(rect);
		}

		window.draw(txt);

		if (!anim_stop) {

			if (ratio > 4)
				up_down = 0;

			if (ratio < 1)
				up_down = 1;

			if (up_down == 0) {
				ratio -= ratio_coeff;
				spikes -= 1;
			}

			if (up_down == 1) {
				ratio += ratio_coeff;
				spikes += 1;
			}
		}
		window.display();
	}
	return 0;
}