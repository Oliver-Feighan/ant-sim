#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>

#include "ant.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1800, 1800), "Ant Colony Simulation");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    auto ant_colony = AntColony(200, arma::vec{900, 900});

    auto food = Food{arma::vec{1350, 900}, 25, 50};

    sf::Clock clock;
    double time = clock.getElapsedTime().asSeconds();

    auto home_func = ant_colony.make_home_pheromones(time);
    auto food_func = ant_colony.make_food_pheromones(time);
    auto last_pherone_check = time;

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

    	ant_colony.move(food);

    	window.clear();

	    if(time - last_pherone_check > 3){
	    	home_func = ant_colony.make_home_pheromones(time);
	    	home_func = ant_colony.make_food_pheromones(time);
	    	last_pherone_check = time;
	    }

	    for(int i = 0; i < ant_colony.home_emitting_positions.n_cols; i++){
	    	const arma::vec pos = ant_colony.home_emitting_positions.col(i);
    		sf::CircleShape shape(30);

    		shape.setPosition(pos(0)-30, pos(1)-30);
    		shape.setFillColor(sf::Color(0, 0, 255, 100));

    		window.draw(shape);

	    }

	    for(int i = 0; i < ant_colony.food_emitting_positions.n_cols; i++){
	    	const arma::vec pos = ant_colony.food_emitting_positions.col(i);
    		sf::CircleShape shape(30);

    		shape.setPosition(pos(0)-30, pos(1)-30);
    		shape.setFillColor(sf::Color(255, 0, 0, 100));

    		window.draw(shape);

	    }

	    sf::CircleShape food_pile(food.size);
	    food_pile.setPosition(food.pos(0)-food.size, food.pos(1)-food.size);
		food_pile.setFillColor(sf::Color(255, 0, 0, 100));
		window.draw(food_pile);

	    sf::CircleShape food_smell(food.pheromone_size);
	    food_smell.setPosition(food.pos(0)-food.pheromone_size, food.pos(1)-food.pheromone_size);
		food_smell.setFillColor(sf::Color(255, 0, 0, 100));
		window.draw(food_smell);


    	for(int i = 0; i < ant_colony.positions.n_cols; i++){
    		const arma::vec pos = ant_colony.positions.col(i);
    		sf::CircleShape shape(1);

    		shape.setPosition(pos(0), pos(1));
    		shape.setFillColor(sf::Color::Green);

    		window.draw(shape);


    	}

    	window.display();


    }

    return 0;
}