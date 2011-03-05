#ifndef _RESMANAGER_H
#define _RESMANAGER_H

#include "ClsIdx.h"
#include "GameObject.h"
#include <QList>
#include <QVector>

namespace td {

/**
 * Resource Manager class for GameObjects.
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

public:
    /**
     * Constructor for the Resource Manager.
     *
     * @author Darryl Pogue
     */
    ResManager();

    /**
     * Destructor for the Resource Manager.
     *
     * @author Darryl Pogue.
     */
    virtual ~ResManager();

    /**
     * Creates a GameObject of the given type.
     *
     * @author Darryl Pogue
     * @param type The class index of the type to be created.
     * @return A new GameObject of the given type, or NULL.
     */
    GameObject* createObject(unsigned char type);

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
        return objects_[type].size();
    }
};

} /* end namespace td */

#endif
