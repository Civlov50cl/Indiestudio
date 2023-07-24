#include <iostream>
#include <fstream>
#include <string>
#include "../lib/bombermanbombs.hpp"

player placecharacter(player myplayer, float y, Model model, ModelAnimation *anims, int a)
{
    // Load the animated model mesh and basic data
    //Texture2D texture = LoadTexture("resources/models/iqm/guytex.png"); // Load model texture and set material
    //SetMaterialTexture(&model.materials[0], MATERIAL_MAP_DIFFUSE, texture); // Set model material map texture
    if (myplayer.getdeath() == 1)
        return myplayer;
    Vector3 position = { myplayer.gety(), y, myplayer.getx() }; // Set model position
    // Load animation data
    if (myplayer.getwalking() != 0){
        myplayer.setframecounter(myplayer.getframecounter() + 1);
        if (myplayer.getframecounter() >= anims[0].frameCount) 
            myplayer.setframecounter(0);
    }
    UpdateModelAnimation(model, anims[0], myplayer.getframecounter());
    if (myplayer.getrotation() == 0)
        model.transform = MatrixRotateXYZ({-80.0f, 0.0f, 0.0f});
    if (myplayer.getrotation() == 1)
        model.transform = MatrixRotateXYZ({-80.0f, 90.0f, 0.0f});
    if (myplayer.getrotation() == 2)
        model.transform = MatrixRotateXYZ({-80.0f, -180.0f, 0.0f});
    if (myplayer.getrotation() == 3)
        model.transform = MatrixRotateXYZ({-80.0f, -90.0f, 0.0f});
    Color colors[4] = {WHITE, PINK, BLUE, GREEN};
    DrawModel(model, position, 300, colors[a]);
    return myplayer;
}

std::vector<std::string> createMapArray(std::string map)
{
    int j = 0;
    int k = 0;
    std::vector<std::string> mapArray;
    std::string line;
    
    for (int i = 0; map[i] != '\0'; i++, k++) {
        if (map[i] == '\n') {
            line = map.substr(j, k);
            mapArray.push_back(line);
            k = -1;
            j = i + 1;
        }
    }
    mapArray.push_back("\0");

    return mapArray;
}

void maptodisp(std::vector<std::string> map, Model bush, Texture2D boitemagique, Texture2D grass)
{
    float sizeratio = 50;
    //DrawCubeTexture()
    for (float i = 0; i < 20; i++){
        for (float j = 0; j < 20; j++){
            DrawCubeTexture(grass, {(-1000 + (i * 400)), 0, (-1000 + (j*400))}, 400, 1, 400, WHITE);
        }
    }
    //DrawCubeTexture(grass, {2000 , 0, 0}, 4000, 1, 4000, WHITE);
    for (int n = 0; map[n][0] != 0; ++n) {
        for (int k = 0; map[n][k] != '\0'; ++k) {
            switch (map[n][k]) {
                case 'X' :
                    DrawModel(bush, {n*sizeratio , 35, k*sizeratio + 12}, 30, WHITE);
                    //DrawCube({n*sizeratio , 1, k*sizeratio}, sizeratio, sizeratio*2, sizeratio, BLUE); // destroyable wall
                    DrawCubeTexture(grass, {n*sizeratio , 1, k*sizeratio}, sizeratio, sizeratio, sizeratio, WHITE);
                    //DrawCube({n*sizeratio , 1, k*sizeratio}, sizeratio, sizeratio, sizeratio, RED);
                    break;
                case 'O' : 
                    DrawCubeTexture(grass, {n*sizeratio , 1, k*sizeratio}, sizeratio, sizeratio, sizeratio, WHITE);
                    //DrawCube({n*sizeratio , 1, k*sizeratio}, sizeratio, sizeratio, sizeratio, RED); // floor
                    break;
                case 'M' : 
                    //DrawModel(boite, {n*sizeratio , 35, k*sizeratio + 12}, 30, WHITE);
                    DrawCubeTexture(boitemagique, {n*sizeratio , 1, k*sizeratio}, sizeratio, sizeratio*2, sizeratio, WHITE);
                    //DrawCube({n*sizeratio , 1, k*sizeratio}, sizeratio, sizeratio*2, sizeratio, BLACK); //wall
                    break;
                case 'P' :
                    DrawCubeTexture(grass, {n*sizeratio , 1, k*sizeratio}, sizeratio, sizeratio, sizeratio, WHITE);
                    //DrawCube({n*sizeratio , 1, k*sizeratio}, sizeratio, sizeratio, sizeratio, RED); // floor
                    break;

            }
        }
    }
}

void bombtodisp(std::list<bomb> bomblist, std::list<explosion> explist, std::list<powerup> powerlist, Model fireup, Model speedup, Model bombup, Model ghost, Model spike, Model shroom)
{
    float sizeratio = 50;
    std::list<bomb>::iterator it = bomblist.begin();
    for (int i = 0; i < bomblist.size(); i++){
        //DrawCube({it->gety() * sizeratio, sizeratio, it->getx() * sizeratio}, sizeratio, sizeratio, sizeratio, GREEN);
        DrawModel(shroom, {it->gety() * sizeratio, sizeratio, it->getx() * sizeratio}, 10, WHITE);
        //à remplacer par modèle de bombe
        it++;
    }
    std::list<explosion>::iterator newit = explist.begin();
    for (int i = 0; i < explist.size(); i++){
        DrawCube({newit->gety() * sizeratio, sizeratio, newit->getx() * sizeratio}, sizeratio, sizeratio, sizeratio, ORANGE);
        //à remplacer par modèle d'explosion
        newit++;
    }
    std::list<powerup>::iterator powit = powerlist.begin();
    for (int i = 0; i < powerlist.size(); i++){
        if (powit->getpower() == 1){
            DrawModel(fireup, {powit->gety() * sizeratio, sizeratio, powit->getx() * sizeratio}, 10, WHITE);
        }
        else if (powit->getpower() == 2){
            DrawModel(speedup, {powit->gety() * sizeratio, sizeratio, powit->getx() * sizeratio}, 10, WHITE);
        }
        else if (powit->getpower() == 3){
            DrawModel(ghost, {powit->gety() * sizeratio, sizeratio, powit->getx() * sizeratio}, 10, WHITE);
        }
        else if (powit->getpower() == 4){
            DrawModel(spike, {powit->gety() * sizeratio, sizeratio, powit->getx() * sizeratio}, 10, WHITE);
        }
        else
            DrawModel(bombup, {powit->gety() * sizeratio, sizeratio, powit->getx() * sizeratio}, 10, WHITE);
        //à remplacer par modèle d'explosion
        powit++;
    }
}

int *allocatekeys(int keya, int keyb, int keyc, int keyd, int keye)
{
    int *keys = new int[5];
    keys[0] = keya;
    keys[1] = keyb;
    keys[3] = keyc;
    keys[2] = keyd;
    keys[4] = keye;
    return keys;
}

player getnewplayer(int y, int x, int sizecase, int *keys)
{
    player newplayer((x * sizecase), (y * sizecase), sizecase, keys);
    return newplayer;
}

player playermovement(player myplayer, std::vector<std::string> map, std::list<bomb> *mybomblist)
{
    int *playerkey = myplayer.getkeys();
    if (myplayer.getdeath() != 0)
        return myplayer;
    if (IsKeyDown(playerkey[0]))
        myplayer.godown(map);
    else if (IsKeyDown(playerkey[1]))
        myplayer.goleft(map);
    else if (IsKeyDown(playerkey[2]))
        myplayer.goup(map);
    else if (IsKeyDown(playerkey[3]))
        myplayer.goright(map);
    else if (IsKeyPressed(playerkey[4])){
        *mybomblist = myplayer.putbomb(*mybomblist);
    }
    else
        myplayer.resetwalking();
    return myplayer;
}

player aimovement(player myplayer, std::vector<std::string> map, std::list<bomb> *mybomblist)
{
    
    int x = (myplayer.getx() + 11) /50;
    int y = (myplayer.gety() + 11) /50;
    int *playerkey = myplayer.getkeys();
    if (myplayer.getdeath() != 0)
        return myplayer;
    if (map[y][x+1] != 'X' && map[y][x+1] != 'M')
        myplayer.goright(map);
    else{
        *mybomblist = myplayer.putbomb(*mybomblist);
        myplayer.resetwalking();
    }
    return myplayer;
}

std::list<player> playercreate(std::vector<std::string> map, int sizecase)
{
    std::list<player> result;
    int *keys;
    int index = 0;
    for (int i = 0; map[i][0] != 0; i ++){
        for (int j = 0; map[i][j] != 0; j++){
            if (map[i][j] == 'P'){
                if (index == 0)
                    keys = allocatekeys(KEY_W, KEY_A, KEY_D, KEY_S, KEY_Q);
                else if (index == 1)
                    keys = allocatekeys(KEY_T, KEY_F, KEY_H, KEY_G, KEY_R);
                else if (index == 2)
                    keys = allocatekeys(KEY_I, KEY_J, KEY_L, KEY_K, KEY_U);
                else if (index == 3)
                    keys = allocatekeys(KEY_Z, KEY_X, KEY_V, KEY_C, KEY_B);
                index += 1;
                result.push_back(getnewplayer(i, j, sizecase, keys));

            }
        }
    }
    return result;
}

std::list<bomb> bombexplode(std::list<bomb> bomblist, std::list<explosion> *explist, Sound boomsound)
{

    std::list<bomb>::iterator it = bomblist.begin();

    int finish = (*explist).size();
    for (int i = 0; i < bomblist.size(); i++){
        it->tic(explist, boomsound);
        it++;
    }
    int a = bomblist.size();
    if (a != 0){
        bomblist = removeexploded(bomblist);
    }
    return bomblist;
}

void writetofile(std::list<player> playerlist, std::vector<std::string> map, int numplayers)
{
    std::ofstream ofs;
    ofs.open("save.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    std::ofstream out;
    out.open("save.txt", std::ios::app);
    for (int n = 0; map[n][0] != 0; ++n) {
        out << map[n] << "\n";
    }
    out.close();
    std::list<player>::iterator it = playerlist.begin();
    for (int i = 0; i < 4; i++){
        it->writesave("save.txt");
        it++;
    }
    out.open("save.txt", std::ios::app);
    out << numplayers << "\n";
    out.close();

}


void dispwinscreen(int a)
{
    Sound mysound = LoadSound("../winscreensound.wav");
    // model.materials[4].maps[MATERIAL_MAP_DIFFUSE].texture = blabla;
    PlaySound(mysound);

    Image parrots = LoadImage("../winscreen.png"); // Load image in CPU memory (RAM)

    // TTF Font loading with custom generation parameters
    Font font = LoadFontEx("resources/KAISG.ttf", 100, 0, 0);

    Texture2D texture = LoadTextureFromImage(parrots);
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    int end = 0;
    int choice = 1;
    char *choices[5] = {"draw, everybody died","player 1 won", "player 2 won", "player 3 won", "player 4 won"};
    while (end == 0 && (!WindowShouldClose())){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2 - 40, WHITE);
        DrawRectangleLines(screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2 - 40, texture.width, texture.height, DARKGRAY);
        if(IsKeyPressed(KEY_G))
            end = 1;
        DrawText(choices[a], 800, 800, 50, BLACK);
        DrawText("Press G to go back", 800, 900, 25, BLACK);
        EndDrawing();
    }
    if (end == 0){
        CloseWindow();
        exit(0);
    }
    UnloadSound(mysound);
    UnloadTexture(texture);
}

// est lancé lorsque une partie est en cours
void ingame(std::vector<std::string> map, std::list<player> playerlist, int numplayers)
{
    int end = 0;
    
    Model fireup = LoadModel("../powerup_range.obj");
    Model speedup = LoadModel("../powerup_speed.obj");
    Model bombup = LoadModel("../powerup_more.obj");
    Model ghost = LoadModel("../powerup_ghost.obj");
    Model spike = LoadModel("../powerup_spike.obj");
    Model model = LoadModel("../wiz.iqm");
    Model shroom = LoadModel("../trueshroom.obj");
    //Model boite = LoadModel("../Magic_box_low.obj");
    Model bush = LoadModel("../uploads_files_3387574_bush.obj");
    Texture2D grass = LoadTexture("../mygrass.png");
    unsigned int animsCount = 0;
    Texture2D boitemagique = LoadTexture("../boitemagique1.png");
    //boite.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = boitemagique;
    //fireup.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture = fire;
    //fireup.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = obsidian;
    ModelAnimation *anims = LoadModelAnimations("../wizanim.iqm", &animsCount);
    // Texture2D blabla = LoadTexture("cloth.png");
    Sound deathsound = LoadSound("../yoda_death.wav");
    Sound boomsound = LoadSound("../booom.wav");
    // model.materials[4].maps[MATERIAL_MAP_DIFFUSE].texture = blabla;
    int bombreload = 0;
    Camera camera = { 0 };
    Music music = LoadMusicStream("../gameplay1.wav");
    camera.position = (Vector3){ -50.0f, 450.0f, 500.0f }; // Camera position//(25, 800, 400)
    camera.target = (Vector3){ 100.0f, 150.0f, 500.0f }; // Camera looking at point (50, 550, 400)
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Camera up vector (rotation towards target)
    camera.fovy = 75.0f; // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE; // Camera mode type
    SetCameraMode(camera, CAMERA_FREE); // Set free camera mode
    //std::list<player> players = playercreate(map, 60);
    int *keys = allocatekeys(KEY_W, KEY_A, KEY_D, KEY_S, KEY_Q);
    player myplayer(50, 50, 50, keys);
    //std::list<player> playerlist = playercreate(map, 50);
    std::list<bomb> bomblist;
    std::list<explosion> explist;
    std::list<powerup> powerlist;
    PlayMusicStream(music);
    float timePlayed = 0.0f;
    while (!WindowShouldClose() && end == 0)
    {
        UpdateMusicStream(music);
        UpdateCamera(&camera);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        //DrawText("welcome in the game", 190, 200, 50, BLUE);
        if (IsKeyPressed(KEY_N))
            end = 1;
        BeginMode3D(camera);
        maptodisp(map, bush, boitemagique, grass);
        //DrawGrid(10, 1.0f);
        bombreload += 1;
        std::list<player>::iterator it = playerlist.begin();
        std::list<explosion>::iterator expit = explist.begin();
        for (int i = 0; i < playerlist.size(); i++){
            if (i < numplayers){
                *it = playermovement(*it, map, &bomblist);
            }
            else{
                *it = aimovement(*it, map, &bomblist);
            }
            if (bombreload > 300){
                it->regenbomb();
            }
            *it = placecharacter(*it, 0, model, anims, i);
            powerlist = removeused(powerlist, &(*it));
            bomblist = bombexplode(bomblist, &explist, boomsound);
            it++;
        }
        if (bombreload > 400)
            bombreload = 0;
        int finish = explist.size();
        for (int i = 0; i < finish; i++){
            expit->tic(&map, &playerlist, &explist, deathsound);
            expit++;
        }
        explist = removetimedout(explist, &map, &powerlist);
        bombtodisp(bomblist, explist, powerlist, fireup, speedup, bombup, ghost, spike, shroom);
        EndMode3D();
        EndDrawing();
        if (getalive(playerlist) < 2) {
            end = 1;
            int a = getwinner(playerlist);
            dispwinscreen(a);
        }
        timePlayed = GetMusicTimePlayed(music)/GetMusicTimeLength(music)*400;

        if (timePlayed > 400) {
            StopMusicStream(music);
            PlayMusicStream(music);
        }
        //displaymap(map);
    }
    StopMusicStream(music);
    if (end == 0){
        CloseWindow();
        writetofile(playerlist, map, numplayers);
        exit(0);
    }
}

int count(std::string string, char tocount)
{
    int result = 0;
    for (int i = 0; string[i] != 0; i++){
        if (string[i] == tocount)
            result += 1;
    }
    return result;
}

int *stringtoints(std::string mystring)
{
    int counted = count(mystring, ';') + 1;
    int *result = new int[counted];
    int i = 0;
    std::string word = "";
    for (auto x : mystring){
        if (x == ';')
        {
            result[i] = stoi(word);
            word = "";
            i += 1;
        }
        else {
            word = word + x;
        }
    }
    result[i] = stoi(word);
    return result;
}

int loadgame()
{
    std::ifstream filemap ("save.txt");
    std::string mapstr;
    if (filemap.is_open()){
        std::getline(filemap, mapstr, '\0');
    }
    else{
        return 84;
    }
    std::list<player> playerlist;
    std::vector<std::string> truemap;
    std::vector<std::string> map = createMapArray(mapstr);
    for (int i = 0; i < 11; i++){
        truemap.push_back(map[i]);
    }
    truemap.push_back("\0");
    for (int i = 0; i < 4; i++){
        player newplayer(stringtoints(map[i+11]));
        playerlist.push_back(newplayer);
    }
    ingame(truemap, playerlist, stoi(map[15]));
    return 0;
}

std::vector<std::string> createrandommap(std::string mapstr)
{
    int a;
    std::vector<std::string> map = createMapArray(mapstr);
    for (int i = 1; i < 10; i++){
        for (int j = 1; j < 20; j++){
            if (((i > 2 && i < 8) || (j > 2 && j < 18)) || ((i == 2 || i == 8) && (j == 2 || j == 18))){
                a = rand() %5;
                if (a > 3){
                    map[i][j] = 'M';
                }
                else if (a > 2){
                    map[i][j] = 'O';
                }
                else{
                    map[i][j] = 'X';
                }
            }
        }
    }
    return map;
}

int choosenumplayer(Texture2D texture)
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    int end = 0;
    int choice = 1;
    char *choices[4] = {"players: 1", "players: 2", "players: 3", "players: 4"};
    while (end == 0 && (!WindowShouldClose())){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2 - 40, WHITE);
        DrawRectangleLines(screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2 - 40, texture.width, texture.height, DARKGRAY);
        if(IsKeyPressed(KEY_G))
            end = 1;
        if(IsKeyPressed(KEY_K)){
            if (choice == 1)
                choice = 4;
            else
                choice -= 1;
        }
        if(IsKeyPressed(KEY_L)){
            if (choice == 4)
                choice = 1;
            else
                choice += 1;
        }
        DrawText(choices[choice - 1], 100, 500, 50, BLACK);
        DrawText("Press K or L key to select your choice", 10, 400, 25, BLACK);
        DrawText("Press G key to play", 550, 400, 25, BLACK);
        EndDrawing();
    }
    if (end == 0){
        CloseWindow();
        exit(0);
    }
    return choice;
}

int main(int ac, char **av)
{
    int choice = 0;
    srand (time(NULL));
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    std::ifstream filemap ("../mapbomberman.txt");
    
    InitWindow(screenWidth, screenHeight, "BOOMBER BOOM BOOM");
    Image parrots = LoadImage("../test.png"); // Load image in CPU memory (RAM)

    // TTF Font loading with custom generation parameters
    Font font = LoadFontEx("resources/KAISG.ttf", 100, 0, 0);

    Texture2D texture = LoadTextureFromImage(parrots);  // Image converted to texture, uploaded to GPU memory (VRAM)
    UnloadImage(parrots);
    Vector2 position = { (float)(screenWidth/2 - texture.width/2), (float)(screenHeight/2 - texture.height/2 - 20) };

    bool showFont = false;
    InitAudioDevice();
    Music music = LoadMusicStream("../menu3.wav");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    PlayMusicStream(music);
    float timePlayed = 0.0f;
    std::string mapstr;
    if (filemap.is_open()){
        std::getline(filemap, mapstr, '\0');
    }
    else{
        return 84;
    }

    std::vector<std::string> map = createMapArray(mapstr);
    char *choices[4] = {"classic mode", " Load Game", "random mode", "    EXIT"};

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateMusicStream(music);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2 - 40, WHITE);
        DrawRectangleLines(screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2 - 40, texture.width, texture.height, DARKGRAY);
        
        if(IsKeyPressed(KEY_K)){
            if (choice == 0)
                choice = 3;
            else
                choice -= 1;
        }
        if(IsKeyPressed(KEY_L)){
            if (choice == 3)
                choice = 0;
            else
                choice += 1;
        }

        for (int i = 0; i < 4; i++) {
            DrawText(choices[i], 350, (i + 1) * 95, 45, BLACK);
            if (i == choice) {
                DrawText(choices[i], 350, (i + 1) * 95, 45, RED);
            }
        }

        DrawText("Press K or L key to select your choice", 10, 600, 25, BLACK);
        DrawText("Press E key to play", 550, 600, 25, BLACK);
        EndDrawing();
        if(IsKeyPressed(KEY_E) && choice == 0){
            StopMusicStream(music);
            ingame(map, playercreate(map, 50), choosenumplayer(texture));
            PlayMusicStream(music);
        }
        if(IsKeyPressed(KEY_E) && choice == 1){
            StopMusicStream(music);
            loadgame();
            PlayMusicStream(music);
        }
        if(IsKeyPressed(KEY_E) && choice == 2){
            StopMusicStream(music);
            std::vector<std::string> randommap = createrandommap(mapstr);
            ingame(randommap, playercreate(randommap, 50), choosenumplayer(texture));
            PlayMusicStream(music);
        }
        if(IsKeyPressed(KEY_E) && choice == 3){
            StopMusicStream(music);
            CloseWindow();
            return 0;
        }
        timePlayed = GetMusicTimePlayed(music)/GetMusicTimeLength(music)*400;

        if (timePlayed > 400) {
            StopMusicStream(music);
            PlayMusicStream(music);
        }
        //----------------------------------------------------------------------------------
    }
    CloseWindow();   
    return 0;
}