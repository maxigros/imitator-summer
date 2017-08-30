#ifndef TARGETCONSTSPEED_H
#define TARGETCONSTSPEED_H

#include "targetgeneral.h"
#include "../../common/config_storage/storage.h"

class TargetConstSpeed : public TargetGeneral
{
    Q_OBJECT
public:
    TargetConstSpeed();
    ~TargetConstSpeed();
protected:
    void update();
};

#endif // TARGETCONSTSPEED_H
