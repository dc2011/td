#ifndef INPUTCOMPONENT
#define INPUTCOMPONENT

#include <QObject>
#include <QEvent>

class InputComponent : public QObject {
    Q_OBJECT
public:
    virtual ~InputComponent() {};
    
    virtual void Update() = 0;
};

#endif
