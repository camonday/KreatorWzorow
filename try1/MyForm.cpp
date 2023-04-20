#include "MyForm.h"
#include "Image.h"
#include <stdio.h>
#include <thread>


using namespace System;
using namespace System::Windows::Forms;

//
// TODO: picture creator/updater
//

void ColourIn(int nValue, int posX, int posY) {
    printf("thread was called with value %d.\n", nValue);
    // lower is example that threads run
    while (true) {
        _sleep(1000);
        printf("%d.\n", nValue);
    }
    //update canva
}

void ThreadFabric(int nValue, int posX, int posY) {
    // remeber threads
    std::thread t1(ColourIn, nValue, posX, posY);
    t1.detach();
}

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
        
        // Calculate position on kanva
        int posX, posY;
        // Here create a thread
        ThreadFabric(nValue, posX, posY);
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
int main(cli::array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    picture obraz;
    obraz.newPicture("try.bmp");

    CReceiver receiver;
    Okienko form;
    CSource* source = form.getSource();
   
    receiver.hookEvent(source);
    Application::Run(% form);
    receiver.unhookEvent(source);
}


