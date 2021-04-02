#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>

#include "ant.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1800, 1800), "Ant Colony Simulation");

    auto ant_colony = AntColony(200, arma::vec{900, 900});

    sf::Clock clock;
    double time = clock.getElapsedTime().asSeconds();

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

    		sf::CircleShape shape(20.f);
    		shape.setPosition(pos.x, pos.y);

    		shape.setFillColor(sf::Color::White);

    		window.draw(shape);
    	}

    	time = clock.getElapsedTime().asSeconds();
    	ant_colony.move();

    	window.clear();

	    const auto home_func = ant_colony.make_home_pheromones(time);

    	for(double i = 0; i < 1800.; i += 50.){
    		for(double j = 0.; j < 1800.; j += 50.){

    			const auto strength = home_func(arma::vec{i, j}, time);

    			if(strength < 1){
    				continue;
    			}
    
    			sf::CircleShape square(10.f, 4);
    			square.setPosition(i, j);
    			square.rotate(45);
    			square.setFillColor(sf::Color(0, 0, strength));

    			window.draw(square);


    		}
    	}


    	for(int i = 0; i < ant_colony.positions.n_cols; i++){
    		const arma::vec pos = ant_colony.positions.col(i);
    		sf::CircleShape shape(1.f);

    		shape.setPosition(pos(0), pos(1));
    		shape.setFillColor(sf::Color::Green);

    		window.draw(shape);


    	}

    	window.display();


    }

    return 0;
}