#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <time.h>
#include "Pheromone.h"
#include <memory>
#include<iostream>
#include <math.h>
#include <algorithm>

enum states{looking,returning,dead};
enum Type{ant,food,anthole,obstacle};
enum Direction{ UP, UPRIGHT, MIDRIGHT, DOWNRIGHT, DOWN, DOWNLEFT, MIDLEFT, UPLEFT };
class Sim_field
{
public:
    int rows;
    int columns;
    Sim_field(int mrows, int mcolumns) :rows(mrows), columns(mcolumns) {};
};
struct Cord {
    int x;
    int y;
    float distance;
    Cord(int mx, int my,float mdistance=0) {
        this->x = mx;
        this->y = my;
        this->distance = mdistance;
    }
    bool operator<(Cord tocomp) {
        return distance < tocomp.distance;
    }
};

class Entity {
private:
    sf::Color Color;
    
public:
    Type Entity_Type;
    std::vector<Cord> taboo;
    bool passable;
    void Set_color(sf::Color buffer) {
        Color = buffer;
    }
    sf::Color Get_color() {
        return Color;
    }
    int getx() {
        return x;
    }
    int gety() {
        return y;
    }
    Entity(int mx, int my,sf::Color kol) :x(mx),y(my),Color(kol){
        passable = true;
    }
    Entity() {};
    int x;
    int y;
    bool move(Entity*** test, int x, int y);
    //virtual bool  rand_mov(Entity*** test, Sim_field gamefield)=0;
    
};
class AntHole : public Entity {
public:
    int current_food;
    AntHole(int mx, int my, sf::Color kol) :Entity(mx, my, kol) {
        this->current_food =100;
        this->Entity_Type = anthole;
    }
    AntHole() {
        
    }
    Entity* produce_ant(Entity*** test, Sim_field gamefield,int &TTL);
    void up();
    void down();
};
class Drawfield : public sf::Drawable, public sf::Transformable {
public:
    void load(Entity*** test,Pheromone*** test1,const int rows, const int columns, int size,bool whattodisplay) {
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(rows * columns * 4);
        if (whattodisplay == false) {
            //wyswietlanie pola symulacji
            for (int i = 0; i < rows; i++) {
                //std::cout << "tik";
                for (int j = 0; j < columns; j++) {
                    //std::cout << "test";
                    //sf::Vertex* quad = &m_vertices[(i*columns + j) * 4];
                    m_vertices[(i * columns + j) * 4].position = sf::Vector2f(j * size, i * size);
                    m_vertices[(i * columns + j) * 4 + 1].position = sf::Vector2f((j + 1) * size, i * size);
                    m_vertices[(i * columns + j) * 4 + 2].position = sf::Vector2f((j + 1) * size, (i + 1) * size);
                    m_vertices[(i * columns + j) * 4 + 3].position = sf::Vector2f(j * size, (i + 1) * size);

                    if (test[i][j] != nullptr) {
                        //std::cout << "test";
                        m_vertices[(i * columns + j) * 4].color = test[i][j]->Get_color();
                        m_vertices[(i * columns + j) * 4 + 1].color = test[i][j]->Get_color();
                        m_vertices[(i * columns + j) * 4 + 2].color = test[i][j]->Get_color();
                        m_vertices[(i * columns + j) * 4 + 3].color = test[i][j]->Get_color();
                    }
                    else {
                        m_vertices[(i * columns + j) * 4].color = sf::Color::White;
                        m_vertices[(i * columns + j) * 4 + 1].color = sf::Color::White;
                        m_vertices[(i * columns + j) * 4 + 2].color = sf::Color::White;
                        m_vertices[(i * columns + j) * 4 + 3].color = sf::Color::White;
                    }
                }
                //m_vertices[599].color = sf::Color::White;
            }
        }
        //wyswietlanie feromonow
        else {
            for (int i = 0; i < rows; i++) {
                //std::cout << "tik";
                for (int j = 0; j < columns; j++) {
                    //std::cout << "test";
                    //sf::Vertex* quad = &m_vertices[(i*columns + j) * 4];
                    m_vertices[(i * columns + j) * 4].position = sf::Vector2f(j * size, i * size);
                    m_vertices[(i * columns + j) * 4 + 1].position = sf::Vector2f((j + 1) * size, i * size);
                    m_vertices[(i * columns + j) * 4 + 2].position = sf::Vector2f((j + 1) * size, (i + 1) * size);
                    m_vertices[(i * columns + j) * 4 + 3].position = sf::Vector2f(j * size, (i + 1) * size);

                    if (test1[i][j] != nullptr) {
                        //std::cout << "test";
                        sf::Color color(0, 255, 0,100+(test1[i][j]->potency)*3);
                        m_vertices[(i * columns + j) * 4].color = color;
                        m_vertices[(i * columns + j) * 4 + 1].color = color;
                        m_vertices[(i * columns + j) * 4 + 2].color = color;
                        m_vertices[(i * columns + j) * 4 + 3].color = color;
                    }
                    else {
                        m_vertices[(i * columns + j) * 4].color = sf::Color::White;
                        m_vertices[(i * columns + j) * 4 + 1].color = sf::Color::White;
                        m_vertices[(i * columns + j) * 4 + 2].color = sf::Color::White;
                        m_vertices[(i * columns + j) * 4 + 3].color = sf::Color::White;
                    }
                }
                m_vertices[599].color = sf::Color::White;
            }
        }
    }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(m_vertices, states);
    }
    sf::VertexArray m_vertices;

};
class Food :public Entity {
public:
    int quantity;
    bool down();
    Food(int mx, int my,int mquantity,sf::Color color=sf::Color::Red):Entity(mx,my,color), quantity(mquantity) {
        Entity_Type = food;
    }
};
class Ant: public Entity{
public:
    std::vector<Cord> movelist;
    states current_state;
    int TTL;
    int pheromone_power;
    Direction direction;
    Ant(int mx, int my, sf::Color kol,int m_TTL) :Entity(mx, my, kol) {
        this->current_state = looking;
        TTL = 450;
        pheromone_power = 0;
        direction = static_cast<Direction>(0);
        
   }
    bool  rand_mov(Entity*** test, Sim_field gamefield);
    static int Ant_amount;
    Cord Look_for_food(Entity*** test, Sim_field gamefield,int &distance);
    Cord Look_for_hole(Entity*** test, Sim_field gamefield,int &distance);
    bool check_for_legality(Cord tocheck);
    bool move_towards(Entity*** test, Sim_field gamefield, Cord target);
    bool move_towards_pheromone(Entity*** test, Sim_field gamefield, Pheromone*** pherotable, Sim_field pherosize,int &trust);
    void down(int pot = 1);
    bool operator<(const Ant& second) {
        return current_state < second.current_state;
    }
private:
    //unsigned int TTL;
    //unsigned int TravelDistance;
    
    //static int Ants_Engaged;
};
class rock :public Entity {
public:
    rock(int mx, int my, sf::Color kol) :Entity(mx, my, kol) {
        this->passable = false;
        Entity_Type = obstacle;
    }
};
class Antoverseer {
public:
    Antoverseer(Cord holeplace) {
        this->hole =new AntHole(holeplace.x,holeplace.y,sf::Color::Cyan);
        std::cout << static_cast<AntHole*>(hole)->current_food;
    }
    int get_current_food() {
        return static_cast<AntHole*>(hole)->current_food;
    }
    bool move_ant(Entity*** anttable, Sim_field antsize, int antnumber, Cord target);
    std::vector<Entity*> ants;
    std::vector<Pheromone*> pheromones;
    bool add_pheromone(Pheromone*** pherotable, int x, int y, int potency);
    bool add_ant(Entity* topass);
    bool live(Entity*** anttable, Sim_field antsize, Pheromone*** pherotable, Sim_field pherosize, int &pheromoneleft,int &TTL,int &uncertainty,int &food_distance, int &hole_distance);
    Entity *hole;
    void pheromone_dissipation(Pheromone*** pherotable);
    void Age_ants(Entity*** anttable);
};