#ifndef _thread_
#define _thread_

#include <QThread>

namespace td
{

/**
 * An implementation of a QThread that automatically runs itself.
 * The entire implementation is contained within this header file.
 *
 * @author Darryl Pogue
 */
class Thread : public QThread
{
protected:
    void run() { exec(); }
};

} /* end namespace td */

#endif
