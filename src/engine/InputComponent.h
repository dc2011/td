#ifndef INPUTCOMPONENT
#define INPUTCOMPONENT

class InputComponent : public QObject {
    Q_OBJECT
public:
    InputComponent();
    ~InputComponent() {};
    
    virtual void Update() = 0;

private:
    
};

#endif