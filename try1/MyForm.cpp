#include "MyForm.h"
#include "Image.h"
#include <stdio.h>
#include <thread>


using namespace System;
using namespace System::Windows::Forms;

ref class MyEventArgs;
ref class Okienko;
void ThreadFabric(int rValue, int gValue, int bValue, int posX, int posY, MyEventArgs^ args);
void ColourIn(int rValue, int gValue, int bValue, int posX, int posY, MyEventArgs^ args);


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
        MyEventArgs^ args = gcnew MyEventArgs();
        args->okienko = this;
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
        Okienko^ okienko = args->okienko;
        int rValue, gValue, bValue;
        okienko->giveColour(&rValue, &gValue, &bValue);
        printf("MyHandler1 was called with values R:%d G:%d B:%d.\n", rValue,gValue,bValue);
        
        // Calculate position on kanva
        int posX = rand() % 25 + 1;
        int posY = rand() % 25 + 1;
        // Here create a thread
        ThreadFabric(rValue, gValue, bValue, posX, posY, args);
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
    Okienko^ okienko = args->okienko;
    System::Drawing::Image^ updatedImage; // = System::Drawing::Image::FromFile("C:\\Users\\arkad\\source\\repos\\try1\\try1\\try4.bmp");
    

    int d = 0;


    while (true) {
        //update canva

        obraz.fillSquare(posX, posY, rValue, gValue, bValue);


        posY += 1;
        obraz.fillSquare(posX, posY, rValue, gValue, bValue);


        d += 2;
        for (int licz = 1; licz <= d; licz++, posX++) {
            //semafor up
            obraz.fillSquare(posX, posY, rValue, gValue, bValue);
            
            //printf("refresh\n");
            //semafor down

            _sleep(100);

        }
        //okienko->RefreshPicture();
        for (int licz = 0; licz <= d; licz++, posY--) {
            obraz.fillSquare(posX, posY, rValue, gValue, bValue);
            //okienko->RefreshPicture();
            //printf("refresh\n");
            _sleep(100);
        }//okienko->RefreshPicture();
        for (int licz = 0; licz <= d; licz++, posX--) {
            obraz.fillSquare(posX, posY, rValue, gValue, bValue);
            //okienko->RefreshPicture();
            //printf("refresh\n");
            _sleep(100);
        }
        //okienko->RefreshPicture();
        for (int licz = 0; licz <= d; licz++, posY++) {
            obraz.fillSquare(posX, posY, rValue, gValue, bValue);
            //okienko->RefreshPicture();
            //printf("refresh\n");
            _sleep(100);
        }
        updatedImage = System::Drawing::Image::FromFile("C:\\Users\\arkad\\source\\repos\\try1\\try1\\try4.bmp");
        okienko->RefreshPicture(updatedImage);
        delete updatedImage;

        // lower is example that threads run
        printf("%d.\n", rValue + gValue + bValue);
    }
    


}

//void fillSquare(intposX,int posY,int rValue,int gValue, int bValue, Okienko okienko)