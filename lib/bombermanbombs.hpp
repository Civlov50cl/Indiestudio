#ifndef __BOMBERMAN__H_
#define __BOMBERMAN__H_
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <cstring>
#include <time.h>
#include <chrono>
#include <thread>
#include <limits.h>
#include <unistd.h>
#include <ctime>
#include <cwchar>
#include <vector>
#include <sys/wait.h>
#include <list>
#include "raylib.h"
#include "raymath.h"


class player;

class explosion{
    public:
        explosion(int x, int y, int power, int direction, int powerup);
        ~explosion();
        int getx();
        int gety();
        int gettimer();
        int getpowerup();
        void tic(std::vector<std::string> *mymap, std::list<player> *myplayers, std::list<explosion> *explosions, Sound deathsound);
    private:
        int _x;
        int _y;
        int _timer = 60;
        int _direction;
        int _power;
        int _powerup;
};

class powerup{
    public:
        powerup(int power, int x, int y);
        ~powerup();
        int getpower();
        int getx();
        int gety();
    private:
        int _x;
        int _y;
        int _power;
};

class bomb{
    public:
        bomb(int x, int y, int power, int powerup);
        ~bomb();
        void tic(std::list<explosion> *explosions, Sound boomsound);
        int getx();
        int gety();
        int gettimer();
        int getpowerup();
    private:
        int _x;
        int _y;
        int _timer = 600;
        int _power;
        int _powerup;
};

class player{
    public:
        player(int x, int y, int sizecase, int *keys);
        player(int *info);
        ~player();
        int getx();
        int gety();
        int getcollx();
        int getcolly();
        int getwalking();
        int getdeath();
        int *getkeys();
        int getwallphase();
        int getframecounter();
        int getrotation();
        Model getmodel();
        void kill();
        void writesave(std::string filename);
        void regenbomb();
        void gotpowerup(int powerup);
        void goleft(std::vector<std::string> map);
        void goright(std::vector<std::string> map);
        void resetwalking();
        void godown(std::vector<std::string> map);
        void goup(std::vector<std::string> map);
        std::list<bomb> putbomb(std::list<bomb> bomblist);
        void setframecounter(int framecounter);
    private:
        int _x;
        int _y;
        int _dead = 0;
        int _speed = 3;
        int _power = 1;
        int _powerupbombspike = 0;
        int _wallphase = 0;
        int _bombmax = 1;
        int _bombs = 1;
        int _sizecase;
        int _walking = 0;
        int _rotation = 0;
        int _framecounter = 0;
        int *_keys;
};

int getalive(std::list <player> playerlist);
int getwinner(std::list <player> playerlist);
std::list<explosion> removetimedout(std::list<explosion> explosions, std::vector<std::string> *mymap, std::list<powerup> *powerlist);
std::list<bomb> removeexploded(std::list<bomb> bomblist);
std::list<powerup> removeused(std::list<powerup> powerlist, player *myplayer);

#endif