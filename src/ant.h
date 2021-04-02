#include <SFML/Graphics.hpp>
#include <math.h>

#define PI 3.14159265

std::pair<double, double>
random_target();

class Ant {

	sf::CircleShape shape;

	double speed = 0.1;
	
	public:
		std::pair<double, double> direction = random_target();

		Ant(sf::RenderWindow & window,
			double x = 0.,
			double y = 0.);

		void
		follow_target(const std::pair<int, int> &target,
					  sf::RenderWindow & window);

		void move(sf::RenderWindow & window);

		void
		new_direction();
		
};