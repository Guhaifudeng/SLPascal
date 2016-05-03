#include "Lex.h"

bool CLex::Process(int iTag)
{
     int iTmp=0;
    if (iTag==-99)
        return false;

    if (iTag<0)
    {
        BufferBack();
        m_szBuffer=trim(m_szBuffer);

        if (iTag==-1)//系统
        {
            m_szBuffer=UpperCase(m_szBuffer);
            if (SearchKeyword(m_szBuffer,iTmp)==true)
            {
                cout<<iTmp+40<<":"<<m_szBuffer<<endl;
                EmitToken(iTmp+40,NULL,m_iRow);
            }
            else
            {
                if (m_szBuffer.compare("TRUE")==0 || m_szBuffer.compare("FALSE")==0 )
                {
                    cout<<3<<":"<<m_szBuffer<<endl;
                    //EmitToken(3,SymbolTbl.RecConstTbl(m_szBuffer,7),m_iRow);// 符号表-存储常量
                }
                else
                {
                    cout<<1<<":"<<m_szBuffer<<endl;
                    //EmitToken(1,m_szBuffer,m_iRow);//标识符
                }
            }
        }

        if (iTag>=-6 && iTag<=-2)//常量
        {
            cout<<-iTag<<":"<<m_szBuffer<<endl;
            //EmitToken(-iTag,SymbolTbl.RecConstTbl(m_szBuffer,-iTag),m_iRow);// 符号表-存储常量
        }
        if (iTag>=-15 && iTag<=-7)//界符
        {
            cout<<-iTag<<":"<<m_szBuffer<<endl;
            EmitToken(-iTag,NULL,m_iRow);
        }

        if (iTag>=-28 && iTag<=-16)//运算符
        {
            cout<<-iTag<<":"<<m_szBuffer<<endl;
            EmitToken(-iTag,NULL,m_iRow);
        }

        if (iTag==-42)//整型
        {
            BufferBack();
            m_szBuffer=trim(m_szBuffer);
            cout<<3<<":"<<m_szBuffer<<endl;
           // EmitToken(3,SymbolTbl.RecConstTbl(m_szBuffer,3),m_iRow); //符号表-存储常量
        }

        m_szBuffer="";
        m_iNonTerminal=0;
    }
    else
    {
        m_iNonTerminal=iTag;
    }

    return true;
}

void CLex::EmitToken(const int iKind, const string szContent, const int iRow)
{
    pTokenList->push_back(CToken(iKind,szContent,iRow,m_szFileName));
}

void CLex::EmitToken(const int iKind, const int iContent, const int iRow)
{
    string szTmp;
    char cBuffer[5];
    itoa(iContent,cBuffer,10);
    szTmp=cBuffer;
    EmitToken(iKind,szTmp,iRow);
}

bool CLex::SearchKeyword(string szKeyWord, int& iPosition)
{
    map<string,int>::iterator It=m_KeywordTbl.find(szKeyWord);
    if (It!=m_KeywordTbl.end())
    {
        iPosition=It->second;
        return true;
    }
    return false;
}

void CLex::SetFileName(string szStr)
{
    m_szFileName=szStr;
}

void CLex::BufferBack()
{
    m_szBuffer.erase(m_szBuffer.end()-1);
    m_iPos--;
}

CLex::CLex()
{

}

CLex::~CLex()
{

}

bool CLex::GenToken(string szSlpSource)
{


    bool bTag=true;
    m_iPos=0;
    m_szSource=szSlpSource;
    m_szSource.push_back(' ');
    m_iNonTerminal=0;
    m_szBuffer="";
    m_iRow=1;
    int TmpPos=0;
    pTokenList->clear();

    while (m_iPos<m_szSource.length() && bTag)
    {
        if (m_szSource[m_iPos]=='\n'&& TmpPos!=m_iPos)
        {
            m_iRow++;

            TmpPos=m_iPos;
        }
        m_szBuffer.push_back(m_szSource.at(m_iPos));
        bTag=Process(m_szLexTbl[m_iNonTerminal][(unsigned char)(m_szSource[m_iPos]<128?m_szSource[m_iPos]:128)]);
        if (!bTag)
        {
            EmitError(m_szFileName+"("+itos(m_iRow)+"): lex Error");

            return false;
        }

        m_iPos++;
    }
    return bTag;
}


void CLex::SetKeywords(string szStr)
{
    SetTbl(szStr,m_KeywordTbl);
}

void CLex::SetLexTbl(string szStr)
{
    int iRow=0;
    int iCol=0;
    int iTmp=0;
    szStr=StrErase(szStr,'\n');
	char node[] = {'L','N','+','-','*','/','(',')','[',']','<','=','>','\'','^','@',';',':',',','.','\n','O'};// 22
	int szLexTbl[38][22] ;
    for(iRow=1; iRow<=37; iRow++)
    {
        for(iCol=0; iCol<=21; iCol++)
        {
            szLexTbl[iRow][iCol]=atoi(szStr.substr(iTmp,3).c_str());
            iTmp=iTmp+3;
        }
    }
	int iNode =0;
	int iState=0;
	for(iState=1; iState<=37; iState++){
		for(iNode=0; iNode<=128; iNode++)//other
			m_szLexTbl[iState][iNode] = szLexTbl[iState][21];
		for(iNode='A'; (iState!=4||iState!=5)&&iNode<='z'; iNode++)//letter
			m_szLexTbl[iState][iNode] = szLexTbl[iState][0];
		for(iNode='0'; iNode<='9'; iNode++)//number
			m_szLexTbl[iState][iNode] = szLexTbl[iState][1];
		for(iNode=2;iNode<=20;iNode++)//single char
			m_szLexTbl[iState][node[iNode]] = szLexTbl[iState][iNode];
		if(iState==4){//e/E
			for(iNode='A';iNode<='z'; iNode++)//letter
				if(iNode=='e'||iNode=='E') m_szLexTbl[iState][iNode] = 035;
				else m_szLexTbl[iState][iNode] = szLexTbl[iState][0];
		}
		if(iState==5){//e/E
			for(iNode='A';iNode<='z'; iNode++)//letter
				if(iNode=='e'||iNode=='E') m_szLexTbl[iState][iNode] =szLexTbl[iState][0] ;
				else m_szLexTbl[iState][iNode] = szLexTbl[iState][21];
		}

	}
}


void CLex::LexInit()
{
    m_szSource="";
    SetLexTbl(FileRead(State.m_szSysDir+"lex.txt"));
    SetKeywords(FileRead(State.m_szSysDir+"keywords.txt"));
}
