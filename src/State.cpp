#include "State.h"

State::State()
{
    //ctor
}

State::~State()
{
    //dtor

}
 bool State::InitCommand(int argv, int** arg)
{

    //user's sources
    //default resources to simply the test
    char buf[80];
    getcwd(buf, sizeof(buf));
    string a;
    a.assign(buf);
    replace_all(a,"\\","\\\\");
    a.append("\\\\");
    cout<<a<<endl;
    m_szSourceFile = a+"test\\1.mlp";
    m_szSysDir=a+"sys\\";
    m_szErrFile=a+"err\\";
    m_szOutputFile=a+"out\\1.asm";

    string szTmp = m_szSysDir + "lex.txt";

    if (-1 == access(szTmp.c_str(),2))
    {
        EmitError("无法找到文件lex.txt");

        return false;
    }

    szTmp = m_szSysDir + "keywords.txt";

    if (-1 == access(szTmp.c_str(),2))
    {
        EmitError("无法找到文件keywords.txt");

        return false;
    }

    szTmp = m_szSysDir + "TypeSys.txt";

    if (-1 == access(szTmp.c_str(),2))
    {
        EmitError("无法找到文件TypeSys.txt");

        return false;
    }
    if (-1 == access(m_szSourceFile.c_str(),2))
    {
        EmitError("无法找到文件"+m_szSourceFile);

        return false;
    }
    //system sources
}
