#ifndef INPUTCOMPONENT
#define INPUTCOMPONENT

#include <QObject>
#include <QEvent>

class InputComponent : public QObject {
    Q_OBJECT
public:
    virtual ~InputComponent() {};
    
    virtual void update() = 0;
};

#endif
