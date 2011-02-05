#include <QPoint>

#include "InputComponent.h"
#include "PhysicsComponent.h"


class GameObject : public QObject {
  Q_OBJECT
public:
    virtual ~GameObject() {};
    
    QPoint GetPos();
    void SetPos(QPoint);

public slots:
    virtual void Update() const = 0;

private:
    QPoint pos_;
};
