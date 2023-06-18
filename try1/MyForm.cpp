//  Copyright [2023] <Arkadia Kowalczyk>

#include "MyForm.h"
#include "Image.h"
#include <stdio.h>
#include <windows.h>
#include <vcclr.h>
#include <thread>   // NOLINT(build/c++11)

ref class MyEventArgs;
ref class Okienko;
ref class ManagedMutex;
void ThreadFabric(int rValue, int gValue, int bValue,
                  int posX, int posY, MyEventArgs^ args);
void ColourIn(int rValue, int gValue, int bValue,
              int posX, int posY, MyEventArgs^ args);
void Paint(MyEventArgs^ args);
void Refresh(int posX, int posY,
             int rValue, int gValue, int bValue,
             picture obraz, MyEventArgs^ args);

gcroot<System::Threading::Mutex^> mutex = gcnew System::Threading::Mutex();

[event_source(native)]
class CSource {
 public:
    __event void MyEvent(MyEventArgs^ args);
};

ref class MyEventArgs : public System::EventArgs {
 public:
    Okienko^ okienko = nullptr;
    int jestMalarz = 0;
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
        int rValue, gValue, bValue;
        args->okienko->giveColour(&rValue, &gValue, &bValue);
        mutex->ReleaseMutex();
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


[System::STAThread]

int main(cli::array<System::String^>^ args) {
    System::Windows::Forms::Application::EnableVisualStyles();
    System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);

    picture obraz;
    obraz.newPicture("try4.bmp");

    CReceiver receiver;
    Okienko form;
    CSource* source = form.getSource();

    receiver.hookEvent(source);
    System::Windows::Forms::Application::Run(% form);
    receiver.unhookEvent(source);
}


void ThreadFabric(int rValue, int gValue, int bValue,
                  int posX, int posY, MyEventArgs^ args) {
    std::thread t1(ColourIn, rValue, gValue, bValue,
                   posX, posY, std::ref(args));
    t1.detach();

    if (args->jestMalarz != 1) {
        printf("%d", args->jestMalarz);
        std::thread t2(Paint, std::ref(args));
        t2.join();  // IMPORTANT: detach makes errors, need to do join
        args->jestMalarz = 1;  // Does not work :(
        printf("%d", args->jestMalarz);
    }
}

void ColourIn(int rValue, int gValue, int bValue,
              int posX, int posY, MyEventArgs^ args) {
    printf("thread was called with value %d.\n", rValue + gValue + bValue);
    picture obraz;

    int d = 0;
    Refresh(posX, posY, rValue, gValue, bValue, obraz, args);

    while (true) {
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

void Paint(MyEventArgs^ args) {
     // while (true) {
       // Wait for 10 seconds
       // std::this_thread::sleep_for(std::chrono::seconds(10));  
       // --makes gui inacessble

       // Check if the mutex is free
       mutex->WaitOne();
       printf("\npaint\n");
       // Mutex is free, perform refresh
       // args->okienko->RefreshPicture(System::Drawing::Image::FromFile("try4.bmp"));
       // Above makes bmp file to not refresh

       // Release the mutex
       mutex->ReleaseMutex();
     //}
}

void Refresh(int posX, int posY,
             int rValue, int gValue, int bValue,
             picture obraz, MyEventArgs^ args) {
    mutex->WaitOne();
    obraz.fillSquare(posX, posY, rValue, gValue, bValue);
    mutex->ReleaseMutex();

    _sleep(100);
}
