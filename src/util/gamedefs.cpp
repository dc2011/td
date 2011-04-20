#include "gamedefs.h"
#include <QSettings>
#include <QStringList>
#include <QCoreApplication>

namespace td {

GameDefs* GameDefs::instance_ = NULL;
QMutex GameDefs::mutex_;

GameDefs::GameDefs() {
    QCoreApplication::setOrganizationName("dc2011");
    QCoreApplication::setApplicationName("td");

    QSettings settings;
    settings.beginGroup("defines");

    foreach (const QString& key, settings.allKeys()) {
        defs_.insert(key, settings.value(key));
    }
}

} /* end namespace td */
