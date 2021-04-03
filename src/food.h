#include <armadillo>

struct Food {
	const arma::vec pos;
	const double size;
	const double pheromone_size;
};