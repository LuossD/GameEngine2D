
#include "MainGame.h"

//SDL2会自动替换带args的main函数,所以这里的main函数必须带参数且必须带返回值
int main(int argc, char** argv)
{
    MainGame mainGame(1024,768);
    mainGame.run();
    system("pause");
    return 0;
}

