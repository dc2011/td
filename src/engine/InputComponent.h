#ifndef INPUTCOMPONENT
#define INPUTCOMPONENT

#include <QObject>

class InputComponent : public QObject {
    Q_OBJECT
public:
    InputComponent();
    virtual ~InputComponent() {};
    
    virtual void Update() = 0;

private:
    
};

#endif