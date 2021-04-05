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

	const arma::mat unsigned_directions = arma::randu(2, n_cols);
	const arma::mat signed_directions = 2 * unsigned_directions -1;
	return arma::normalise(signed_directions);
}

arma::vec
get_distances(const arma::mat &relative_displacements){

	arma::vec result(relative_displacements.n_cols);

	for(int i = 0; i < result.n_elem; i++){
		result(i) = arma::norm(relative_displacements.col(i));
	}

	return result;

}

void
AntColony::update_pheromones(
	const double time
	){

	//decrease the intensity of existing points
	this->emission_strengths -= this->time_deactivation * (time - this->emission_times);

	//get the new start times and positions of pheromone centers
	const arma::mat new_emissions_positions = this->positions;

	const arma::vec new_emission_times = 
			[time, n_centres = new_emissions_positions.n_cols](){
		arma::vec result = arma::vec(n_centres);
		result.fill(time);

		return result;
	}();

	const arma::vec new_emission_strengths = this->energies;

	//append the new positions to the emission lists
	this->emission_positions = arma::join_horiz(this->emission_positions, new_emissions_positions);
	this->emission_times = arma::join_vert(this->emission_times, new_emission_times);
	this->emission_strengths = arma::join_vert(this->emission_strengths, new_emission_strengths);
	this->emission_types = arma::join_vert(this->emission_types, this->follow_modes);

	//remove the old points that have gone past the time limit or have strengths under threshold
	const arma::uvec active_points = arma::find(this->emission_strengths > 1e-6);

	this->emission_positions = this->emission_positions.cols(active_points);
	this->emission_times = this->emission_times(active_points);
	this->emission_strengths = this->emission_strengths(active_points);
	this->emission_types = this->emission_types(active_points);

}

AntColony::AntColony(
	const int n_ants,
	const arma::vec &origin
	){

	this->n_ants = n_ants;
	this->follow_modes = arma::uvec(n_ants, arma::fill::zeros);
	this->energies = arma::zeros(n_ants);
	this->energies.fill(this->max_energy);

	const auto points_on_unit_circle = make_random_directions(this->n_ants);
	this->positions = 25 * points_on_unit_circle;
	this->positions.each_col() += origin;

	this->directions = points_on_unit_circle;

};

arma::mat
distance_matrix(
	const arma::mat &coords1,
	const arma::mat &coords2
	){

	const auto dim2 = coords2.n_cols;

	const arma::mat x1_image = arma::repmat(coords1.row(0).t(), 1, dim2);
	const arma::mat y1_image = arma::repmat(coords1.row(1).t(), 1, dim2);

	const arma::mat x1_x2 = x1_image.each_row() - coords2.row(0);
	const arma::mat y1_y2 = y1_image.each_row() - coords2.row(1);
	
	return arma::sqrt(arma::square(x1_x2) + arma::square(y1_y2)); 
}

void
AntColony::smell_pheromones(const Food &food, const Home &home)
	{

	const auto full_distance_mat = distance_matrix(this->positions, this->emission_positions);

	for(int i = 0; i < full_distance_mat.n_rows; i++){
		const arma::vec pos_i = this->positions.col(i);
		const arma::uword mode = this->follow_modes(i);

		if(mode == 0 && arma::norm(pos_i - food.pos) < food.size + smelling_max_distance){
			this->directions.col(i) = food.pos - pos_i; 
			continue;
		}

		if(mode == 1 && arma::norm(pos_i - home.pos) < home.size + smelling_max_distance){
			this->directions.col(i) = home.pos - pos_i; 
			continue;
		}

		double max_strength = 0;
		
		const arma::vec dir = this->directions.col(i);

		for(int j = 0; j < full_distance_mat.n_cols; j++){
			if(this->emission_types(j) == mode){
				continue;
			}
			
			if(full_distance_mat(i, j) > this->smelling_max_distance){
				continue;
			}
			
			if(this->emission_strengths(j) < max_strength){
				continue;
			}
			
			const arma::vec pos_j = this->emission_positions.col(j);

			if(std::acos(arma::norm_dot(dir, pos_j)) < 1.0){
				continue;
			}
			
			max_strength = this->emission_strengths(j);	

		}

		if(max_strength == 0){
			continue;
		}

		const arma::uvec index = arma::find(this->emission_strengths == max_strength);
		this->directions.col(i) = this->emission_positions.col(index(0)) - pos_i;
	}
}

void
AntColony::move(
	const Food &food,
	const Home &home,
 	double d_time
	){

	//lower energy levels
	this->energies *= 0.99;
	//this->energies = arma::clamp(this->energies, this->min_energy, this->max_energy);

	//follow smells and steering
	//steering
	const arma::uvec steering_mask = 
		arma::find(arma::randu(this->n_ants) < this->steering_probability);

	const arma::mat steering_directions =
		make_random_directions(steering_mask.n_rows);

	this->directions.cols(steering_mask) += this->steering_factor * steering_directions;

	//update following modes
	const arma::vec distance_to_food = get_distances(this->positions.each_col() - food.pos);
	const arma::uvec at_food_pile = arma::find(distance_to_food < food.size);

	const arma::vec distance_to_home = get_distances(this->positions.each_col() - home.pos);
	const arma::uvec at_home_pile = arma::find(distance_to_home < home.size);

	this->returned += arma::intersect(at_home_pile, arma::find(this->follow_modes == 1)).eval().n_elem;

	this->follow_modes(at_food_pile).fill(1);
	this->follow_modes(at_home_pile).fill(0);

	const arma::uvec getting_food = arma::find(this->follow_modes == 0);
	const arma::uvec going_home = arma::find(this->follow_modes == 1);

	//if at the home or food pile, recharge to max_energy and turn around
	const arma::uvec recharged = arma::join_vert(at_food_pile, at_home_pile);
	this->energies(recharged).fill(this->max_energy);

	this->smell_pheromones(food, home);
	
	//normalize directions
	this->directions = arma::normalise(this->directions);

	//update positions
	const arma::mat new_positions = this->positions + this->speed * this->directions; // * d_time;

	//periodic boundries
	this->positions = mod<arma::mat>(new_positions + 1800, 1800);









}