#ifndef OUTPARSER_H
#define OUTPARSER_H

class AbstractOutParser {
public:
    virtual int write(const QString& fName) = 0;
};

#endif // OUTPARSER_H
