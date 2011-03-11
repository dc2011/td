#ifndef NPC_H
#define NPC_H

#include <QVector2D>
#include <QEvent>
#include <QKeyEvent>

#include "Unit.h"
#include "Effect.h"
#include "../input/NPCInputComponent.h"
#include "../physics/NPCPhysicsComponent.h"
#include "../graphics/GenericDinoGraphicsComponent.h"

namespace td {

class NPC : public Unit {
    Q_OBJECT

public:
    /**
     * Gets the unique class index for this object type.
     *
     * @author Darryl Pogue
     * @return The class index.
     */
    static unsigned char clsIdx() {
        return td::clsidx::kNPC;
    }

public:
    NPC();
    virtual ~NPC() {}

    virtual void update();
    size_t getHealth();
    void setHealth(size_t);
    size_t getDamage();
    void setDamage(size_t);
    /**
     * initializes the NPCs components.
     *
     * @author Duncan Donaldson
     */
    virtual void initComponents();

    int getWidth(){
        return width_;
    }

    void setWidth(int width){
        width_ = width;
    }

    int getHeight(){
        return height_;
    }

    void setHeight(int height){
        height_ = height;
    }
private:
    size_t health_;
    size_t damage_;
    QList<Effect*> effects_;
    int height_;
    int width_;
};

} /* end namespace td */

#endif // NPC_H
