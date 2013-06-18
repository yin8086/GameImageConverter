#include <QtCore>
#include "InParserFac.h"
#include "InParser/UnityInParser.h"
#include "InParser/PNGInParser.h"

AbstractInParser* InParserFactory::createInParser(int mode) {
    if(mode == 0){
        return new UnityInParser();
    }
    else if(mode == 1) {
        return new PNGInParser();
    }
    else
        return NULL;
}
