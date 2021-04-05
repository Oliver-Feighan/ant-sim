#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>

#include "ant.h"

int main()
{

	sf::Texture arrow_texture;
	if (!arrow_texture.loadFromFile("../images/arrow_height_20.png")){
    	std::cout << "Error in loading arrow png file";
    	return 1;
	}

	sf::Font text_font;
	if (!text_font.loadFromFile("../fonts/Courier_New_Bold.ttf")){
    	std::cout << "Error in loading font tff file";
    	return 1;
	}

    sf::RenderWindow window(sf::VideoMode(1800, 1800), "Ant Colony Simulation");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    auto ant_colony = AntColony(150, arma::vec{900, 900});

    auto food = Food{arma::vec{1350, 900}, 20};
    auto home = Home{arma::vec{900, 900}, 20};

    sf::Clock clock;
    double time = clock.getElapsedTime().asSeconds();

    ant_colony.update_pheromones(time);
    auto last_pherone_check = time;
    auto last_movement = time;

    //while(window.isOpen() && time < 0.05){
	while(window.isOpen()){
    	window.clear();
    	sf::Event event;
    	
    	while(window.pollEvent(event)){
    		if(event.type == sf::Event::Closed){
    			window.close();
    		}
    	}


    	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
    		const auto pos = sf::Mouse::getPosition(window);

    		sf::CircleShape shape(20);
    		shape.setPosition(pos.x, pos.y);

    		shape.setFillColor(sf::Color::White);

    		window.draw(shape);
    	}

    	time = clock.getElapsedTime().asSeconds();

    	ant_colony.move(food, home, time - last_movement);
    	last_movement = time;

    	window.clear();

	    if(time - last_pherone_check > 0.5){
	    	ant_colony.update_pheromones(time);
	    	last_pherone_check = time;
	    }

	    for(int i = 0; i < ant_colony.emission_positions.n_cols; i++){
	    	const arma::vec pos = ant_colony.emission_positions.col(i);
	    	const double strength = ant_colony.emission_strengths(i);
    		
    		sf::CircleShape shape(2);

    		shape.setPosition(pos(0)-5, pos(1)-5);

    		if(ant_colony.emission_types(i) == 0){
	    		shape.setFillColor(sf::Color(0, 0, 255, 100));
    		} else {
    			shape.setFillColor(sf::Color(255, 0, 0, 100));
    		}

    		window.draw(shape);

	    }

	    sf::CircleShape food_pile(food.size);
	    food_pile.setPosition(food.pos(0)-food.size, food.pos(1)-food.size);
		food_pile.setFillColor(sf::Color(255, 0, 0, 100));
		window.draw(food_pile);

		sf::CircleShape home_pile(home.size);
	    home_pile.setPosition(home.pos(0)-home.size, home.pos(1)-home.size);
		home_pile.setFillColor(sf::Color(0, 0, 255, 100));
		window.draw(home_pile);



    	for(int i = 0; i < ant_colony.positions.n_cols; i++){
    		const auto pos = ant_colony.positions.col(i);
    		const auto mode = ant_colony.follow_modes(i);

			sf::CircleShape shape(1);

			if(mode == 0){
    			shape.setPosition(pos(0), pos(1));
    			shape.setFillColor(sf::Color::Green);

    		} else {
    			shape.setPosition(pos(0), pos(1));
    			shape.setFillColor(sf::Color::Red);

    		}
    		
    		window.draw(shape);

    	}

    	sf::Text text;
		text.setFont(text_font);
		text.setString("Food Gathered : " + std::to_string(ant_colony.returned));
		text.setPosition(50, 1700);
		text.setCharacterSize(48);
		text.setFillColor(sf::Color::Green);
		window.draw(text);

    	window.display();


    }

    return 0;
}