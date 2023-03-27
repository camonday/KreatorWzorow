#include "MyForm.h"
#include <stdio.h>


using namespace System;

using namespace System::Windows::Forms;


[event_receiver(native)]
class CReceiver {
public:
    void MyHandler1(int nValue) {
        printf("MyHandler1 was called with value %d.\n", nValue);

    }


    void hookEvent(try1::CSource* pSource) {
        __hook(&try1::CSource::MyEvent, pSource, &CReceiver::MyHandler1);
    }

    void unhookEvent(try1::CSource* pSource) {
        __unhook(&try1::CSource::MyEvent, pSource, &CReceiver::MyHandler1);
    }
};

[STAThread]
void main(array<String^>^ args)

{
   // try1::CSource source;
    CReceiver receiver;


    Application::EnableVisualStyles();

    Application::SetCompatibleTextRenderingDefault(false);

    try1::MyForm form;
    try1::CSource source = form.giveSource();
    



    receiver.hookEvent(&source);
    Application::Run(% form);
    receiver.unhookEvent(&source);



}

