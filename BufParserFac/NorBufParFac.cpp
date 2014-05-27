#include <QtCore>
#include "BaseDef.h"
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
#include "BufferParser/DXTBufParser.h"
#include "BufferParser/DXT1BufParser.h"
#include "BufferParser/ETC1BufParser.h"
#include "BufferParser/ATCIBufParser.h"


AbstractBufferParser* NormalBufParserFac::createBufParser(const QString &type) {
    if(type == "ALPHA8") {
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
    else if(type == "DXT5") {
        return new DXTBufParser();
    }
    else if(type == "DXT1") {
        return new DXT1BufParser();
    }
    else if(type == "ETC1") {
        return new ETC1BufParser();
    }
    else if(type == "ATCI") {
        return new ATCIBufParser();
    }
    else
        return NULL;
}
