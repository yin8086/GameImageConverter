#include <QtCore>
#include "InParserFac.h"
#include "InParser/UnityInParser.h"

AbstractInParser* InParserFactory::createInParser(int mode) {
    if(mode == 0){
        return new UnityInParser();
    }
    else
        return NULL;
}
