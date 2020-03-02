#include <iostream>
#include "Game.h"
#include "util/Util.h"


int main() {
    // Log::RealLog("啦啦啦:%s;%d%;%s;%f");
    LogUtil::LogInfo("啦啦啦:%s;%d;%s;%f", "111aaaa", 20, "嘎嘎嘎", 1.23);
    LogUtil::LogWarning("啦啦啦:%s;%d;%s;%f", "111aaaa", 20, "嘎嘎嘎", 1.23);
    LogUtil::LogError("啦啦啦:%s;%d;%s;%f", "111aaaa", 20, "嘎嘎嘎", 1.23);
    Game *game = new Game();
    game->start();
    system("pause");
    return 0;
}