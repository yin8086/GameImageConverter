#include <QtCore>
#include "OutParserFac.h"
#include "OutParser/PNGOutParser.h"

AbstractOutParser* OutParserFactory::createOutParser(int oMode) {
    if (oMode == 1) {
        return new PNGOutParser();
    }
    else if(oMode == 0) {
        //return new
    }
    else
        return NULL;
}

