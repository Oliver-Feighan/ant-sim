#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "ant.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1800, 1800), "Ant Colony Simulation");

    std::vector<Ant> ants;

    for(int i = 0; i < 200; i++){
    	ants.push_back(Ant(window, 900, 900));
    }


    auto count = 0;

    std::pair<int, int> target;

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

    		target.first = pos.x;
    		target.second = pos.y;

    		sf::CircleShape shape(20.f);
    		shape.setPosition(pos.x, pos.y);

    		shape.setFillColor(sf::Color::White);

    		window.draw(shape);
    	}


    	count++;

    	if(count % 2000 == 0){
    		for(auto &ant : ants){
    			ant.new_direction();
    		}
    	}

    	for(auto &ant : ants){
    		ant.move(window);
		}	

    	window.display();


    }

    return 0;
}