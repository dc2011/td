#ifndef _RESMANAGER_H
#define _RESMANAGER_H

#include "ClsIdx.h"
#include "GameObject.h"
#include <QList>
#include <QVector>

namespace td {

class Driver;

/**
 * Manager class for GameObjects.
 *
 * @author Darryl Pogue
 */
class ResManager
{
private:
    /**
     * The storage structure for objects.
     * This is less than ideal, blame Darryl Pogue.
     */
    QVector<QList<GameObject*> > objects_;

    /**
     * The current game driver, which is used as a parent for all game objects.
     */
    Driver* driver_;

public:
    /**
     * Constructor for the Resource Manager.
     *
     * @author Darryl Pogue
     * @param driver The current game driver.
     */
    ResManager(Driver* driver);

    /**
     * Destructor for the Resource Manager.
     *
     * @author Darryl Pogue.
     */
    virtual ~ResManager();

    /**
     * Creates a GameObject of the given type and adds it to the manager.
     *
     * @author Darryl Pogue
     * @param type The class index of the type to be created.
     * @return A new GameObject of the given type, or NULL.
     */
    GameObject* createObject(unsigned char type);

    /**
     * Creates a GameObject with the given id and adds it to the manager.
     *
     * @author Darryl Pogue
     * @param id The id of the object to be created.
     * @return A new GameObject with the given id, or NULL.
     */
    GameObject* createObjectWithID(unsigned int id);

    /**
     * Creates a temporary GameObject of the given type, without adding it to the
     * manager.
     *
     * @author Darryl Pogue
     * @param type The class index of the type to be created.
     * @return A new GameObject of the given type, or NULL.
     */
    GameObject* createTempObject(unsigned char type);

    /**
     * Adds an existing game object to the resource manager.
     *
     * @author Duncan Donaldson
     * @author Darryl Pogue
     * @param obj A pointer to the object to be added.
     */
    void addExistingObject(GameObject* obj);

    /**
     * Finds a GameObject based on its identifier.
     *
     * @author Darryl Pogue
     * @param id The identifier of the object to search for.
     * @return The GameObject, or NULL if it cannot be found.
     */
    GameObject* findObject(unsigned int id);

    /**
     * Deletes a GameObject based on its identifier.
     *
     * @author Darryl Pogue
     * @param id The identifier of the object to delete.
     */
    void deleteObject(unsigned int id);

    /**
     * Deletes a GameObject.
     *
     * @author Darryl Pogue
     * @param obj The GameObject to delete.
     */
    void deleteObject(GameObject* obj);

    /**
     * Gets the total number of objects.
     *
     * @author Darryl Pogue
     * @return The number of objects.
     */
    unsigned int countObjects() const;

    /**
     * Gets the number of objects of the given type.
     *
     * @author Darryl Pogue
     * @param type The class index of the type to count.
     * @return The number of objects of the given type.
     */
    unsigned int countObjectsByType(unsigned char type) const {
        unsigned int ret = 0;
        for (int i = 0; i < objects_[type].size(); i++) {
            if (objects_[type][i] != NULL) {
                ret++;
            }
        }
        return ret;
    }

protected:
    /**
     * Creates a GameObject of the given type.
     *
     * @author Darryl Pogue
     * @param type The class index of the type to be created.
     * @return A new GameObject of the given type, or NULL.
     */
    GameObject* internalCreateObject(unsigned char type);
};

} /* end namespace td */

#endif
