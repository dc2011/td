#include "Driver.h"

namespace td {

Driver::Driver() : QObject(), gameMap_(NULL), gameTimer_(NULL)
{
    mgr_ = new ResManager(this);
}

Driver::~Driver()
{
    delete mgr_;
    delete gameMap_;
    delete gameTimer_;
}

} /* end namespace td */
