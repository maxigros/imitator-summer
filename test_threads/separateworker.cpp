#include "separateworker.h"

SeparateWorker::SeparateWorker()
{
    std::cout << "sep" << std::endl;
    on_off = false;
}

SeparateWorker::~SeparateWorker()
{
    if (loop != NULL)
        delete loop;
}

void SeparateWorker::addThread()
{
    LoopClass *loop = new LoopClass;
    QThread *thread = new QThread;
    loop->moveToThread(thread);
    connect(thread, SIGNAL(started()), loop, SLOT(process()));
}

void SeparateWorker::stopThreads()
{

}

void SeparateWorker::process()
{

}

void SeparateWorker::stop()
{
    loop->on_off = false;
    delete loop;
}
