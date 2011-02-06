#ifndef SERVERDRIVER_H
#define SERVERDRIVER_H

#include <QObject>

class ServerDriver : public QObject {
  Q_OBJECT
public:
  ServerDriver(QObject *parent = 0) { }
  virtual ~ServerDriver() { }

private:
  
};

#endif
