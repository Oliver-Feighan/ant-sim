#include "ant.h"
#include <iostream>
#include <stdlib.h>


Ant::Ant(sf::RenderWindow & window, double x, double y){
	this->shape = sf::CircleShape(10.f);
	this->shape.setFillColor(sf::Color::Green);

	this->shape.setPosition(x, y);

	window.draw(this->shape);
}

double
norm(
	const double x,
	const double y){

	return sqrt(x*x + y*y);
}

double 
norm(
	const std::pair<int, int> &v){

	return norm(v.first, v.second);
}

std::pair<double, double>
target_unit_vector(
	const std::pair<int, int> &position,
	const std::pair<int, int> &target){

	const std::pair<double, double> v = {
		target.first - position.first,
		target.second - position.second
	};

	const auto n = norm(v.first, v.second);

	if(norm(v) < 1e-6){
		return {0., 0.};
	}

	return {
		v.first / n,
		v.second / n,
	};

}

void
Ant::follow_target(
	const std::pair<int, int> &target,
	sf::RenderWindow & window){

	const auto pos = this->shape.getPosition();

	const auto v = target_unit_vector(std::pair<int, int>{pos.x, pos.y}, target);

	this->shape.move(this->speed * v.first, this->speed * v.second);

	window.draw(this->shape);

}

void
Ant::move(sf::RenderWindow &window){

	this->shape.move(this->speed * this->direction.first, this->speed * this->direction.second);

	const auto pos = this->shape.getPosition();

	const auto in_bounds = [box_size=1800](const int c){
		return (c > 0 && c < box_size);
	};

	if(!in_bounds(pos.x)){
		if(pos.x < 0){

		}
	}

	if(!in_bounds(pos.y)){
		if(pos.y < 0){
			
		}
	}

	window.draw(this->shape);

}

std::pair<double, double>
random_target(){
	return {
		2. * rand() / (RAND_MAX + 1.) - 1.,
		2. * rand() / (RAND_MAX + 1.) - 1.
	};
}

void
Ant::new_direction(){
	constexpr double force = 1;

	const auto new_direction = random_target();

	this->direction.first += force * new_direction.first;	
	this->direction.second += force * new_direction.second;	

}








