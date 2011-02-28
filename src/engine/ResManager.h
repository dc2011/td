#ifndef _RESMANAGER_H
#define _RESMANAGER_H

#include "ClsIdx.h"
#include "GameObject.h"
#include <QList>
#include <QVector>

namespace td {

class ResManager
{
private:
    QVector<QList<GameObject*> > objects_;

public:
    ResManager();
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
