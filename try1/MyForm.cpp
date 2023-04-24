#include "MyForm.h"
#include "Image.h"
#include <stdio.h>
#include <thread>


using namespace System;
using namespace System::Windows::Forms;

//
// TODO: picture creator/updater
//

void ColourIn(int rValue, int gValue, int bValue, int posX, int posY) {
    printf("thread was called with value %d.\n", rValue+gValue+bValue);
    
   



    
    while (true) {
        //update canva
        picture obraz;
        obraz.fillSquare(posX, posY, rValue, gValue, bValue);

        // find way in which to change posX, posY
        posX+= rand() % 3 - 1;
        posY+= rand() % 3 - 1;

        _sleep(1000);

        // lower is example that threads run
        printf("%d.\n", rValue + gValue + bValue);
    }
    
    

}

void ThreadFabric(int rValue, int gValue, int bValue, int posX, int posY) {
    // remeber threads
    std::thread t1(ColourIn, rValue, gValue, bValue, posX, posY);
    t1.detach();
}

[event_source(native)]
class CSource {
public:
    __event void MyEvent(int rValue, int gValue, int bValue);
};

[event_receiver(native)]
class CReceiver {
public:
    void MyHandler1(int rValue, int gValue, int bValue) {
        printf("MyHandler1 was called with values R:%d G:%d B:%d.\n", rValue,gValue,bValue);
        
        // Calculate position on kanva
        int posX = rand() % 25 + 1;
        int posY = rand() % 25 + 1;
        // Here create a thread
        ThreadFabric(rValue, gValue, bValue, posX, posY);
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
        __raise source->MyEvent(paintBrush.R, paintBrush.G, paintBrush.B);
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
    obraz.newPicture("try4.bmp");

    CReceiver receiver;
    Okienko form;
    CSource* source = form.getSource();
   
    receiver.hookEvent(source);
    Application::Run(% form);
    receiver.unhookEvent(source);
}


