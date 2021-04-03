#include <armadillo>

#include "food.h"

class AntColony {
	const double steering_probability = 0.1;
	const double steering_factor = 1;
	const double speed = 1.2;

	const double pheromone_freq = 0.2;
	const double pheromone_time_c = 30;
	const double pheromone_distance_c = 50;
	const double pheromone_strength = 10;

	public:
		int n_ants;

		arma::mat positions;
		arma::mat directions;
		arma::uvec follow_modes;

		arma::mat home_emitting_positions = arma::zeros(2, 0);
		arma::vec home_emission_times = arma::zeros(0);

		arma::mat food_emitting_positions = arma::zeros(2, 0);
		arma::vec food_emission_times = arma::zeros(0);

		std::function<double(const arma::vec &coor, const double time)>
		make_home_pheromones(
			double time
		);

		std::function<double(const arma::vec &coor, const double time)>
		make_food_pheromones(
			double time
		);

		AntColony(
			int n_ants,
			const arma::vec &origin
		);

		void
		move(const Food &food);

};