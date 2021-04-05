#include <armadillo>

#include "utils.h"

class AntColony {
	public:
		const double steering_probability = 0.1;
		const double steering_factor = 1.5;
		const double speed = 2.0;

		const double max_energy = 5000;
		const double min_energy = 30;

		const double time_deactivation = 1;

		const double smelling_max_distance = 80;

		int n_ants;

		arma::mat positions;
		arma::mat directions;
		arma::uvec follow_modes;

		arma::vec energies;

		arma::mat emission_positions = arma::zeros(2, 0);
		arma::vec emission_times = arma::zeros(0);
		arma::vec emission_strengths = arma::zeros(0);
		arma::uvec emission_types = arma::uvec(0, arma::fill::zeros);

		int returned = 0;

		void
		update_pheromones(
			double time
		);

		void
		smell_pheromones(
			const Food &food,
			const Home &home
		);

		AntColony(
			int n_ants,
			const arma::vec &origin
		);

		void
		move(
			const Food &food,
			const Home &home,
			double d_time
		);

};