#include <QtCore>
#include "OutParserFac.h"
#include "OutParser/PNGOutParser.h"

AbstractOutParser* OutParserFactory::createOutParser(int oMode) {
    if (oMode == 1) {
        return new PNGOutParser();
    }
    else
        return NULL;
}

