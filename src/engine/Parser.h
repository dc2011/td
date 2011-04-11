#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QFile>

#include "NPCWave.h"

namespace td {

class Parser {
public:
    explicit Parser(const QString& filename) throw (const char*);
    ~Parser();
    NPCWave* readWave();

// variables
private:
    QFile file_;

public:
    int difficulty;
    int baseHP;
    int woodQty;
    int stoneQty;
    int boneQty;
    int tarQty;
    QString map;
};

}

#endif
