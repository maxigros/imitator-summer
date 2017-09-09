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
    void update(double world_time_delta);
};

#endif // TARGETCONSTSPEED_H
