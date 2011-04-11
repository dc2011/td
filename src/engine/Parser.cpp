#include <QFile>
#include <QStringList>

#include "Parser.h"

namespace td {

Parser::Parser(const QString &filename) throw (const char*) : file_(filename) {
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
    NPCWave* wave = new NPCWave();
    QString waveLine = file_.readLine();
    QStringList waveInfo = waveLine.split(',');
    return wave;
}

}
