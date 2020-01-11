#include <iostream>
#include "Game.h"

using namespace std;


int main() {
    cout << "程序开始！！！" << endl;
    Game game = Game::Create();
    game.start();
    return 0;
}