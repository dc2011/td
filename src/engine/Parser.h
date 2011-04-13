#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QFile>

#include "NPCWave.h"

namespace td {

class Parser {
public:
    /**
      Construct the parser based on the file.

      @param filename Map's info file path.
      @throws File does not exist.
      @author Nick Huber
      */
    explicit Parser(QObject* parent, const QString& filename) throw (const char*);

    /**
      Destructor. Closes the file.

      @author Nick Huber
      */
    ~Parser();

    /**
      Read and construct the next wave from the file.

      @return pointer to the next wave object, or NULL if the file is empty.
      @author Nick Huber
      */
    NPCWave* readWave();

    /**
      Utility function to check if the file has been finished reading.
      Can be used in a while loop (while(!parser.done()) { process readWave() }

      @return Whether the parser is finished yet.
      @author Nick Huber
      */
    bool done() { return file_.atEnd(); }

// variables
private:
    QFile file_;
    QObject* parent_;

public:
    int difficulty; /**< Map difficulty multiplier. */
    int baseHP;     /**< Base's HP value. */
    int woodQty;    /**< Amount of wood in a wood mine. */
    int stoneQty;   /**< Amount of stone in a stone mine. */
    int boneQty;    /**< Amount of bone in a bone mine. */
    int tarQty;     /**< Amount of tar in a tar mine. */
    QString map;    /**< Name of associated map. */
};

}

#endif
