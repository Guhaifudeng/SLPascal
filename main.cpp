#include "Afx.h"
#include "State.h"
using namespace std;
extern CState State;
int main(int argc,char** argv)
{
    if(!State.CommandInit(argc,argv))
    {
        PrintError();
        //return 0;
    }

    cout << "\nHello world!" << endl;
    return 0;
}
