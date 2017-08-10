#include "loopclass.h"

LoopClass::LoopClass()
{
    counter = 0;
    std::cout << "loop class created" << std::endl;
}

LoopClass::~LoopClass()
{

}

void LoopClass::process()
{
    cout << "process begin" << endl;
    while(1){
        counter++;
        if (counter == 10000000)
        {
            counter = 0;
            emit gogo();
        }
    }
}

