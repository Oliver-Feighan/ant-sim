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

	const arma::uvec pheromone_mask =
		arma::find(arma::randu(this->n_ants) < this->home_pheromone_freq);

	const arma::mat new_emissions_positions =
		this->positions.cols(pheromone_mask);

	const arma::vec new_emission_times = [pheromone_mask, time](){
		arma::vec result = arma::vec(pheromone_mask.n_elem); 
		result.fill(time);

		return result;
	}();

	this->emitting_positions = arma::join_horiz(this->emitting_positions, new_emissions_positions);
	this->emission_times = arma::join_vert(this->emission_times, new_emission_times);

	return [emitting_positions = this->emitting_positions, 
			emission_times = this->emission_times,
			time_c = this->home_pheromone_time_c,
			distance_c = this->home_pheromone_distance_c](
			const arma::vec &coord, const double time
			){

		const arma::vec time_function = arma::exp(- time_c * (time - emission_times));

		const arma::vec distances = get_distances(coord - emitting_positions.each_col());

		const arma::vec distance_function = arma::exp(- distance_c * arma::square(0.001 * distances));

		return std::min(arma::sum(100 * time_function % distance_function), 255.);

	};


}

AntColony::AntColony(
	const int n_ants,
	const arma::vec &origin
	){

	this->n_ants = n_ants;
	this->positions = arma::mat(2, n_ants, arma::fill::zeros).each_col() + origin;
	this->directions = make_random_directions(this->n_ants);

};

void
AntColony::move(){

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