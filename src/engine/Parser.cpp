#include <QFile>
#include <QStringList>

#include "Parser.h"

namespace td {

Parser::Parser(QObject* parent, const QString &filename) throw (const char*) :parent_(parent), file_(filename) {

    if (!file_.exists()) {
        throw "Parser::Parser(const QString&) : file does not exist.";
    }

    file_.open(QFile::ReadOnly);
    QString linedata(file_.readLine());
    QStringList mapInfo = linedata.split(',');

    difficulty = mapInfo.at(0).toInt();
    map = mapInfo.at(1);
    baseHP = mapInfo.at(2).toInt();
    woodQty = mapInfo.at(3).toInt();
    stoneQty = mapInfo.at(4).toInt();
    boneQty = mapInfo.at(5).toInt();
    tarQty = mapInfo.at(6).toInt();
}

Parser::~Parser() {
    file_.close();
}

NPCWave* Parser::readWave() {
    if (file_.atEnd()) {
        return NULL;
    }
    QString waveLine = file_.readLine();

    if (waveLine.compare("==") || waveLine.compare("\n"))
    {
        return NULL;
    }

    QStringList waveInfo = waveLine.split(',');

    NPCWave* wave = new NPCWave(parent_, waveInfo.at(3).toUInt(), waveInfo.at(2).toUInt(),
                                waveInfo.at(1).toUInt(),waveInfo.at(0).toUInt(),
                                waveInfo.at(5).toUInt());
    return wave;
}

}
