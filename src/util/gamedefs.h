#ifndef GAMEDEFS_H
#define GAMEDEFS_H

#include <QMap>
#include <QString>
#include <QVariant>
#include "mutex_magic.h"

namespace td {

class GameDefs
{
    THREAD_SAFE_SINGLETON

private:
    /** Static instance of the class. There can only be one. */
    static GameDefs* instance_;

    /** Map of game defines and their values. */
    QMap<QString, QVariant> defs_;


    /**
     * Private constructor.
     * Reads the QSettings file and initializes the defines map.
     *
     * @author Darryl Pogue
     */
    GameDefs();

public:
    /**
     * Returns the GameDefs instance.
     *
     * @author Darryl Pogue
     * @return An instance of GameDefs.
     */
    static GameDefs* instance() {
        mutex_.lock();
        if (instance_ == NULL) {
            instance_ = new GameDefs();
        }
        mutex_.unlock();
        return instance_;
    }

    template<typename T>
    T getValue(QString key) {
        QVariant v = 0;
        if (defs_.contains(key)) {
            v = defs_[key];
        }

        return v.value<T>();
    }
};

} /* end namespace td */

#endif
