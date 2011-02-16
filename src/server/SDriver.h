#ifndef SDRIVER_H
#define SDRIVER_H
#include <QTimer>
#include <QApplication>
#include <QVector>
class SDriver : public QObject {
  
private:
    //  GameInfo gameInfo;
    QTimer* gameTimer_;
    //QVector<GameObject> objects;
public:
    // ctors and dtors
    SDriver();
    ~SDriver();

    /**
     * Connects all current GameObjects' SLOTs to a timer SIGNAL.
     * 
     * @author Duncan Donaldson
     * @return void
     */
    //void bindAll();

    /**
     * Connects a single GameObject's SLOT to a timer SIGNAL.
     * 
     * @author Duncan Donaldson
     * @return void
     */
    //void bindSingle(const GameObject& obj);
    
    /**
     * Start game timer.
     * 
     * @author Duncan Donaldson
     * @return void
     */
    void startGame();
    
    /**
     * Stop game timer.
     * 
     * @author Duncan Donaldson
     * @return void
     */
    void endGame();
    
    /**
     * Load map from file, parse data, store in game info map property
     * 
     * @author Duncan Donaldson
     * @return int
     */
    //int loadMap(GameInfo &gi, char* map);
};
#endif
