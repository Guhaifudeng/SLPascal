#ifndef CLEX_H
#define CLEX_H
#include "Afx.h"
#include "State.h"
#include "Structure.h"
#include "CommonLib.h"
#include "ErrorProc.h"
#include "State.h"
using namespace std;
extern CState State;
extern vector<CToken> *pTokenList;
class CLex
{
private:
    int m_szLexTbl[40][130];					//词法分析表
    string m_szSource;							//源代码字符串
    map<string,int> m_KeywordTbl;				//保留字表
    string m_szBuffer;							//词法分析缓存区
    int m_iRow;									//当前分析的源代码行号
    string m_szFileName;						//源程序文件名
    int m_iNonTerminal;							//当前非终结符编号
    int m_iPos;									//源代码当前读取位置
    bool Process(int iTag);						//词法分析处理
    void EmitToken(const int iKind,const string szContent,const int iRow);		//记录单词信息
    void EmitToken(const int iKind,const int iContent,const int iRow);			//记录单词信息
    bool SearchKeyword(string szKeyWord,int &iPosition);
    void BufferBack();

public:
    CLex();
    ~CLex();
    bool GenToken(string szSource);
    void SetKeywords(string szStr);
    void SetLexTbl(string szStr);
    void SetFileName(string szStr);
    void LexInit();
};

#endif // CLEX_H
