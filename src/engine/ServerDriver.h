#ifndef SERVERDRIVER_H
#define SERVERDRIVER_H

class ServerDriver : public QObject {
  Q_OBJECT
public:
  ServerDriver(QObject *parent = 0);
  ~ServerDriver();

private:
  
};

#endif