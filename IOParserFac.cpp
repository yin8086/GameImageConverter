#include <QtCore>
#include "BaseDef.h"
#include "IOParserFac.h"
#include "IOParser/PNGIOParser.h"
#include "IOParser/UnityIOParser.h"
#include "IOParser/GzipGimIOParser.h"

AbstractIOParser* IOParserFactory::createIOParser(int mode) {
    if(mode == 0){
        return new UnityIOParser();
    }
    else if(mode == 1) {
        return new PNGIOParser();
    }
    else if(mode == 2) {
        return new GzipGimIOParser();
    }
    else
        return NULL;
}
