#include "boxgenerate.h"

BoxGenerate::BoxGenerate(QString configFilename, QObject *parent) : QObject(parent)
{
    cout << "moduleGenerate created with file: " << configFilename.toStdString() << endl;
}

BoxGenerate::~BoxGenerate()
{
    cout << "moduleGenerate deleting" << endl;
}

void BoxGenerate::stop()
{
    cout << "moduleGenerate stopping" << endl;
    toStop = true;
    emit finish();
}

void BoxGenerate::process()
{
    cout << "moduleGenerate processing" << endl;
    int c = 0;
    while(!toStop)
    {
        c++;
    }
}
