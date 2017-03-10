#ifndef QUATERNION_H
#define QUATERNION_H

#include "ik/gen/config.h"

C_HEADER_BEGIN

struct quat_t
{
    ik_real w;
    ik_real x;
    ik_real y;
    ik_real z;
};

C_HEADER_END

#endif /* QUATERNION_H */
