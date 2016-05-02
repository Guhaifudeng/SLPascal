#ifndef CERROR_H
#define CERROR_H
#include "Afx.h"

class CError
{
    public:
        CError();
        virtual ~CError();
    void PrintErrorLine(int errorLine);//just output the line number where this program generates error
    void PrintErrorNote(string errorNote);//output the note when there has some resources lost
    protected:
    private:
};

#endif // CERROR_H
