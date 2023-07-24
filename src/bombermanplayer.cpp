#include "../lib/bombermanbombs.hpp"

player::player(int x, int y, int sizecase, int *keys)
{
    _x = x;
    _y = y;
    _sizecase = sizecase;
    _keys = keys;
}

player::player(int *info)
{
    _x = info[0];
    _y = info[1];
    _dead = info[2];
    _speed = info[3];
    _power = info[4];
    _powerupbombspike = info[5];
    _wallphase = info[6];
    _bombmax = info[7];
    _bombs = info[8];
    _sizecase = info[9];
    _walking = info[10];
    _rotation = info[11];
    _framecounter = info[12];
    _keys = new int[5];
    for (int i = 0; i < 5; i++){
        _keys[i] = info[i + 13];
    }
}

player::~player()
{

}

void player::setframecounter(int framecounter)
{
    _framecounter = framecounter;
}

int player::getframecounter()
{
    return _framecounter;
}

int player::getx()
{
    return _x;
}

int player::getwallphase()
{
    return _wallphase;
}

int player::gety()
{
    return _y;
}

int player::getdeath()
{
    return _dead;
}

int *player::getkeys()
{
    return _keys;
}

void player::kill()
{
    _dead = 1;
}

void player::goleft(std::vector<std::string> map)
{
    int truex = (_x + 10 - _speed) / _sizecase;
    int truey = (_y + 10) / _sizecase;
    int othertruey = (_y + _sizecase - 10) / _sizecase;
    if ((_wallphase == 1 && map[truey][truex] == 'X') || (truey == othertruey && map[truey][truex] != 'M' && map[truey][truex] != 'X'))
    {
        _x -= _speed;
        _walking = 1;
    }
    else{
        _walking = 0;
    }
    _rotation = 1;
}

void player::goright(std::vector<std::string> map)
{
    int truex = (_x - 10 + _speed + _sizecase) / _sizecase;
    int truey = (_y + 10) / _sizecase;
    int othertruey = (_y + _sizecase - 10) / _sizecase;
    if ((_wallphase == 1 && map[truey][truex] == 'X') || (truey == othertruey && map[truey][truex] != 'M' && map[truey][truex] != 'X'))
    {
        _x += _speed;
        _walking = 1;
    }
    else{
        _walking = 0;
    }
    _rotation = 3;
}

void player::godown(std::vector<std::string> map)
{
    int truey = (_y - 10 + _speed + _sizecase) / _sizecase;
    int truex = (_x + 10) / _sizecase;
    int othertruex = (_x + _sizecase - 10) / _sizecase;
    if ((_wallphase == 1 && map[truey][truex] == 'X') || (truex == othertruex && map[truey][truex] != 'M' && map[truey][truex] != 'X'))
    {
        _y += _speed;
        _walking = 1;
    }
    else{
        _walking = 0;
    }
    _rotation = 0;
}

void player::gotpowerup(int powerup)
{
    if (powerup == 1){
        _power += 1;
    }
    if (powerup == 2 && _speed < 6){
        _speed += 1;
    }
    if (powerup == 3){
        _wallphase = 1;
    }
    if (powerup == 4){
        _powerupbombspike = 1;
    }
    if (powerup == 5){
        _bombmax += 1;
        _bombs += 1;
    }
}

void player::goup(std::vector<std::string> map)
{
    int truey = (_y + 10 - _speed) / _sizecase;
    int truex = (_x + 10) / _sizecase;
    int othertruex = (_x + _sizecase - 10) / _sizecase;
    if ((_wallphase == 1 && map[truey][truex] == 'X') || (truex == othertruex && map[truey][truex] != 'M' && map[truey][truex] != 'X'))
    {
        _y -= _speed;
        _walking = 1;
    }
    else{
        _walking = 0;
    }
    _rotation = 2;
}

void player::resetwalking()
{
    _walking = 0;
}

int player::getwalking()
{
    return _walking;
}

int player::getrotation()
{
    return _rotation;
}

void player::regenbomb()
{
    if (_bombs < _bombmax){
        _bombs += 1;
    }
}

std::list<bomb> player::putbomb(std::list<bomb> bomblist)
{   
    int x = _x / _sizecase;
    if (_x % _sizecase > _sizecase - 20)
        x += 1;
    int y = _y / _sizecase;
    if (_y % _sizecase > _sizecase - 20)
        y += 1;
    std::list<bomb>::iterator it = bomblist.begin();
    for (int i = 0; i < bomblist.size(); i++){
        if (it->getx() == x && it->gety() == y){
            return bomblist;
        }
        it++;
    }

    if (_bombs > 0){
        _bombs -= 1;
        bomb newbomb(x, y, _power, _powerupbombspike);
        bomblist.push_back(newbomb);
    }
    return bomblist;
}

int player::getcollx()
{
    return (_x + (_sizecase/2) / _sizecase);
}

int player::getcolly()
{
    return (_y + (_sizecase/2) / _sizecase);
}

void player::writesave(std::string filename)
{
    std::ofstream out;
    out.open("save.txt", std::ios::app);
    out << _x << ";";
    out << _y << ";";
    out << _dead << ";";
    out << _speed << ";";
    out << _power << ";";
    out << _powerupbombspike << ";";
    out << _wallphase << ";";
    out << _bombmax << ";";
    out << _bombs << ";";
    out << _sizecase << ";";
    out << _walking << ";";
    out << _rotation << ";";
    out << _framecounter << ";";
    for (int i = 0; i < 4; i++)
        out << _keys[i] << ";";
    out << _keys[4] << "\n";
    out.close();
}