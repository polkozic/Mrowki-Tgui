#include "Entity.h"
std::mt19937 gen(time(NULL));
bool Entity::move(Entity*** test, int x, int y) {
    if (test[x][y] != nullptr) {
        if (test[x][y]->Entity_Type == ant and test[x][y]->passable==true) {
            test[x][y] = test[this->getx()][this->gety()];
            test[this->getx()][this->gety()] = nullptr;
            this->x = x;
            this->y = y;
            //std::cout << "case";
            return true;
        }
        return false;
    }
    else {
        test[x][y] = test[this->getx()][this->gety()];
        test[this->getx()][this->gety()] = nullptr;
        this->x = x;
        this->y = y;
        return true;
    }

}
bool Ant::check_for_legality(Cord tocheck) {
    if (taboo.empty()) {
        return 1;
    }
    for (int i = 0; i < taboo.size() - 1; i++) {
        if (tocheck.x == taboo[i].x and tocheck.y == taboo[i].y) {
            return 0;
        }
    }
    return 1;
}
bool  Ant::rand_mov(Entity*** test, Sim_field gamefield) {
    //std::vector<Cord> possibilities;
    //stara metoda losowania ruchu (kiepska)
    //lewy górny róg
    /*if (x - 1 >= 0 and y - 1 >= 0 and test[x - 1][y - 1] == nullptr and check_for_legality(Cord(x - 1, y - 1))) {
        possibilities.push_back(Cord(x - 1, y - 1));
    }
    //góra
    if (x - 1 >= 0 and test[x - 1][y] == nullptr and check_for_legality(Cord(x - 1, y))) {
        possibilities.push_back(Cord(x - 1, y));
    }
    //prawy górny róg
    if (x - 1 >= 0 and y + 1 < gamefield.columns and test[x - 1][y + 1] == nullptr and check_for_legality(Cord(x - 1, y + 1))) {
        possibilities.push_back(Cord(x - 1, y + 1));
    }
    //prawy œrodek
    if (x >= 0 and y + 1 < gamefield.columns and test[x][y + 1] == nullptr and check_for_legality(Cord(x, y + 1))) {
        possibilities.push_back(Cord(x, y + 1));
    }
    //Prawy dolny róg
    if (x + 1 < gamefield.rows and y + 1 < gamefield.columns and test[x + 1][y + 1] == nullptr and check_for_legality(Cord(x + 1, y + 1))) {
        possibilities.push_back(Cord(x + 1, y + 1));
    }
    //dó³
    if (x + 1 < gamefield.rows and test[x + 1][y] == nullptr and check_for_legality(Cord(x + 1, y))) {
        possibilities.push_back(Cord(x + 1, y));
    }
    //lewy dolny róg
    if (x + 1 < gamefield.rows and y - 1 >= 0 and test[x + 1][y - 1] == nullptr and check_for_legality(Cord(x + 1, y - 1))) {
        possibilities.push_back(Cord(x + 1, y - 1));
    }
    //lewy œrodek
    if (x >= 0 and y - 1 >= 0 and test[x][y - 1] == nullptr and check_for_legality(Cord(x, y - 1))) {
        possibilities.push_back(Cord(x, y - 1));
    }
    */
    //TROCHE NOWSZA (nadal kiepska)
    /*
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            //if (i == x and j == y) continue;
            if (i >= 0 and j >= 0 and i < gamefield.rows and j < gamefield.columns and test[i][j] == nullptr ) {
                possibilities.push_back(Cord(i, j));
            }
            else if (i >= 0 and j >= 0 and i < gamefield.rows and j < gamefield.columns and test[i][j] != nullptr and test[i][j]->Entity_Type==ant) {
                possibilities.push_back(Cord(i, j));
            }
        }
    }
    std::random_device rd;
    if (possibilities.size() == 0) {
        //std::cout << "taboo";
        this->taboo.clear();
        return false;
    }
    std::uniform_int_distribution<> distrib(0, possibilities.size() - 1);
    int chosen = distrib(gen);
    this->move(test, possibilities[chosen].x, possibilities[chosen].y);
    possibilities.clear();
    return true;
    */
    //METODA UWZGLÊDNIAJ¥CA KIERUNEK
    // 0-skrec w lewo, 1-kieruj sie prosto, 2-skrec w prawo
    std::uniform_int_distribution<> distrib(0, 3);
    int chosen = distrib(gen);
    std::uniform_int_distribution<> randomdir(0, 7);
    int chosendir = randomdir(gen);
    //std::cout << chosen;
    switch (direction)
    {
    case UP:
        switch (chosen)
        {
        case 0:
            if (x - 1 >= 0 and y - 1 >= 0) {
                direction = UPLEFT;
                if (!move(test, x - 1, y - 1)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction= static_cast<Direction>(chosendir);
                return false;
            }
        break;
        case 1:
            if (x - 1 >= 0) {
                
                if (!move(test, x - 1, y)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
        break;
        case 2:
            if (x - 1 >= 0 and y + 1 < gamefield.columns) {
                direction = UPRIGHT;
                if (!move(test, x - 1, y + 1)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
        break;
        case 3:
            if (x - 1 >= 0) {

                if (!move(test, x - 1, y)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
        default:
            break;
        }
        break;
    case UPLEFT:
        switch (chosen)
        {
        case 0:
            if (x >= 0 and y - 1 >= 0) {
                direction = MIDLEFT;
                if (!move(test, x, y - 1)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
            break;
        case 1:
            if (x - 1 >= 0 and y - 1 >= 0) {

                if (!move(test, x - 1, y - 1)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
            break;
        case 2:
            if (x - 1 >= 0) {
                direction = UP;
                if (!move(test, x - 1, y)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
            break;
        case 3:
            if (x - 1 >= 0 and y - 1 >= 0) {

                if (!move(test, x - 1, y - 1)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
        default:
            break;
        }
        break;
    case MIDLEFT:
        switch (chosen)
        {
        case 0:
            if (x + 1 < gamefield.rows and y - 1 >= 0) {
                direction = DOWNLEFT;
                if (!move(test, x + 1, y - 1)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
            break;
        case 1:
            if (x >= 0 and y - 1 >= 0) {

                if(!move(test, x, y - 1)){
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
            break;
        case 2:
            if (x - 1 >= 0 and y - 1 >= 0) {
                direction = UPLEFT;
                if (!move(test, x - 1, y - 1)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
            break;
        case 3:
            if (x >= 0 and y - 1 >= 0) {

                if(!move(test, x, y - 1)){
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
        default:
            break;
        }
        break;
    case DOWNLEFT:
        switch (chosen)
        {
        case 0:
            if (x + 1 < gamefield.rows) {
                direction = DOWN;
                if (!move(test, x + 1, y)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
            break;
        case 1:
            if (x + 1 < gamefield.rows and y - 1 >= 0) {
                
                if (!move(test, x + 1, y - 1)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
            break;
        case 2:
            if (x >= 0 and y - 1 >= 0) {
                direction = MIDLEFT;
                if (!move(test, x, y - 1)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
            break;
        case 3:
            if (x + 1 < gamefield.rows and y - 1 >= 0) {

                if (!move(test, x + 1, y - 1)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
        default:
            break;
        }
        break;
    case DOWN:
        switch (chosen)
        {
        case 0:
            if (x + 1 < gamefield.rows and y + 1 <gamefield.columns) {
                direction = DOWNRIGHT;
                if (!move(test, x + 1, y + 1)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
            break;
        case 1:
            if (x + 1 < gamefield.rows) {
                
                if(!move(test, x + 1, y)){
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
            break;
        case 2:
            if (x + 1 < gamefield.rows and y - 1 >= 0) {
                direction = DOWNLEFT;
                if (!move(test, x + 1, y - 1)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
            break;
        case 3:
            if (x + 1 < gamefield.rows) {

                if(!move(test, x + 1, y)){
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
        default:
            break;
        }
        break;
    case DOWNRIGHT:
        switch (chosen)
        {
        case 0:
            if (x >= 0 and y + 1 < gamefield.columns) {
                direction = MIDRIGHT;
                if (!move(test, x, y + 1)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
            break;
        case 1:
            if (x + 1 < gamefield.rows and y + 1<gamefield.columns) {
                
                if(!move(test, x + 1, y + 1)){
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
            break;
        case 2:
            if (x + 1 < gamefield.rows) {
                direction = DOWN;
                if (!move(test, x + 1, y)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
            break;
        case 3:
            if (x + 1 < gamefield.rows and y + 1 < gamefield.columns) {

                if (!move(test, x + 1, y + 1)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
        default:
            break;
        }
        break;
    case MIDRIGHT:
        switch (chosen)
        {
        case 0:
            if (x - 1 >= 0 and y + 1 < gamefield.columns) {
                direction = UPRIGHT;
                if (!move(test, x - 1, y + 1)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
            break;
        case 1:
            if (x >= 0 and y + 1 < gamefield.columns) {
                
                if (!move(test, x, y + 1)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
            break;
        case 2:
            if (x + 1 < gamefield.rows and y + 1<gamefield.columns) {
                direction = DOWNRIGHT;
                if (!move(test, x + 1, y + 1)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
            break;
        case 3:
            if (x >= 0 and y + 1 < gamefield.columns) {

                if (!move(test, x, y + 1)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
        default:
            break;
        }
        break;
    case UPRIGHT:
        switch (chosen)
        {
        case 0:
            if (x - 1 >= 0) {
                direction = UP;
                if (!move(test, x - 1, y)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
            break;
        case 1:
            if (x - 1 >= 0 and y + 1 < gamefield.columns) {
                
                if (!move(test, x - 1, y + 1)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
            break;
        case 2:
            if (x >= 0 and y + 1 < gamefield.columns) {
                direction = MIDRIGHT;
                if (!move(test, x, y + 1)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
            break;
        case 3:
            if (x - 1 >= 0 and y + 1 < gamefield.columns) {

                if (!move(test, x - 1, y + 1)) {
                    direction = static_cast<Direction>(chosendir);
                    return false;
                }
                return true;
            }
            else {
                direction = static_cast<Direction>(chosendir);
                return false;
            }
        default:
            break;
        }
        break;
    default:
        return false;
        break;
    }
}
Cord Ant::Look_for_food(Entity*** test, Sim_field gamefield,int &distance) {
    for (int i = x - distance; i < x + distance; i++) {
        for (int j = y - distance; j < y + distance; j++) {
            if (i >= 0 and j >= 0 and i < gamefield.rows and j < gamefield.columns and test[i][j] != nullptr and test[i][j]->Entity_Type == food) {
                //std::cout << "found";
                return Cord(i, j);
            }
        }
    }
    return Cord(-1, -1);
}
Cord Ant::Look_for_hole(Entity*** test, Sim_field gamefield,int &distance) {
    for (int i = x - distance; i < x + distance; i++) {
        for (int j = y - distance; j < y + distance; j++) {
            if (i >= 0 and j >= 0 and i < gamefield.rows and j < gamefield.columns and test[i][j] != nullptr and test[i][j]->Entity_Type == anthole) {
                //std::cout << "found";
                return Cord(i, j);
            }
        }
    }
    return Cord(-1, -1);
}
//usuwa jedno jedzenie, wysy³a false jak jedzenie sie skonczy
bool Food::down() {
    quantity -= 1;
    if (quantity == 0) {
        return false;
    }
    return true;
}
bool Ant::move_towards(Entity*** test, Sim_field gamefield, Cord target) {
    std::vector<Cord> possibilities;
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            possibilities.push_back(Cord(i, j, pow((target.x - i), 2) + pow((target.y - j), 2)));
        }
    }
    std::sort(possibilities.begin(), possibilities.end());
    for (int i = 0; i < possibilities.size() - 1; i++) {
        if (possibilities[i].x >= 0 and possibilities[i].y >= 0 and possibilities[i].x < gamefield.rows and possibilities[i].y < gamefield.columns and check_for_legality(Cord(possibilities[i].x, possibilities[i].y)) and move(test, possibilities[i].x, possibilities[i].y)) {
            //std::cout << possibilities[i].x << " " << possibilities[i].y;
            return true;
        }
    }
    
    return false;
}
bool Ant::move_towards_pheromone(Entity*** test, Sim_field gamefield, Pheromone*** pherotable, Sim_field pherosize,int &trust) {
    std::vector<std::pair<Cord,Direction>> possibilities;
    int pheromone_distance = 1;
    trust = 10;
    int totalphero=0;
    
    /*for (int i = x - pheromone_distance; i < x + pheromone_distance; i++) {
        for (int j = y - pheromone_distance; j < y + pheromone_distance; j++) {
            if (i >= 0 and j >= 0 and i < gamefield.rows and j < gamefield.columns and test[i][j] != nullptr and pherotable[i][j] != nullptr) {
                totalphero += pherotable[i][j]->potency;
                possibilities.push_back(Cord(i, j, pherotable[i][j]->potency));


            }
        }
    }
        possibilities.push_back(Cord(-1, -1, trust));
        totalphero += trust;
        std::uniform_int_distribution<> distrib(0, totalphero);
        int chosen = distrib(gen);
        for (int i = 0; i < possibilities.size() - 1; i++) {
            chosen -= possibilities[i].distance;
            if (chosen <= 0) {
                //this->move_towards(test, gamefield, possibilities[i]);
                this->move(test, possibilities[i].x, possibilities[i].y);
                
                possibilities.clear();
                return true;
            }
        }

        //this->move(test, possibilities[chosen].x, possibilities[chosen].y);
        //taboo.push_back(new Cord(possibilities[chosen].x, possibilities[chosen].y));
        */
    switch (direction)
    {
    case UP:
        //for (int i = 1; i < pheromone_distance + 1; i++) {
            if (x - 1 >= 0 and y - 1 >= 0 and x - 1 < gamefield.rows and y - 1 < gamefield.columns and pherotable[x - 1][y - 1] != nullptr) {
                totalphero += pherotable[x-1][y-1]->potency;
                possibilities.push_back(std::make_pair(Cord(x-1, y-1, pherotable[x-1][y-1]->potency), UPLEFT));
            }
            if (x - 1 >= 0 and y >= 0 and x - 1 < gamefield.rows and y < gamefield.columns and pherotable[x - 1][y ] != nullptr) {
                totalphero += pherotable[x - 1][y]->potency;
                possibilities.push_back(std::make_pair(Cord(x-1, y, pherotable[x-1][y]->potency), UP));
            }
            if (x - 1 >= 0 and y+1 >= 0 and x - 1 < gamefield.rows and y+1 < gamefield.columns and pherotable[x - 1][y+1] != nullptr) {
                totalphero += pherotable[x - 1][y+1]->potency;
                possibilities.push_back(std::make_pair(Cord(x - 1, y+1, pherotable[x - 1][y+1]->potency), UPRIGHT));
            }
       // }
        break;
    case UPRIGHT:
        if (x  >= 0 and y + 1 >= 0 and x  < gamefield.rows and y + 1 < gamefield.columns and pherotable[x][y + 1] != nullptr) {
            totalphero += pherotable[x][y + 1]->potency;
            possibilities.push_back(std::make_pair(Cord(x, y + 1, pherotable[x][y + 1]->potency), MIDRIGHT));
        }
        if (x - 1 >= 0 and y >= 0 and x - 1 < gamefield.rows and y < gamefield.columns and pherotable[x - 1][y] != nullptr) {
            totalphero += pherotable[x - 1][y]->potency;
            possibilities.push_back(std::make_pair(Cord(x - 1, y, pherotable[x - 1][y]->potency), UP));
        }
        if (x - 1 >= 0 and y + 1 >= 0 and x - 1 < gamefield.rows and y + 1 < gamefield.columns and pherotable[x - 1][y + 1] != nullptr) {
            totalphero += pherotable[x - 1][y + 1]->potency;
            possibilities.push_back(std::make_pair(Cord(x - 1, y + 1, pherotable[x - 1][y + 1]->potency), UPRIGHT));
        }
        break;
    case MIDRIGHT:
        if (x >= 0 and y + 1 >= 0 and x < gamefield.rows and y + 1 < gamefield.columns and pherotable[x][y + 1] != nullptr) {
            totalphero += pherotable[x][y + 1]->potency;
            possibilities.push_back(std::make_pair(Cord(x, y + 1, pherotable[x][y + 1]->potency), MIDRIGHT));
        }
        if (x + 1 >= 0 and y+1 >= 0 and x + 1 < gamefield.rows and y+1 < gamefield.columns and pherotable[x + 1][y+1] != nullptr) {
            totalphero += pherotable[x + 1][y+1]->potency;
            possibilities.push_back(std::make_pair(Cord(x + 1, y+1, pherotable[x + 1][y+1]->potency), DOWNRIGHT));
        }
        if (x - 1 >= 0 and y + 1 >= 0 and x - 1 < gamefield.rows and y + 1 < gamefield.columns and pherotable[x - 1][y + 1] != nullptr) {
            totalphero += pherotable[x - 1][y + 1]->potency;
            possibilities.push_back(std::make_pair(Cord(x - 1, y + 1, pherotable[x - 1][y + 1]->potency), UPRIGHT));
        }
        break;
    case DOWNRIGHT:
        if (x >= 0 and y + 1 >= 0 and x < gamefield.rows and y + 1 < gamefield.columns and pherotable[x][y + 1] != nullptr) {
            totalphero += pherotable[x][y + 1]->potency;
            possibilities.push_back(std::make_pair(Cord(x, y + 1, pherotable[x][y + 1]->potency), MIDRIGHT));
        }
        if (x + 1 >= 0 and y + 1 >= 0 and x + 1 < gamefield.rows and y + 1 < gamefield.columns and pherotable[x + 1][y + 1] != nullptr) {
            totalphero += pherotable[x + 1][y + 1]->potency;
            possibilities.push_back(std::make_pair(Cord(x + 1, y + 1, pherotable[x + 1][y + 1]->potency), DOWNRIGHT));
        }
        if (x + 1 >= 0 and y  >= 0 and x + 1 < gamefield.rows and y < gamefield.columns and pherotable[x + 1][y] != nullptr) {
            totalphero += pherotable[x + 1][y]->potency;
            possibilities.push_back(std::make_pair(Cord(x + 1, y, pherotable[x + 1][y]->potency), DOWN));
        }
        break;
    case DOWN:
        if (x+1 >= 0 and y - 1 >= 0 and x+1 < gamefield.rows and y - 1 < gamefield.columns and pherotable[x+1][y - 1] != nullptr) {
            totalphero += pherotable[x+1][y - 1]->potency;
            possibilities.push_back(std::make_pair(Cord(x+1, y - 1, pherotable[x+1][y - 1]->potency), DOWNLEFT));
        }
        if (x + 1 >= 0 and y + 1 >= 0 and x + 1 < gamefield.rows and y + 1 < gamefield.columns and pherotable[x + 1][y + 1] != nullptr) {
            totalphero += pherotable[x + 1][y + 1]->potency;
            possibilities.push_back(std::make_pair(Cord(x + 1, y + 1, pherotable[x + 1][y + 1]->potency), DOWNRIGHT));
        }
        if (x + 1 >= 0 and y >= 0 and x + 1 < gamefield.rows and y < gamefield.columns and pherotable[x + 1][y] != nullptr) {
            totalphero += pherotable[x + 1][y]->potency;
            possibilities.push_back(std::make_pair(Cord(x + 1, y, pherotable[x + 1][y]->potency), DOWN));
        }
        break;
    case DOWNLEFT:
        if (x + 1 >= 0 and y - 1 >= 0 and x + 1 < gamefield.rows and y - 1 < gamefield.columns and pherotable[x + 1][y - 1] != nullptr) {
            totalphero += pherotable[x + 1][y - 1]->potency;
            possibilities.push_back(std::make_pair(Cord(x + 1, y - 1, pherotable[x + 1][y - 1]->potency), DOWNLEFT));
        }
        if (x >= 0 and y - 1 >= 0 and x < gamefield.rows and y - 1 < gamefield.columns and pherotable[x][y - 1] != nullptr) {
            totalphero += pherotable[x][y - 1]->potency;
            possibilities.push_back(std::make_pair(Cord(x, y - 1, pherotable[x][y - 1]->potency), MIDLEFT));
        }
        if (x + 1 >= 0 and y >= 0 and x + 1 < gamefield.rows and y < gamefield.columns and pherotable[x + 1][y] != nullptr) {
            totalphero += pherotable[x + 1][y]->potency;
            possibilities.push_back(std::make_pair(Cord(x + 1, y, pherotable[x + 1][y]->potency), DOWN));
        }
        break;
    case MIDLEFT:
        if (x + 1 >= 0 and y - 1 >= 0 and x + 1 < gamefield.rows and y - 1 < gamefield.columns and pherotable[x + 1][y - 1] != nullptr) {
            totalphero += pherotable[x + 1][y - 1]->potency;
            possibilities.push_back(std::make_pair(Cord(x + 1, y - 1, pherotable[x + 1][y - 1]->potency), DOWNLEFT));
        }
        if (x >= 0 and y - 1 >= 0 and x < gamefield.rows and y - 1 < gamefield.columns and pherotable[x][y - 1] != nullptr) {
            totalphero += pherotable[x][y - 1]->potency;
            possibilities.push_back(std::make_pair(Cord(x, y - 1, pherotable[x][y - 1]->potency), MIDLEFT));
        }
        if (x - 1 >= 0 and y - 1 >= 0 and x - 1 < gamefield.rows and y - 1 < gamefield.columns and pherotable[x - 1][y - 1] != nullptr) {
            totalphero += pherotable[x - 1][y - 1]->potency;
            possibilities.push_back(std::make_pair(Cord(x - 1, y - 1, pherotable[x - 1][y - 1]->potency), UPLEFT));
        }
        break;
    case UPLEFT:
        if (x - 1 >= 0 and y >= 0 and x - 1 < gamefield.rows and y < gamefield.columns and pherotable[x - 1][y] != nullptr) {
            totalphero += pherotable[x - 1][y]->potency;
            possibilities.push_back(std::make_pair(Cord(x - 1, y, pherotable[x - 1][y]->potency), UP));
        }
        if (x >= 0 and y - 1 >= 0 and x < gamefield.rows and y - 1 < gamefield.columns and pherotable[x][y - 1] != nullptr) {
            totalphero += pherotable[x][y - 1]->potency;
            possibilities.push_back(std::make_pair(Cord(x, y - 1, pherotable[x][y - 1]->potency), MIDLEFT));
        }
        if (x - 1 >= 0 and y - 1 >= 0 and x - 1 < gamefield.rows and y - 1 < gamefield.columns and pherotable[x - 1][y - 1] != nullptr) {
            totalphero += pherotable[x - 1][y - 1]->potency;
            possibilities.push_back(std::make_pair(Cord(x - 1, y - 1, pherotable[x - 1][y - 1]->potency), UPLEFT));
        }
        break;
    default:
        break;
    }
    possibilities.push_back(std::make_pair(Cord(-1, - 1, trust), UPLEFT));
    totalphero += trust;
    
    std::uniform_int_distribution<> distrib(0, totalphero);
    int chosen = distrib(gen);
    
    for (int i = 0; i < possibilities.size(); i++) {
        chosen -= possibilities[i].first.distance;
        if (chosen <= 0) {
            //this->move_towards(test, gamefield, possibilities[i]);
            if (possibilities[i].first.x == -1) {
                //std::cout << "fail";
                return false;
            }
            this->move(test, possibilities[i].first.x, possibilities[i].first.y);
            direction = possibilities[i].second;
            possibilities.clear();
            return true;
        }
    }
        possibilities.clear();
        return false;

    
}
void Ant::down(int pot) {
    TTL -= pot;
}
void AntHole::up() {
    current_food +=1;
}
void AntHole::down() {
    current_food -= 1;
}
Entity* AntHole::produce_ant(Entity*** test, Sim_field gamefield,int &TTL){
    if (current_food <= 0) {
        //std::cout << "glodny";
        return nullptr;
    }
    int distance = 1;
    std::vector<Cord> possibilities;
    for (int i = x - distance; i < x + distance; i++) {
        for (int j = y - distance; j < y + distance; j++) {
            if (i >= 0 and j >= 0 and i < gamefield.rows and j < gamefield.columns and test[i][j] == nullptr ) {
                //std::cout << "found";
                possibilities.push_back(Cord(i, j));
            }
        }
    }
    std::random_device rd;
    if (possibilities.size() == 0) {
        return nullptr;
    }
    std::uniform_int_distribution<> distrib(0, possibilities.size() - 1);
    int chosen = distrib(gen);
    Entity* buff= new Ant(possibilities[chosen].x, possibilities[chosen].y, sf::Color::Black,TTL);
    test[possibilities[chosen].x][possibilities[chosen].y] = buff;
    //mrówka patrzy w losow¹ stronê
    std::uniform_int_distribution<> distrib1(0, 7);
    int chosen1 = distrib1(gen);
    static_cast<Ant*>(test[possibilities[chosen].x][possibilities[chosen].y])->direction = static_cast<Direction>(chosen1);
   
    down();
    //std::cout << current_food;
    return buff;
}
bool Antoverseer::add_ant(Entity* topass) {
    ants.push_back(topass);
    Ant::Ant_amount++;
    return 1;
}
bool Antoverseer::add_pheromone(Pheromone*** pherotable, int x, int y, int potency) {
    if (pherotable[x][y] == nullptr) {
        pherotable[x][y] = new Pheromone(x,y,potency);
        pheromones.push_back(pherotable[x][y]);
    }
    else {
        pherotable[x][y]->up(potency);
    }
    return 1;
}
void Antoverseer::pheromone_dissipation(Pheromone*** pherotable){
    if (!pheromones.empty()) {
        for (int i = 0; i < pheromones.size() - 1; i++) {
            pheromones[i]->down(1);
            if (pheromones[i]->potency <= 0) {
                int x = pheromones[i]->x;
                int y = pheromones[i]->y;
                delete pheromones[i];
                pheromones.erase(pheromones.begin() + i);
                pherotable[x][y] = nullptr;

            }
        }
    }
}
void Antoverseer::Age_ants(Entity*** anttable) {
    if (!ants.empty()) {
        for (int i = 0; i < ants.size(); i++) {
            //std::cout << static_cast<Ant*>(ants[i])->TTL;
            static_cast<Ant*>(ants[i])->down();
            
            if (static_cast<Ant*>(ants[i])->TTL == 0) {
                int x = ants[i]->x;
                int y = ants[i]->y;
                static_cast<Ant*>(ants[i])->taboo.clear();
                delete ants[i];
                ants.erase(ants.begin() + i);
                anttable[x][y] = nullptr;
                Ant::Ant_amount--;
            }
        }
    }
}
bool Antoverseer::move_ant(Entity*** anttable, Sim_field antsize,int antnumber,Cord target) {
    anttable[target.x][target.y] = ants[antnumber];
    return true;
}
bool Antoverseer::live(Entity*** anttable, Sim_field antsize, Pheromone*** pherotable, Sim_field pherosize,int &pheromoneleft,int &TTL,int &uncertainty,int &food_distance,int &hole_distance) {
    std::uniform_int_distribution<> distrib1(0, 7);
    
    
    for (int i = 0; i < ants.size(); i++) {
        bool move = false;
        
        int pheromonetoleft = pheromoneleft;
        //mrówka szuka po¿ywienia
        if (static_cast<Ant*>(ants[i])->current_state == looking) {
            ants[i]->taboo.push_back( Cord(ants[i]->x, ants[i]->y));
            
            //zapamiêtuje gdzie chodzi³a
            //std::cout << "hellop";
            static_cast<Ant*>(ants[i])->movelist.push_back(Cord(ants[i]->x, ants[i]->y));
            Cord temp = static_cast<Ant*>(ants[i])->Look_for_food(anttable, antsize,food_distance);
            if (temp.x != -1) {
                static_cast<Ant*>(ants[i])->move_towards(anttable, antsize, temp);
                move = true;
                //sprawdzamy odleg³oœæ od jedzenia i podejmujemy decyzje
                if (sqrt(pow((ants[i]->x - temp.x), 2) + pow((ants[i]->y - temp.y), 2)) < 1.5) {
                    ants[i]->Set_color(anttable[temp.x][temp.y]->Get_color());
                    //std::cout << "om nom";
                    if (!static_cast<Food*>(anttable[temp.x][temp.y])->down()) {                        
                        delete anttable[temp.x][temp.y];
                        anttable[temp.x][temp.y] = nullptr;
                    }
                    //mrówka teraz wraca, odwracamy wektor w którym trzyma poprzednie ruchy i zmieniamy stan na returning
                    std::reverse(static_cast<Ant*>(ants[i])->movelist.begin(), static_cast<Ant*>(ants[i])->movelist.end());
                    static_cast<Ant*>(ants[i])->taboo.clear();
                    static_cast<Ant*>(ants[i])->current_state = returning;
                    static_cast<Ant*>(ants[i])->pheromone_power = pheromonetoleft / static_cast<Ant*>(ants[i])->movelist.size();
                    static_cast<Ant*>(ants[i])->TTL = TTL;
                }
            }
            //mo¿e rusza siê za feromonem
            if (static_cast<Ant*>(ants[i])->move_towards_pheromone(anttable, antsize, pherotable, pherosize,uncertainty)) {
                move = true;
                //std::cout << "feromon";
            }
            //ruszanie siê losowo
            if (move == false) {
                if (!static_cast<Ant*>(ants[i])->rand_mov(anttable, antsize)) {
                    //int x = ants[i]->x;
                    //int y = ants[i]->y;
                    //delete ants[i];
                    //ants.erase(ants.begin() + i);
                    //anttable[x][y] = nullptr;
                    //continue;
                }
            }
        }
        //mrówka wraca z po¿ywieniem
        if (static_cast<Ant*>(ants[i])->current_state == returning) {
            add_pheromone(pherotable, ants[i]->x, ants[i]->y, static_cast<Ant*>(ants[i])->pheromone_power);
            Cord temp=static_cast<Ant*>(ants[i])->Look_for_hole(anttable, antsize,hole_distance);
            if (temp.x != -1) {
                if (sqrt(pow((ants[i]->x - temp.x), 2) + pow((ants[i]->y - temp.y), 2)) < 1.5) {
                    //Mrówka oddaje jedzenie
                    static_cast<AntHole*>(hole)->up();
                    ants[i]->Set_color(sf::Color::Black);
                    static_cast<Ant*>(ants[i])->current_state =looking;
                    static_cast<Ant*>(ants[i])->TTL = TTL;
                    static_cast<Ant*>(ants[i])->movelist.clear();
                    //losujemy kierunek
                    int chosen1 = distrib1(gen);
                    static_cast<Ant*>(ants[i])->direction = static_cast<Direction>(chosen1);
                    //std::cout << "delivered";
                }
                static_cast<Ant*>(ants[i])->move_towards(anttable, antsize, temp);
                move = true;
            }
            if (!static_cast<Ant*>(ants[i])->movelist.empty() and move!=true) {
                static_cast<Ant*>(ants[i])->move(anttable,static_cast<Ant*>(ants[i])->movelist[0].x, static_cast<Ant*>(ants[i])->movelist[0].y);
                static_cast<Ant*>(ants[i])->movelist.erase(static_cast<Ant*>(ants[i])->movelist.begin() + 0);
                move_ant(anttable, antsize, i, Cord(ants[i]->x, ants[i]->y));
            }
            move_ant(anttable, antsize, i, Cord(ants[i]->x, ants[i]->y));
            //std::cout << i;
        }
        
    }
    Entity* buff = nullptr;
    buff = static_cast<AntHole*>(hole)->produce_ant(anttable,antsize,TTL);
    if (buff) {
        add_ant(buff);
    }
    std::sort(ants.begin(), ants.end());
    if (!ants.empty()) {
        for (int i = 0; i < ants.size() - 1; i++) {
            move_ant(anttable, antsize, i, Cord(ants[i]->x, ants[i]->y));
        }
    }
    return 1;
}