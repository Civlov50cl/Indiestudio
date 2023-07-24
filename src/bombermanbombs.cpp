#include "../lib/bombermanbombs.hpp"

void addxy(int *x, int *y, int direction)
{
    if (direction == 0)
        *x -= 1;
    if (direction == 1)
        *x += 1;
    if (direction == 2)
        *y -= 1;
    if (direction == 3)
        *y += 1;
}


explosion::explosion(int x, int y, int power, int direction, int powerup)
{
    _x = x;
    _y = y;
    _power = power;
    _direction = direction;
    _powerup = powerup;
};

explosion::~explosion()
{

};

int getalive(std::list <player> playerlist)
{
    int result = 0;
    std::list<player>::iterator it = (playerlist).begin();
    for (size_t i = 0; i < (playerlist).size(); i++){
        if (it->getdeath() == 0){
            result += 1;
        }
        it++;
    }
    return result;  
}

int getwinner(std::list <player> playerlist)
{
    int result = 1;
    std::list<player>::iterator it = (playerlist).begin();
    for (size_t i = 0; i < (playerlist).size(); i++){
        if (it->getdeath() == 0){
            return result;
        }
        result ++;
        it++;
    }
    return 0;  
}

void explosion::tic(std::vector<std::string> *mymap, std::list<player> *myplayers, std::list<explosion> *explosions, Sound deathsound)
{
    int x = _x;
    int y = _y;
    std::vector<std::string> map = *mymap;
    std::list<player> players = *myplayers;
    std::list<explosion> myexplosions = *explosions;
    if (_timer == 60 && _power > 0){
        if (_direction != 4){
            addxy(&x, &y, _direction);
            if (map[y][x] != 'M'){
                explosion newexplosion(x, y, (_power-1) , _direction, _powerup);
                (*explosions).push_back(newexplosion);
            }
        }
        else{
            if (map[y][x-1] != 'M'){
            explosion newexplosiona(x-1, y, (_power-1) , 0, _powerup);
            (*explosions).push_back(newexplosiona);
            }
            if (map[y][x+1] != 'M'){
            explosion newexplosionb(x+1, y, (_power-1) , 1, _powerup);
            (*explosions).push_back(newexplosionb);
            }
            if (map[y-1][x] != 'M'){
            explosion newexplosionc(x, y-1, (_power-1) , 2, _powerup);
            (*explosions).push_back(newexplosionc);
            }
            if (map[y+1][x] != 'M'){
            explosion newexplosiond(x, y+1, (_power-1) , 3, _powerup);
            (*explosions).push_back(newexplosiond);
            }
        }
    }
    std::list<player>::iterator it = (*myplayers).begin();
    for (size_t i = 0; i < (*myplayers).size(); i++){
        if (((it->getx() + 20) / 50) == _x && ((it->gety()+20)/50)== _y and it->getdeath() == 0){
            it->kill();
            PlaySound(deathsound);
        }
        it++;
    }
    _timer -= 1;
}

int explosion::getx()
{
    return _x;
}

int explosion::gety()
{
    return _y;
}

int explosion::gettimer()
{
    return _timer;
}

int explosion::getpowerup()
{
    return _powerup;
}

bomb::bomb(int x, int y, int power, int powerup)
{
    _x = x;
    _y = y;
    _power = power;
    _powerup = powerup;
}

bomb::~bomb()
{
    //create explosion object at x and y
}

void bomb::tic(std::list<explosion> *explosions, Sound boomsound)
{
    _timer -= 1;
    std::list<explosion>::iterator it = (*explosions).begin();
    int finish = (*explosions).size();
    for (size_t i = 0; i < finish; i++){
        if (it->getx() == _x && it->gety() == _y && _timer != 1)
            _timer = 0;
        it++;
    }
    if (_timer < 1){
        explosion newexplosion(_x, _y, _power , 4, _powerup);
        (*explosions).push_back(newexplosion);
        PlaySound(boomsound);
    }
}

int bomb::getx()
{
    return _x;
}

int bomb::gety()
{
    return _y;
}

int bomb::gettimer()
{
    return _timer;
}

int bomb::getpowerup()
{
    return _powerup;
}

std::list<bomb> removeexploded(std::list<bomb> bomblist)
{
    std::list<bomb>::iterator it = bomblist.begin();
    std::list<bomb>::iterator it2;
    for (size_t i = 0; i < bomblist.size(); i++){
        if (it->gettimer() < 1){
            it2 = it;
            it2++;
            bomblist.erase(it);
            it = it2;
        }
    }
    return bomblist;
}

std::list<powerup> removeused(std::list<powerup> powerlist, player *myplayer)
{
    std::list<powerup>::iterator it = powerlist.begin();
    std::list<powerup>::iterator it2;
    for (size_t i = 0; i < powerlist.size(); i++){
        if ((it->getx() == ((*myplayer).getx() + 20) / 50) && (it->gety() == ((*myplayer).gety() + 20) / 50)) {
            (*myplayer).gotpowerup(it->getpower());
            it2 = it;
            it2++;
            powerlist.erase(it);
            it = it2;
        }
        it++;
    }
    return powerlist;
}

std::list<explosion> removetimedout(std::list<explosion> explosions, std::vector<std::string> *mymap, std::list<powerup> *powerlist)
{
    std::vector<std::string> map = *mymap;
    std::list<explosion>::iterator it = explosions.begin();
    std::list<explosion>::iterator it2;
    int b;
    char a;
    for (size_t i = 0; i < explosions.size(); i++){
        a = map[it->gety()][it->getx()];
        if (it->gettimer() < 1){
            it2 = it;
            it2++;
            explosions.erase(it);
            it = it2;
        }
        else if (a != 'O' && a != 'P'){
            if (it->getpowerup() == 1 && a == 'X'){
            (*mymap)[it->gety()][it->getx()] = 'O';
            b = 0;
            int randnum = rand() %10;
            if (randnum > 8){
                b = 4;
            }
            else if (randnum > 7){
                b = 3;
            }
            else if (randnum > 6){
                b = 2;
            }
            else if (randnum > 4){
                b = 1;
            }
            else if (randnum > 3){
                b = 5;
            }
            if (b != 0){
                powerup newpowerup(b, it->getx(), it->gety());
                (*powerlist).push_back(newpowerup);
            }
            }
            else{
                if (a == 'X'){
                    (*mymap)[it->gety()][it->getx()] = 'O';
                    b = 0;
                    int randnum = rand() %10;
                    if (randnum > 8){
                        b = 4;
                    }
                    else if (randnum > 7){
                        b = 3;
                    }
                    else if (randnum > 6){
                        b = 2;
                    }
                    else if (randnum > 4){
                        b = 1;
                    }
                    else if (randnum > 3){
                        b = 5;
                    }
                    if (b != 0){
                        powerup newpowerup(b, it->getx(), it->gety());
                        (*powerlist).push_back(newpowerup);
                    }
                        
                }
                it2 = it;
                it2++;
                explosions.erase(it);
                it = it2;
            }
        }

        it++;
    }
    return explosions;
}

powerup::powerup(int power, int x, int y)
{
    _power = power;
    _x = x;
    _y = y;
}

powerup::~powerup()
{

}

int powerup::getpower()
{
    return _power;
}

int powerup::getx()
{
    return _x;
}

int powerup::gety()
{
    return _y;
}