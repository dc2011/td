#ifndef CDRIVER_H
#define CDRIVER_H

#include <QTimer>
#include <QPointF>
#include <QSet>

namespace td {

class ContextMenu;
class GameObject;
class Map;
class NPC;
class Player;
class Projectile;
class ResManager;
class Tower;
class MainWindow;
class Stream;
class Unit;

class CDriver : public QObject {
    Q_OBJECT
  
private:
     /** The game object resource manager. */
    ResManager* mgr_;
     /** The central game timer that initiates all object updates. */
    static QTimer* gameTimer_;
     /** The player on this client. */
    Player* human_;
     /** The main game window, where all graphics will be drawn. */
    MainWindow* mainWindow_;
     /** The game map containing all tiles, waypoints, and access methods. */
    Map* gameMap_;
     /** A context menu that appears around the player. */
    ContextMenu* contextMenu_;
     /** An set of enemy units. */
    QSet<NPC*> npc_;
     /** Keeps track of how many NPCs there currently are. */
    size_t npcCounter_;
     /** A projectile fired from a tower. */
    Projectile* projectile_;
     /** A tower built by the players. */
    Tower* tower_;
     /** An set of towers. */
    QSet<Tower*> towers_;
     /** The single instance of this class that can be created. */
    static CDriver* instance_;
     /** Tells objects whether or not the game is being played single player **/
    bool singlePlayer_;
    
    CDriver(MainWindow* parent = 0);
    ~CDriver();

public:
    /**
     * Creates an instance of the class if one doesn't exist yet.
     *
     * @author Dean Morin
     * @param mainWindow A pointer to the main window where everything is drawn.
     * @returns An new instance of the class if one doesn't exist yet, or
     * if one does, it returns a pointer to that instance.
     */
    static CDriver* init(MainWindow* mainWindow);
   
    /**
     * Calls the dtor for the singleton instance.
     *
     * @author Dean Morin
     */
    static void shutdown();
   
    /**
     * Returns the instance of this Singleton class. Should only be used if
     * you know that init() has already been called.
     *
     * @author Dean Morin
     * @returns A pointer to the one available instance of this class.
     */
    static CDriver* instance() {
        return instance_;
    }

    /**
     * Connects the client driver to the server. This must be called
     * at some point before the updateServer() method is ever called,
     * as it creates the stream that updateServer() uses to push updates
     * to the server.
     * 
     * @author Duncan Donaldson
     */
    void connectToServer(const QString& servaddr);

    /**
     * Disconnects the client driver from the server,
     * and destroys the stream used to update the server, call this on cleanup.
     * 
     * @author Duncan Donaldson
     */
    void disconnectFromServer();

    /**
     * Sends client updates to the server, static method, this
     * call this method from the update() function of the GameObject
     * whose state you want to send to the server.
     * 
     * @author Duncan Donaldson
     * @param obj The GameObject to transmit.
     */
    static void updateServer(GameObject* obj);

    /**
     * reads in an object, if it exists, updates it,
     * if it doesn't exist creates it.
     * @author Duncan Donaldson
     */
    void readObject(Stream* s);
    /**
     * 
     * Destroys an object on the client, and notifies the server
     * that the object has been destroyed.
     *
     * @author Duncan Donaldson
     */
    void destroyObjSync(int id);
    /**
     * 
     * Destroys an object on the client without notifying
     * the server of the object destruction.
     *
     * @author Duncan Donaldson
     */
    void destroyObjLocal(int id);
    /**
     * Creates a human player object.
     * Sets event filter for key presses to be passed to PlayerInputComponent.
     * 
     * @author Tom Nightingale
     * @author Duncan Donaldson
     * @author Darryl Pogue
     * @return pointer to new player instance.
     */
    void createHumanPlayer(MainWindow *);

    /**
     * creates npc object
     * @author Marcel Vangrootheest
     * @returns the reference to an NPC
     */
    NPC* createNPC();

    /**
     * Stop game timer.
     * 
     * @author Duncan Donaldson
     * @return void
     */
    void endGame();

    /**
     * Returns the game timer
     *
     * @author Terence Stenvold
     * @return the game timer
     */
    static QTimer* getTimer();


    /**
    * Getter for gameMap_
    *
    * @author Ian Lee
    */
    Map* getGameMap(){
        return gameMap_;
    }

    /**
     * Gets a pointer to the main window where all graphics are drawn.
     *
     * @author Dean Morin, Darryl Pogue. Special thanks to Marcel Vangrootheest.
     * @return The main window where all graphics are drawn.
     */
    MainWindow* getMainWindow() {
        return mainWindow_;
    }
    /**
     * getter for SinglePlayer
     *
     * @author Duncan Donaldson
     * @return whether or not the game is being played single player.
     */
    bool isSinglePlayer();
    /**
     * sets the value of singlePlayer
     *
     * @author Duncan Donaldson
     * @param the value to set singlePlayer to.
     */
    void setSinglePlayer(bool singlePlayer);
    
public slots:
    /**
    * Initialize and start game timer.
    * [Hijacked and updated by Tom Nightingale] 
    * Client side objects are created here.
    *
    * @author Duncan Donaldson
    * @return void
    */
    void startGame(bool singlePlayer);

    /**
     * Called whenenever the spacebar is pressed. It checks the tile type that
     * the player is currently standing on, and performs the appropriate action.
     */
    void handleSpacebarPress();

private slots:
    /**
     * Creates a projectile object.
     *
     * @author Pan Khantidhara, Marcel Vangrootheest, Dean Morin
     * @param source The starting point of the projectile.
     * @param target The destination point of the projectile.
     */
    void createProjectile(QPointF source, QPointF target);

    /**
     * Temp testing method.
     *
     * @author Dean Morin
     */
    void createTower(int towerType, QPointF pos);

    /**
     * handles a received UDP message.
     *
     * @author Duncan Donaldson
     */
    void UDPReceived(Stream* s);

    /**
     * Creates Npc objects based on the game tick.
     *
     * @author Marcel Vangrootheest
     */
    void NPCCreator();

    /**
     * Deletes NPC later
     *
     * @author Marcel Vangrootheest
     */
    void NPCDeleter(Unit*);
};

} /* end namespace td */

#endif
