#include "MyForm.h"
#include "Image.h"
#include <stdio.h>
#include <thread>
#include <vcclr.h>
#include <windows.h>

using namespace System::Threading;

using namespace System;
using namespace System::Windows::Forms;

ref class MyEventArgs;
ref class Okienko;
ref class ManagedMutex;
void ThreadFabric(int rValue, int gValue, int bValue, int posX, int posY, MyEventArgs^ args);
void ColourIn(int rValue, int gValue, int bValue, int posX, int posY, MyEventArgs^ args);
void Refresh(int posX, int posY, int rValue, int gValue, int bValue, picture obraz, MyEventArgs^ args);

gcroot<Mutex^> mutex = gcnew Mutex();

[event_source(native)]
class CSource {
public:
    __event void MyEvent(MyEventArgs^ args);
};

ref class MyEventArgs : public EventArgs {
public:
    
    Okienko^ okienko = nullptr;
};

public ref class Okienko : try1::MyForm {
    CSource* source = new CSource;

public:
    void DoubleClick_toOverride() override {
        mutex->WaitOne();
            MyEventArgs^ args = gcnew MyEventArgs();
            args->okienko = this;
        mutex->ReleaseMutex();
        __raise source->MyEvent(args);
    }

    void giveColour(int* r, int* g, int* b) {
        *r = paintBrush.R;
        *g = paintBrush.G;
        *b = paintBrush.B;
    }

    CSource* getSource() {
        return source;
    }
};

[event_receiver(native)]
class CReceiver {
public:
    void MyHandler1(MyEventArgs^ args) {
        mutex->WaitOne();
        Okienko^ okienko = args->okienko;
        int rValue, gValue, bValue;
        okienko->giveColour(&rValue, &gValue, &bValue);
        printf("MyHandler1 was called with values R:%d G:%d B:%d.\n", rValue,gValue,bValue);
        
        // Calculate position on kanva
        int posX = rand() % 25 + 1;
        int posY = rand() % 25 + 1;
        // Here create a thread
        ThreadFabric(rValue, gValue, bValue, posX, posY, args);
        mutex->ReleaseMutex();
    }

    void hookEvent(CSource* pSource) {
        __hook(&CSource::MyEvent, pSource, &CReceiver::MyHandler1);
    }
    void unhookEvent(CSource* pSource) {
        __unhook(&CSource::MyEvent, pSource, &CReceiver::MyHandler1);
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





void ThreadFabric(int rValue, int gValue, int bValue, int posX, int posY, MyEventArgs^ args) {
    // remeber threads
    std::thread t1(ColourIn, rValue, gValue, bValue, posX, posY, std::ref(args));
    t1.detach();
}

void ColourIn(int rValue, int gValue, int bValue, int posX, int posY, MyEventArgs^ args) {
    printf("thread was called with value %d.\n", rValue + gValue + bValue);
    picture obraz;
    
    //System::Drawing::Image^ updatedImage; // = System::Drawing::Image::FromFile("C:\\Users\\arkad\\source\\repos\\try1\\try1\\try4.bmp");
    

    int d = 0;
    Refresh(posX, posY, rValue, gValue, bValue, obraz, args);

    while (true) {
        //update canva
        //obraz.fillSquare(posX, posY, rValue, gValue, bValue);
        Refresh(posX, posY, rValue, gValue, bValue, obraz, args);
        posY += 1;
        Refresh(posX, posY, rValue, gValue, bValue, obraz, args);

        d += 2;
        for (int licz = 1; licz < d; licz++, posX++) {
            Refresh(posX, posY, rValue, gValue, bValue, obraz, args);
        }

        for (int licz = 0; licz < d; licz++, posY--) {
            Refresh(posX, posY, rValue, gValue, bValue, obraz, args);
        }
       
        for (int licz = 0; licz < d; licz++, posX--) {
            Refresh(posX, posY, rValue, gValue, bValue, obraz, args);
        }
        for (int licz = 0; licz < d; licz++, posY++) {
            Refresh(posX, posY, rValue, gValue, bValue, obraz, args);
        }
        
        // lower is example that threads run
        printf("%d.\n", rValue + gValue + bValue);
    }
    


}

void Refresh(int posX, int posY, int rValue, int gValue, int bValue, picture obraz, MyEventArgs^ args) {
     
    
 
    String^ path = "C:\\Users\\arkad\\source\\repos\\try1\\try1\\try4.bmp";

    mutex->WaitOne();
    obraz.fillSquare(posX, posY, rValue, gValue, bValue);
    mutex->ReleaseMutex();

    mutex->WaitOne();
       // printf("args = %p\n", args);
        Okienko^ okienko = args->okienko;

        GC::Collect();
        System::Drawing::Image^ updatedImage;
        updatedImage = System::Drawing::Image::FromFile(path);
        okienko->RefreshPicture(updatedImage);
        delete updatedImage;
        

   mutex->ReleaseMutex();

    _sleep(100);

}

//void fillSquare(intposX,int posY,int rValue,int gValue, int bValue, Okienko okienko)