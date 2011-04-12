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

class CannonEffect : public Effect {
    Q_OBJECT

public:
    explicit CannonEffect(Unit* unit);
    virtual ~CannonEffect() {}

    void apply();
};

class FlakEffect : public Effect {
    Q_OBJECT

public:
    explicit FlakEffect(Unit* unit);
    virtual ~FlakEffect() {}

    void apply();
};

class PlayerTerrainEffect : public Effect {
    Q_OBJECT

public:
    explicit PlayerTerrainEffect(Unit* unit);
    virtual ~PlayerTerrainEffect() {}

    void apply();
};

class NPCTarEffect : public Effect {
    Q_OBJECT

public:
    explicit NPCTarEffect(Unit* unit);
    virtual ~NPCTarEffect(){}

    void apply();
};

class FireEffect : public Effect {
    Q_OBJECT

public:
    explicit FireEffect(Unit* unit);
    virtual ~FireEffect(){}

    void apply();
};

class BurningEffect : public Effect {
    Q_OBJECT

public:
    explicit BurningEffect(Unit* unit);
    virtual ~BurningEffect(){}

    void apply();
};

} /* end namespace td */

#endif
