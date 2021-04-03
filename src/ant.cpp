#include "ant.h"
#include <algorithm>
#include <iostream>
#include <stdlib.h>

template<typename T>
T mod(T a, int n)
{
    return a - arma::floor(a/n)*n;
}  

arma::mat
make_random_directions(const int n_cols){

	const arma::mat unsinged_directions = arma::randu(2, n_cols);
	const arma::mat singed_directions = 2 * unsinged_directions -1;
	return arma::normalise(singed_directions);
}

arma::vec
get_distances(const arma::mat &relative_displacements){

	arma::vec result(relative_displacements.n_cols);

	for(int i = 0; i < result.n_elem; i++){
		result(i) = arma::norm(relative_displacements.col(i));
	}

	return result;

}

std::function<double(const arma::vec &coord, const double time)>
AntColony::make_home_pheromones(
	const double time
	){

	//remove the old points that have gone past the time limit
	const arma::uvec active_points = 
		arma::find((time - this->home_emission_times) < this->pheromone_time_c);

	this->home_emitting_positions = this->home_emitting_positions.cols(active_points);
	this->home_emission_times = this->home_emission_times(active_points);


	//get the new start times and positions of pheromone centers
	const arma::uvec getting_food = arma::find(this->follow_modes == 0);
	const arma::mat new_emissions_positions = this->positions.cols(getting_food);

	const arma::vec new_emission_times = 
			[time, 
			n_centres = new_emissions_positions.n_cols](){
		arma::vec result = arma::vec(n_centres);
		result.fill(time);

		return result;
	}();

	//append the new positions to the emission lists
	this->home_emitting_positions = arma::join_horiz(this->home_emitting_positions, new_emissions_positions);
	this->home_emission_times = arma::join_vert(this->home_emission_times, new_emission_times);

	return [emitting_positions = this->home_emitting_positions, 
			emission_times = this->home_emission_times,
			time_c = this->pheromone_time_c,
			distance_c = this->pheromone_distance_c,
			strength = this->pheromone_strength](
			const arma::vec &coord, const double time
			){

		arma::vec time_function = time_c - (time - emission_times);
		time_function(arma::find(time_function < 0)).fill(0);

		const arma::vec distances = get_distances(coord - emitting_positions.each_col());

		arma::vec distance_function = distance_c - distances;
		distance_function(arma::find(distance_function < 0)).fill(0);

		return std::min(arma::sum(strength * time_function % distance_function), 255.);

	};


}

std::function<double(const arma::vec &coord, const double time)>
AntColony::make_food_pheromones(
	const double time
	){

	//remove the old points that have gone past the time limit
	const arma::uvec active_points = 
		arma::find((time - this->food_emission_times) < this->pheromone_time_c);

	this->food_emitting_positions = this->food_emitting_positions.cols(active_points);
	this->food_emission_times = this->home_emission_times(active_points);


	//get the new start times and positions of pheromone centers
	const arma::uvec getting_food = arma::find(this->follow_modes == 1);
	const arma::mat new_emissions_positions = this->positions.cols(getting_food);

	const arma::vec new_emission_times = 
			[time, 
			n_centres = new_emissions_positions.n_cols](){
		arma::vec result = arma::vec(n_centres);
		result.fill(time);

		return result;
	}();

	//append the new positions to the emission lists
	this->food_emitting_positions = arma::join_horiz(this->food_emitting_positions, new_emissions_positions);
	this->food_emission_times = arma::join_vert(this->food_emission_times, new_emission_times);

	return [emitting_positions = this->food_emitting_positions, 
			emission_times = this->food_emission_times,
			time_c = this->pheromone_time_c,
			distance_c = this->pheromone_distance_c,
			strength = this->pheromone_strength](
			const arma::vec &coord, const double time
			){

		arma::vec time_function = time_c - (time - emission_times);
		time_function(arma::find(time_function < 0)).fill(0);

		const arma::vec distances = get_distances(coord - emitting_positions.each_col());

		arma::vec distance_function = distance_c - distances;
		distance_function(arma::find(distance_function < 0)).fill(0);

		return std::min(arma::sum(strength * time_function % distance_function), 255.);

	};


}


AntColony::AntColony(
	const int n_ants,
	const arma::vec &origin
	){

	this->n_ants = n_ants;
	this->follow_modes = arma::uvec(n_ants, arma::fill::zeros);
	this->positions = arma::mat(2, n_ants, arma::fill::zeros).each_col() + origin;
	this->directions = make_random_directions(this->n_ants);

};

void
AntColony::move(const Food &food){

	//update following modes
	const arma::vec distance_to_food = get_distances(this->positions.each_col() - food.pos);
	const arma::uvec at_food_pile = arma::find(distance_to_food < food.size);

	this->follow_modes(at_food_pile).fill(1);

	const arma::uvec getting_food = arma::find(this->follow_modes == 0);
	const arma::uvec going_home = arma::find(this->follow_modes == 1);

	//if in the food or home smell circles (and correct mode), move towards target
	const arma::uvec at_food_smell = arma::find(distance_to_food < food.pheromone_size);

	const arma::uvec at_food_want_food = arma::intersect(at_food_smell, getting_food);

	this->directions.cols(at_food_want_food) = food.pos - this->positions.cols(at_food_want_food).eval().each_col();

	//otherwise follow smells and steering
	const arma::uvec steering_mask = 
		arma::find(arma::randu(this->n_ants) < this->steering_probability);

	const arma::mat steering_directions =
		make_random_directions(steering_mask.n_rows);

	this->directions.cols(steering_mask) += steering_directions;

	this->directions = arma::normalise(this->directions);

	const arma::mat new_positions =
		this->positions + this->speed * this->directions;

	this->positions = mod<arma::mat>(new_positions + 1800, 1800);
}