#ifndef MainWindow_H
#define MainWindow_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QFileDialog>
#include <QString>
#include "../engine/GraphicsComponent.h"

namespace td {

class MainWindow : public QMainWindow {
    Q_OBJECT

private:

    /**
     * The graphics scene which contains all the objects
     */
    QGraphicsScene* scene_;

    /**
     * The view which displays the graphics scene.
     */
    QGraphicsView* view_;

public:
    MainWindow();
    virtual ~MainWindow();
    /**
     * Creates a dialog box that allows the user to select a map.
     *
     * @author Duncan Donaldson
     */
    QString GetMapName();
    QGraphicsScene* getScene() { return scene_; }
    
protected:
    virtual bool event(QEvent*);
    //virtual void keyPressEvent(QKeyEvent *);
    virtual void keyReleaseEvent(QKeyEvent *);

public slots:
    /**
     * Creates a graphical representation of a game object.
     * This creates a QGraphicsPixmapItem to be rendered, adds it to the
     * graphics scene, and stores it back in the graphics component of the
     * game object.
     *
     * @author Darryl Pogue
     * @param gc The GraphicsComponent of the game object.
     */
    void createGraphicRepr(GraphicsComponent* gc);

    /**
     * Draws the graphical representation of the game object.
     *
     * @author Darryl Pogue
     * @param gc The GraphicsComponent of the game object.
     */
    void drawItem(QPoint pos, GraphicsComponent* gc);
    
signals:
    void signalKeyPressed(int);
    void signalKeyReleased(int);
};

} /* end namespace td */

#endif
