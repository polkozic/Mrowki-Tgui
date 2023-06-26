#include <SFML/Graphics.hpp>

class Entity{
public:
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
    int x;
    int y;
    

private:
	sf::Color Color;
	bool passable;
};

class Drawfield : public sf::Drawable, public sf::Transformable {
public:
    void load(Entity*** test, const int rows, const int columns, int size) {
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(rows * columns * 4);
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
            m_vertices[599].color = sf::Color::White;
        }

    }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(m_vertices, states);
    }
    sf::VertexArray m_vertices;

};

