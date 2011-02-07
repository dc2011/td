#ifndef INPUTCOMPONENT
#define INPUTCOMPONENT

#include <QObject>
#include <QEvent>
class Unit;
class InputComponent : public QObject {
    Q_OBJECT
public:
    virtual ~InputComponent() {};
    virtual void setParent(Unit*) = 0;
    virtual void update() = 0;
};

#endif
