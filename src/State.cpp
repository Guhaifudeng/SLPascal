#include "State.h"
void replace_all(string& str,char* oldValue,char* newValue)
{
    string::size_type pos(0);

    while(true){
        pos=str.find(oldValue,pos);
        if (pos!=(string::npos))
        {
            str.replace(pos,strlen(oldValue),newValue);
            pos+=2;//注意是加2，为了跳到下一个反斜杠
        }
        else
            break;
    }
}
 bool CState::CommandInit(int argc, char** argv)
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
    m_szSourceFile= a+"test\\1.mlp";
    m_szSysDir=a+"sys\\";
    m_szErrFile=a+"err\\";
    m_szOutputFile=a+"out\\1.asm";

    string szTmp = m_szSysDir + "lex.txt";

    if (-1 == access(szTmp.c_str(),2))
    {
        EmitError("can't find the file named lex.txt");

        return false;
    }

    szTmp = m_szSysDir + "keywords.txt";

    if (-1 == access(szTmp.c_str(),2))
    {
        EmitError("can't find the file named keywords.txt");

        return false;
    }

    szTmp = m_szSysDir + "TypeSys.txt";

    if (-1 == access(szTmp.c_str(),2))
    {
        EmitError("can't find the file named TypeSys.txt");

        return false;
    }
    if (-1 == access(m_szSourceFile.c_str(),2))
    {
        EmitError("can't find the file"+m_szSourceFile);

        return false;
    }
    return true;
    //system sources
}
