#ifndef GLOBAL_H
#define GLOBAL_H
#include "Afx.h"
#include "State.h"
#include "Structure.h"
#include "Lex.h"
#include "ErrorProc.h"
using namespace std;
extern CState State;
extern vector<ErrorInfo> ErrorProcess;
extern vector<CToken> *pTokenList;
#endif // GLOBAL_H
