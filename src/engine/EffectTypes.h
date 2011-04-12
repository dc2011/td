#ifndef TD_EFFECTTYPES_H
#define TD_EFFECTTYPES_H

#include "Unit.h"
#include "Effect.h"

namespace td {

class NPCPlayerEffect : public Effect {
    Q_OBJECT

public:
    explicit NPCPlayerEffect(Unit* unit);
    virtual ~NPCPlayerEffect();
    void apply();
};

class ArrowEffect : public Effect {
    Q_OBJECT

public:
    explicit ArrowEffect(Unit* unit);
    virtual ~ArrowEffect() {}
    void apply();
};
/**
* an effect that modifies a player's movement speed
* if they are on a bad type of terrain..
*
* @author Duncan Donaldson
* @author Luke Queenan
*/
class PlayerTerrainSlowEffect : public Effect {
    Q_OBJECT

public:
    explicit PlayerTerrainSlowEffect(Unit* unit);
    virtual ~PlayerTerrainSlowEffect();
    /**
     * applies the player slowdown effect.
     *
     * @author Duncan Donaldson
     * @author Luke Queenan
     */
    void apply();
};
/**
* an effect that modifies a player's movement speed
* if they are on a good type of terrain..
*
* @author Duncan Donaldson
*/
class PlayerTerrainFastEffect : public Effect {
    Q_OBJECT

public:
    explicit PlayerTerrainFastEffect(Unit* unit);
    virtual ~PlayerTerrainFastEffect();
    /**
     * applies the player slowdown effect.
     *
     * @author Duncan Donaldson
     * @author Luke Queenan
     */
    void apply();
};
/**
* an effect that does initial damage to an NPC
* then slows the NPC for a period of time
*
* @author Duncan Donaldson
*/
class NPCTarEffect : public Effect {
    Q_OBJECT

public:
    explicit NPCTarEffect(Unit* unit);
    virtual ~NPCTarEffect();
    /**
     * applies the tar slowdown effect.
     *
     * @author Duncan Donaldson
     */
    void apply();
};
/**
* an effect that deals damage over time to an NPC.
*
* @author Duncan Donaldson
*/
class NPCBurnEffect : public Effect {
    Q_OBJECT

public:
    explicit NPCBurnEffect(Unit* unit);
    virtual ~NPCBurnEffect(){}
    /**
     * applies the burn effect.
     *
     * @author Duncan Donaldson
     */
    void apply();
};

} /* end namespace td */

#endif
