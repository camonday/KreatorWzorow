#include "MyForm.h"
#include <stdio.h>


using namespace System;

using namespace System::Windows::Forms;

[event_source(native)]
class CSource {
public:
    __event void MyEvent(int nValue);
};

[event_receiver(native)]
class CReceiver {
public:
    void MyHandler1(int nValue) {
        printf("MyHandler1 was called with value %d.\n", nValue);

    }


    void hookEvent(CSource* pSource) {
        __hook(&CSource::MyEvent, pSource, &CReceiver::MyHandler1);
    }

    void unhookEvent(CSource* pSource) {
        __unhook(&CSource::MyEvent, pSource, &CReceiver::MyHandler1);
    }
};




public ref class Okienko : try1::MyForm {
    CSource* source = new CSource;
public: void DoubleClick_toOverride() override{
        __raise source->MyEvent(paintBrush.ToArgb());
    }
    public: CSource* getSource() {
        return source;
    }
};

[STAThread]
int main(array<String^>^ args)

{
   // try1::CSource source;
    
    CReceiver receiver;
    Application::EnableVisualStyles();

    Application::SetCompatibleTextRenderingDefault(false);

    Okienko form;
    CSource* source = form.getSource();
   
    



    receiver.hookEvent(source);
    Application::Run(% form);
    receiver.unhookEvent(source);



}


