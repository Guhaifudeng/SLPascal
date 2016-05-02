#ifndef STATE_H
#define STATE_H


class State
{

    public:
        string m_szSourceFile;
        string m_szSysDir;
        string m_szOutputFile;
        //string m_szSysLib;
        //string m_szUserLib;
        string m_szErrFile;
        bool m_bOpti;//optimization

    public:
        CState()
        {
            m_szSourceFile = "";
            m_szSysDir = "";
            m_szOutputFile = "";
            m_szSysLib = "";
            //m_szUserLib = "";
            //m_szErrFile = "";
            m_bOpti = false;
        };
        virtual ~State();
        bool CommandInit(int argc, char** argv);
    protected:
    private:

};

#endif // STATE_H
