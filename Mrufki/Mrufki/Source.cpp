#include <SFML/Graphics.hpp>
#include <array>
#include <TGUI/TGUI.hpp>
#include "Entity.h"
int Ant::Ant_amount = 0;
bool Initialize_simulation(tgui::EditBox::Ptr new_rows,tgui::EditBox::Ptr new_columns, int &rows,int &columns,bool &preparation) {
    rows= tgui::String(new_rows->getText()).toInt(100);
    columns= tgui::String(new_columns->getText()).toInt(100);
    preparation = false;
    return false;
}
bool Add_Food(Entity*** test, Sim_field pole,int food_amount,sf::RenderWindow &window,int cellsize) {
    float x_fl = sf::Mouse::getPosition(window).y;
    x_fl = x_fl / cellsize;
    
    int x=std::round(x_fl);
    std::cout << x;
    float y_fl = sf::Mouse::getPosition(window).x;
    y_fl = y_fl / cellsize;
    int y = std::round(y_fl);
    if (x >= 0 and y >= 0 and x < pole.rows and y < pole.columns and test[x][y] == nullptr) {
        test[x][y] = new Food(x, y, food_amount);
        return true;
    }
    return false;
}
bool Add_Obstacle(Entity*** test, Sim_field pole, int food_amount, sf::RenderWindow& window, int cellsize) {
    float x_fl = sf::Mouse::getPosition(window).y;
    x_fl = x_fl / cellsize;
    int x = std::round(x_fl);
    float y_fl = sf::Mouse::getPosition(window).x;
    y_fl = y_fl / cellsize;
    int y = std::round(y_fl);
    if (x >= 0 and y >= 0 and x < pole.rows and y < pole.columns and test[x][y] == nullptr) {
        test[x][y] = new rock(x, y, sf::Color::Black);
        return true;
    }
    return false;
}
int resize(sf::RenderWindow& window, Sim_field pole) {
    double x = 1000;
    
    if (x) {
        if (pole.rows<=pole.columns) {
            return std::floor(x / static_cast<double>(pole.rows));
        }
        else {
            return std::floor(x / static_cast<double>(pole.columns));
        }
    }
    
}
int clamp(int value, int low, int high) {
    if (value < low) {
        return low;
    }
    else if (value > high) {
        return high;
    }
    return value;
}
int main()
{
    
    
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!",sf::Style::Titlebar | sf::Style::Close);
    //sf::RenderWindow window1(sf::VideoMode(1000, 1000), "SFML works!");
    //sf::RenderWindow window1{{800, 600}, "TGUI window with SFML"};
    //window.setSize(sf::Vector2u(100, 1000));
    tgui::GuiSFML gui{ window };
    tgui::GuiSFML prep{ window };
    tgui::Theme::setDefault("C:/TGUI-0.9/themes/Black.txt");
    //tworzenie tablicy 2d dynamicznej entity
   
    window.setFramerateLimit(60);
    sf::Clock tick;
    sf::Time elapsed = sf::milliseconds(0);
    sf::Clock phero_tick;
    sf::Time phero_elapsed= sf::milliseconds(0);
    int i=0;
    int j=0;
    //test[0][0].Set_color(sf::Color::Green);
    //test[0][0].x = 0;
    //test[0][0].y = 0;
    int x=0;
    int y=0;
    
    
    Cord Ant_Hole(-1, -1);
    
    int rows = 100;
    int columns = 100;
    int time_to_compute = 10;
    int pheromone_compute = 10;
    int pheromoneleft=3000;
    int TTL = 800;
    int uncertainty = 40;
    int food_sight = 6;
    int hole_sight = 5;
    bool preparation = true;
    bool stop = false;
    bool pheromones = false;
    bool options = false;
    bool food_placing = false;
    int food_power = 10;
    bool rock_placing = false;
    prep.setTextSize(20);
    auto rows_text_box = tgui::EditBox::create();
    rows_text_box->setSize({ "66.67%", "12.5%" });
    rows_text_box->setPosition({ "10%", "10%" });
    rows_text_box->setDefaultText("Ilosc wierszy");
    
    auto column_text_box = tgui::EditBox::create();
    column_text_box->setSize({ "66.67%", "12.5%" });
    column_text_box->setPosition({ "10%", "22.5%" });
    column_text_box->setDefaultText("Ilosc kolumn");
    auto prep_button= tgui::Button::create();
    prep_button->setSize({ "20%", "12.5%" });
    prep_button->setPosition({ "50%", "50%" });
    prep_button->setText("Rozpocznij");
    prep_button->onPress(&Initialize_simulation,rows_text_box,column_text_box,std::ref(rows),std::ref(columns),std::ref(preparation));
    prep.add(rows_text_box);
    prep.add(column_text_box);
    prep.add(prep_button);
    //Budowa GUI
    auto label = tgui::Label::create();
    label->setPosition({ "15%", "85%" });;
    gui.add(label);
    auto Pheromone_left_edit = tgui::EditBox::create();
    Pheromone_left_edit->setPosition({ "5%", "5%" });
    Pheromone_left_edit->setSize({ "30%", "10%" });
    auto Pheromone_text = tgui::Label::create();
    Pheromone_text->setPosition({ "35%", "5%" });
    Pheromone_text->setText("Ilosc feromonu do dyspozycji");
    gui.add(Pheromone_text);
    gui.add(Pheromone_left_edit);
    auto TTL_edit = tgui::EditBox::create();
    TTL_edit->setPosition({ "5%", "15%" });
    TTL_edit->setSize({ "30%", "10%" });
    auto TTL_text= tgui::Label::create();
    TTL_text->setPosition({ "35%", "15%" });
    TTL_text->setText("czas zycia mrowek");
    gui.add(TTL_edit);
    gui.add(TTL_text);
    auto uncertainty_edit = tgui::EditBox::create();
    uncertainty_edit->setPosition({ "5%", "25%" });
    uncertainty_edit->setSize({ "30%", "10%" });
    auto uncertainty_text = tgui::Label::create();
    uncertainty_text->setPosition({ "35%", "25%" });
    uncertainty_text->setText("szansa na odrzucenie feromonu");
    gui.add(uncertainty_edit);
    gui.add(uncertainty_text);
    auto compute_edit= tgui::EditBox::create();
    compute_edit->setPosition({ "5%", "35%" });
    compute_edit->setSize({ "30%", "10%" });
    auto  compute_text = tgui::Label::create();
    compute_text->setPosition({ "35%", "35%" });
    compute_text->setText("co ile milisekund mrowki wykonuja obliczenia");
    gui.add(compute_edit);
    gui.add(compute_text);
    auto food_distance_edit= tgui::EditBox::create();
    food_distance_edit->setPosition({ "5%", "45%" });
    food_distance_edit->setSize({ "30%", "10%" });
    auto  food_distance_text = tgui::Label::create();
    food_distance_text->setPosition({ "35%", "45%" });
    food_distance_text->setText("dystans na ktory mrowka widzi jedzenie");
    gui.add(food_distance_edit);
    gui.add(food_distance_text);
    auto hole_distance_edit = tgui::EditBox::create();
    hole_distance_edit->setPosition({ "5%", "55%" });
    hole_distance_edit->setSize({ "30%", "10%" });
    auto  hole_distance_text = tgui::Label::create();
    hole_distance_text->setPosition({ "35%", "55%" });
    hole_distance_text->setText("dystans na ktory mrowka widzi mrowisko");
    gui.add(hole_distance_edit);
    gui.add(hole_distance_text);
    auto food_power_edit = tgui::EditBox::create();
    food_power_edit->setPosition({ "5%", "65%" });
    food_power_edit->setSize({ "30%", "10%" });
    auto  food_power_text = tgui::Label::create();
    food_power_text->setPosition({ "35%", "65%" });
    food_power_text->setText("ilosc jedzenia w stawianym jedzeniu");
    gui.add(food_power_edit);
    gui.add(food_power_text);
    auto pheromone_compute_edit = tgui::EditBox::create();
    pheromone_compute_edit->setPosition({ "5%", "75%" });
    pheromone_compute_edit->setSize({ "30%", "10%" });
    auto  pheromone_compute_text = tgui::Label::create();
    pheromone_compute_text->setPosition({ "35%", "75%" });
    pheromone_compute_text->setText("Co ile ruchow mrowek usuwac feromony");
    gui.add(pheromone_compute_edit);
    gui.add(pheromone_compute_text);
    //gui.add(editBox, "MyWidgetName");
    window.setSize(sf::Vector2u(1000, 1000));
    //Inicjalizacja Symulacji
    while (window.isOpen() and  preparation) {
        sf::Event prep_event;
        while (window.pollEvent(prep_event)) {
           prep.handleEvent(prep_event);
           if (prep_event.type==sf::Event::Closed) {
               window.close();
               break;
           }
        }
        
        window.clear();
        prep.draw();
        window.display();
    }
    Sim_field pole(rows, columns);
    //Przygotowanie symulacji
    Entity*** test = new Entity * *[rows];
    for (int i = 0; i < rows; i++) {
        test[i] = new Entity * [columns];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            //std::cout << "pong";
            //test[i][j]->Set_color(sf::Color::White);
            test[i][j] = nullptr;
            //test[i][j].y = j;
        }
    }
    //tworzymy tablicy 2d dynamicznej feromonów
    Pheromone*** test1 = new Pheromone * *[rows];
    for (int i = 0; i < rows; i++) {
        test1[i] = new Pheromone * [columns];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            //std::cout << "pong";
            //test[i][j]->Set_color(sf::Color::White);
            test1[i][j] = nullptr;
            //test[i][j].y = j;
        }
    }
    Drawfield drawwin;
    int cellsize = resize(window, pole);
    drawwin.load(test, test1, rows, columns, cellsize, false);
    //Wybieranie lokacji mrowiska
    while (window.isOpen() and Ant_Hole.x==-1) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { 
                std::cout << "click";
                float x_fl = sf::Mouse::getPosition(window).y;
                x_fl = x_fl / cellsize;
                int x = std::round(x_fl);
                float y_fl = sf::Mouse::getPosition(window).x;
                y_fl = y_fl / cellsize;
                int y = std::round(y_fl);
                Ant_Hole.x = x;
                Ant_Hole.y = y;
            }

        }
        drawwin.load(test, test1, rows, columns, cellsize, false);
        window.clear();
        window.draw(drawwin);
        window.display();
    }
    Antoverseer nad(Ant_Hole);
    test[Ant_Hole.x][Ant_Hole.y] = nad.hole;
    //test[60][60] = new Food(60, 60, 10000);
    
   
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(options)gui.handleEvent(event);
            switch (event.type)
            {
                // window closed
            case sf::Event::Closed:
                window.close();
                break;

                // key pressed
            case sf::Event::KeyPressed:
                if (event.key.code==sf::Keyboard::Space) {
                    if (stop == false) {
                        stop = true;
                    }
                    else {
                        stop = false;
                    }
                }
                else if (event.key.code == sf::Keyboard::Add) {
                    time_to_compute = clamp(time_to_compute + 5, 5, 500);
                }
                else if (event.key.code == sf::Keyboard::Subtract) {
                    time_to_compute = clamp(time_to_compute - 5, 5, 500);
                }
                else if (event.key.code == sf::Keyboard::E) {
                    if (pheromones == false) {
                        pheromones = true;
                    }
                    else {
                        pheromones = false;
                    }
                }
                else if (event.key.code == sf::Keyboard::F) {
                    if (food_placing == false) {
                        rock_placing = false;
                        food_placing = true;
                    }
                    else {
                        food_placing = false;
                    }
                }
                else if (event.key.code == sf::Keyboard::R) {
                    if (rock_placing == false) {
                        food_placing = false;
                        rock_placing = true;
                    }
                    else {
                        rock_placing = false;
                    }
                }
                else if (event.key.code == sf::Keyboard::O) {
                    if (options == false) {
                        options = true;
                        food_placing = false;
                        rock_placing = false;
                        window.setSize(sf::Vector2u(500, 500));
                        uncertainty_edit->setDefaultText(tgui::String(uncertainty));
                        TTL_edit->setDefaultText(tgui::String(TTL));
                        Pheromone_left_edit->setDefaultText(tgui::String(pheromoneleft));
                        compute_edit->setDefaultText(tgui::String(time_to_compute));
                        food_distance_edit->setDefaultText(tgui::String(food_sight));
                        hole_distance_edit->setDefaultText(tgui::String(hole_sight));
                        food_power_edit->setDefaultText(tgui::String(food_power));
                        pheromone_compute_edit->setDefaultText(tgui::String(pheromone_compute));
                    }
                    else {
                        options = false;
                        uncertainty= tgui::String(uncertainty_edit->getText()).toInt(uncertainty);
                        TTL = tgui::String(TTL_edit->getText()).toInt(TTL);
                        pheromoneleft = tgui::String(Pheromone_left_edit->getText()).toInt(pheromoneleft);
                        time_to_compute= tgui::String(compute_edit->getText()).toInt(time_to_compute);
                        food_sight= tgui::String(food_distance_edit->getText()).toInt(food_sight);
                        hole_sight = tgui::String(hole_distance_edit->getText()).toInt(hole_sight);
                        food_power= tgui::String(food_power_edit->getText()).toInt(food_power);
                        pheromone_compute= tgui::String(pheromone_compute_edit->getText()).toInt(pheromone_compute);
                        uncertainty_edit->setFocused(0);
                        TTL_edit->setFocused(0);
                        Pheromone_left_edit->setFocused(0);
                        compute_edit->setFocused(0);
                        food_distance_edit->setFocused(0);
                        hole_distance_edit->setFocused(0);
                        food_power_edit->setFocused(0);
                        pheromone_compute_edit->setFocused(0);
                        window.setSize(sf::Vector2u(1000, 1000));
                        std::cout << TTL;
                    }
                }
                
                    break;
            case(sf::Event::MouseButtonPressed): {
                if (event.key.code == sf::Mouse::Left and food_placing) {
                    std::cout << "click";
                    Add_Food(test, pole, food_power, window, cellsize);
                }
                else if (event.key.code == sf::Mouse::Left and rock_placing) {
                    std::cout << "click";
                    Add_Obstacle(test, pole, 100, window, cellsize);
                }
                        break;
                    }
                // we don't process other types of events
            default:
                break;
            }

        }
        
        elapsed += tick.getElapsedTime();
        phero_elapsed += tick.getElapsedTime();
        tick.restart();
        //std::cout << Ant::Ant_amount;
        if (elapsed >= sf::milliseconds(time_to_compute) and !stop and !options) {
            //i++;
            
            //std::cout << test[i][j].x << " " << test[i][j].y;
            
            nad.live(test, pole, test1, pole,pheromoneleft,TTL,uncertainty,food_sight,hole_sight);
            
            nad.Age_ants(test);
            elapsed = sf::microseconds(0);
        }
        if (phero_elapsed >= sf::milliseconds(time_to_compute*pheromone_compute) and !stop and !options) {
            //std::cout << Ant::Ant_amount << std::endl;
            nad.pheromone_dissipation(test1);
            
            label->setText(tgui::String( Ant::Ant_amount));
            phero_elapsed = sf::milliseconds(0);
        }
        if (!options)drawwin.load(test, test1, rows, columns,cellsize , pheromones);
        window.clear();
        if(!options)window.draw(drawwin);
        if(options)gui.draw();

        window.display();
    }
    
    return 0;
}