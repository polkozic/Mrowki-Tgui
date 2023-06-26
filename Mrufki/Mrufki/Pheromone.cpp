#include "Pheromone.h";

void Pheromone::up(int pot) {
	potency += pot;
}
void Pheromone::down(int pot) {
	potency -= pot;
}