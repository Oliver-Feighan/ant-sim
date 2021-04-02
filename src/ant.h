#include <armadillo>

class AntColony {
	const double steering_probability = 0.1;
	const double steering_factor = 1;
	const double speed = 5;

	const double home_pheromone_freq = 0.01;
	const double home_pheromone_time_c = 1;
	const double home_pheromone_distance_c = 200;

	public:
		int n_ants;

		arma::mat positions;
		arma::mat directions;
		arma::uvec follow_modes;

		arma::mat emitting_positions = arma::zeros(2, 0);
		arma::vec emission_times = arma::zeros(0);


		std::function<double(const arma::vec &coor, const double time)>
		make_home_pheromones(
			double time
		);

		AntColony(
			int n_ants,
			const arma::vec &origin
		);

		void
		move();

};