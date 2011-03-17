#include <QObject>

template <typename T>

class DelayedDelete : public QObject {

public:
    explicit DelayedDelete(T* &item) : item_(item) {
        item = 0;
        deleteLater();
    }

    virtual ~DelayedDelete() {
        delete item_;
    }

private:
    T* item_;
};


