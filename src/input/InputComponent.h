#ifndef INPUTCOMPONENT
#define INPUTCOMPONENT

#include <QObject>
#include <QEvent>

namespace td {

class Unit;

class InputComponent : public QObject {
    Q_OBJECT
public:
    virtual ~InputComponent() {};
    
    /**
     * Inheriting classes need to define a method of setting their parent (owner) object.
     * 
     * @author Tom Nightingale
     */
    virtual void setParent(Unit*) = 0;
    
    /**
     * TODO: Is this being used?
     * 
     * @author Tom Nightingale
     */
    virtual void update() = 0;
};

} /* end namespace td */

#endif
