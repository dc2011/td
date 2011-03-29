#ifndef TD_EFFECTTYPES_H
#define TD_EFFECTTYPES_H

#include "Unit.h"
#include "Effect.h"

namespace td {

class NPCPlayerEffect : public Effect {
    Q_OBJECT

public:
    NPCPlayerEffect(Unit* unit);
    virtual ~NPCPlayerEffect() {}

    void apply();
};

} /* end namespace td */

#endif
