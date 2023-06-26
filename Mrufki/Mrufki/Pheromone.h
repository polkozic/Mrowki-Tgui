class Pheromone{
public:
	Pheromone();
	Pheromone(int mx,int my,int pot) :x(mx),y(my), potency(pot) {};
	int potency;
	void up(int pot);
	int x;
	int y;
	void down(int pot);
private:

};

