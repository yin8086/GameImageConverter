#include <QtCore>
#include "NorBufParFac.h"

#include "BufferParser/AlphaBufParser.h"
#include "BufferParser/ARGB1555BufParser.h"
#include "BufferParser/ARGB4444BufParser.h"
#include "BufferParser/ARGB8888BufParser.h"
#include "BufferParser/PVRCT4BufParser.h"
#include "BufferParser/RGB565BufParser.h"
#include "BufferParser/RGB888BufParser.h"
#include "BufferParser/RGBA4444BufParser.h"
#include "BufferParser/RGBA8888BufParser.h"

AbstractBufferParser* AbstractBufParseFactory::createBufParser(const QString &type) {
    if(type == "Alpha8") {
        return new AlphaBufParser();
    }
    else if(type == "ARGB1555") {
        return new ARGB1555BufParser();
    }
    else if(type == "ARGB4444") {
        return new ARGB4444BufParser();
    }
    else if(type == "ARGB8888") {
        return new ARGB8888BufParser();
    }
    else if(type == "RGB565") {
        return new RGB565BufParser();

    }
    else if(type == "RGB888") {
        return new RGB888BufParser();
    }
    else if(type == "RGBA4444") {
        return new RGBA4444BufParser();
    }
    else if(type == "RGBA8888") {
        return new RGBA8888BufParser();
    }
    else if(type == "PVRTC4") {
        return new PVRCT4BufParser();
    }
    else
        return NULL;
}