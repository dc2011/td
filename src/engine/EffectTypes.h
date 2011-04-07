#ifndef TD_EFFECTTYPES_H
#define TD_EFFECTTYPES_H

#include "Unit.h"
#include "Effect.h"

namespace td {

class NPCPlayerEffect : public Effect {
    Q_OBJECT

public:
    explicit NPCPlayerEffect(Unit* unit);
    virtual ~NPCPlayerEffect() {}

    void apply();
};

class ArrowEffect : public Effect {
    Q_OBJECT

public:
    explicit ArrowEffect(Unit* unit);
    virtual ~ArrowEffect() {}

    void apply();
};

class PlayerTerrain : public Effect {
    Q_OBJECT

public:
    explicit PlayerTerrain(Unit* unit);
    virtual ~PlayerTerrain() {}

    void apply();
};

} /* end namespace td */

#endif
