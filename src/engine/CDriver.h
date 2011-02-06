#ifndef CDRIVER_H
#define CDRIVER_H
#include <QTimer>
#include <QApplication>
#include <QVector>
#include "Player.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerInputComponent.h"
//#include "GameInfo.h"
//#include "GameObject.h"
class CDriver : public QObject {
  
private:
    //  GameInfo gameInfo;
    QTimer* gameTimer_;
    Player* human_;
    //QVector<GameObject> objects;
public:
    // ctors and dtors
    CDriver(QObject *parent = 0);
    ~CDriver();

    /**
     * Creates a human player object.
     * Sets event filter for key presses to be passed to PlayerInputComponent.
     * 
     * @author Tom Nightingale
     * @return Player*, pointer to new player instance.
     */
    Player* createHumanPlayer(QObject *);

    /**
     * TODO: "Description here"
     * 
     * @author Duncan / Ian
     * @return void
     */
    void bindAll();

    /**
     * TODO: "Description here"
     * 
     * @author Duncan / Ian
     * @return void
     */
    void bindSingle(const GameObject& obj);
    
    /**
     * Start game timer.
     * 
     * @author Duncan / Ian
     * @return void
     */
    void startGame();
    
    /**
     * Stop game timer.
     * 
     * @author Duncan / Ian
     * @return void
     */
    void endGame();
    
    /**
     * Load map from file, parse data, store in game info map property
     * 
     * @author Duncan / Ian
     * @return int
     */
    //int loadMap(GameInfo &gi, char* map);
};
#endif
