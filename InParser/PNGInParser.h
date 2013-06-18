#ifndef PNGINPARSER_H
#define PNGINPARSER_H
#include "InParse.h"

class PNGInParser: public AbstractInParser {
public:
    QString getPixels(unsigned char *&rpDst);
    void parsePixels(unsigned char *, unsigned char *, const QString& );
    void getPals(unsigned char *&);
};

#endif // PNGINPARSER_H
