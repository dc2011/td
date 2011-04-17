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
    virtual void apply();
};

class ArrowEffect : public Effect {
    Q_OBJECT

public:
    explicit ArrowEffect(Unit* unit);
    virtual ~ArrowEffect() {}
    virtual void apply();
};

class ArrowEffectL2 : public Effect {
    Q_OBJECT

public:
    explicit ArrowEffectL2(Unit* unit);
    virtual ~ArrowEffectL2() {}
    virtual void apply();
};

class ArrowEffectL3 : public Effect {
    Q_OBJECT

public:
    explicit ArrowEffectL3(Unit* unit);
    virtual ~ArrowEffectL3() {}
    virtual void apply();
};

class ArrowEffectL4 : public Effect {
    Q_OBJECT

public:
    explicit ArrowEffectL4(Unit* unit);
    virtual ~ArrowEffectL4() {}
    virtual void apply();
};

class ArrowEffectL5 : public Effect {
    Q_OBJECT

public:
    explicit ArrowEffectL5(Unit* unit);
    virtual ~ArrowEffectL5() {}
    virtual void apply();
};

class CannonEffect : public Effect {
    Q_OBJECT

public:
    explicit CannonEffect(Unit* unit);
    virtual ~CannonEffect() {}

    virtual void apply();
};

class CannonEffectL2 : public Effect {
    Q_OBJECT

public:
    explicit CannonEffectL2(Unit* unit);
    virtual ~CannonEffectL2() {}

    virtual void apply();
};

class CannonEffectL3 : public Effect {
    Q_OBJECT

public:
    explicit CannonEffectL3(Unit* unit);
    virtual ~CannonEffectL3() {}

    virtual void apply();
};

class CannonEffectL4 : public Effect {
    Q_OBJECT

public:
    explicit CannonEffectL4(Unit* unit);
    virtual ~CannonEffectL4() {}

    virtual void apply();
};

class CannonEffectL5 : public Effect {
    Q_OBJECT

public:
    explicit CannonEffectL5(Unit* unit);
    virtual ~CannonEffectL5() {}

    virtual void apply();
};

class FlakEffect : public Effect {
    Q_OBJECT

public:
    explicit FlakEffect(Unit* unit);
    virtual ~FlakEffect() {}

    virtual void apply();
};

class FlakEffectL2 : public Effect {
    Q_OBJECT

public:
    explicit FlakEffectL2(Unit* unit);
    virtual ~FlakEffectL2() {}

    virtual void apply();
};

class FlakEffectL3 : public Effect {
    Q_OBJECT

public:
    explicit FlakEffectL3(Unit* unit);
    virtual ~FlakEffectL3() {}

    virtual void apply();
};

class FlakEffectL4 : public Effect {
    Q_OBJECT

public:
    explicit FlakEffectL4(Unit* unit);
    virtual ~FlakEffectL4() {}

    virtual void apply();
};

class FlakEffectL5 : public Effect {
    Q_OBJECT

public:
    explicit FlakEffectL5(Unit* unit);
    virtual ~FlakEffectL5() {}

    virtual void apply();
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
    virtual void apply();
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
    virtual void apply();
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
    virtual void apply();
};

class NPCTarEffectL2 : public Effect {
    Q_OBJECT

public:
    explicit NPCTarEffectL2(Unit* unit);
    virtual ~NPCTarEffectL2();
    /**
     * applies the tar slowdown effect.
     *
     * @author Duncan Donaldson
     */
    virtual void apply();
};

class NPCTarEffectL3 : public Effect {
    Q_OBJECT

public:
    explicit NPCTarEffectL3(Unit* unit);
    virtual ~NPCTarEffectL3();
    /**
     * applies the tar slowdown effect.
     *
     * @author Duncan Donaldson
     */
    virtual void apply();
};

class NPCTarEffectL4 : public Effect {
    Q_OBJECT

public:
    explicit NPCTarEffectL4(Unit* unit);
    virtual ~NPCTarEffectL4();
    /**
     * applies the tar slowdown effect.
     *
     * @author Duncan Donaldson
     */
    virtual void apply();
};

class NPCTarEffectL5 : public Effect {
    Q_OBJECT

public:
    explicit NPCTarEffectL5(Unit* unit);
    virtual ~NPCTarEffectL5();
    /**
     * applies the tar slowdown effect.
     *
     * @author Duncan Donaldson
     */
    virtual void apply();
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
    virtual void apply();

private:
    int count_;
};
/**
* an effect that deals damage over time to an NPC.
*
* @author Duncan Donaldson
*/
class NPCBurnEffectL2 : public Effect {
    Q_OBJECT

public:
    explicit NPCBurnEffectL2(Unit* unit);
    virtual ~NPCBurnEffectL2(){}
    /**
     * applies the burn effect.
     *
     * @author Duncan Donaldson
     */
    virtual void apply();

private:
    int count_;
};
/**
* an effect that deals damage over time to an NPC.
*
* @author Duncan Donaldson
*/
class NPCBurnEffectL3 : public Effect {
    Q_OBJECT

public:
    explicit NPCBurnEffectL3(Unit* unit);
    virtual ~NPCBurnEffectL3(){}
    /**
     * applies the burn effect.
     *
     * @author Duncan Donaldson
     */
    virtual void apply();

private:
    int count_;
};
/**
* an effect that deals damage over time to an NPC.
*
* @author Duncan Donaldson
*/
class NPCBurnEffectL4 : public Effect {
    Q_OBJECT

public:
    explicit NPCBurnEffectL4(Unit* unit);
    virtual ~NPCBurnEffectL4(){}
    /**
     * applies the burn effect.
     *
     * @author Duncan Donaldson
     */
    virtual void apply();

private:
    int count_;
};
/**
* an effect that deals damage over time to an NPC.
*
* @author Duncan Donaldson
*/
class NPCBurnEffectL5 : public Effect {
    Q_OBJECT

public:
    explicit NPCBurnEffectL5(Unit* unit);
    virtual ~NPCBurnEffectL5(){}
    /**
     * applies the burn effect.
     *
     * @author Duncan Donaldson
     */
    virtual void apply();

private:
    int count_;
};

class FireEffect : public Effect {
    Q_OBJECT

public:
    explicit FireEffect(Unit* unit);
    virtual ~FireEffect(){}

    virtual void apply();
};

class FireEffectL2 : public Effect {
    Q_OBJECT

public:
    explicit FireEffectL2(Unit* unit);
    virtual ~FireEffectL2(){}

    virtual void apply();
};

class FireEffectL3 : public Effect {
    Q_OBJECT

public:
    explicit FireEffectL3(Unit* unit);
    virtual ~FireEffectL3(){}

    virtual void apply();
};

class FireEffectL4 : public Effect {
    Q_OBJECT

public:
    explicit FireEffectL4(Unit* unit);
    virtual ~FireEffectL4(){}

    virtual void apply();
};

class FireEffectL5 : public Effect {
    Q_OBJECT

public:
    explicit FireEffectL5(Unit* unit);
    virtual ~FireEffectL5(){}

    virtual void apply();
};

} /* end namespace td */

#endif
