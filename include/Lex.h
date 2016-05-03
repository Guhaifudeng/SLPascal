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
    int m_szLexTbl[40][130];					//�ʷ�������
    string m_szSource;							//Դ�����ַ���
    map<string,int> m_KeywordTbl;				//�����ֱ�
    string m_szBuffer;							//�ʷ�����������
    int m_iRow;									//��ǰ������Դ�����к�
    string m_szFileName;						//Դ�����ļ���
    int m_iNonTerminal;							//��ǰ���ս�����
    int m_iPos;									//Դ���뵱ǰ��ȡλ��
    bool Process(int iTag);						//�ʷ���������
    void EmitToken(const int iKind,const string szContent,const int iRow);		//��¼������Ϣ
    void EmitToken(const int iKind,const int iContent,const int iRow);			//��¼������Ϣ
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
