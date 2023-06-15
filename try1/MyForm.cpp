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
void Paint(MyEventArgs^ args);
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
    int jestMalarz = 0;
};

public ref class Okienko : try1::MyForm {
    CSource* source = new CSource;

public:
    void DoubleClick_toOverride() override {
        //printf("mutex tbc ");
        mutex->WaitOne();
        //printf("mutex c ");
            MyEventArgs^ args = gcnew MyEventArgs();
            args->okienko = this;
            //printf("mutex tb relesed ");
        mutex->ReleaseMutex();
        //printf("mutex relesed ");
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
        //Okienko^ okienko = args->okienko;
        int rValue, gValue, bValue;
        args->okienko->giveColour(&rValue, &gValue, &bValue);
        //printf("HANDLER: args = %p\n", args->okienko);
        //printf("MyHandler1 was called with values R:%d G:%d B:%d.\n", rValue,gValue,bValue);
        //printf("mutex relesed HANDLER");
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










[STAThread]


int main(cli::array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    picture obraz;
    obraz.newPicture("C:\\Users\\arkad\\Source\\Repos\\camonday\\KreatorWzorowClean\\try1\\try4.bmp");

    CReceiver receiver;
    Okienko form;
    CSource* source = form.getSource();
   
    receiver.hookEvent(source);
    Application::Run(% form);
    receiver.unhookEvent(source);

   
   
}





void ThreadFabric(int rValue, int gValue, int bValue, int posX, int posY, MyEventArgs^ args) {
    // remeber threads
    //printf("TF1: args = %p\n", args);
    std::thread t1(ColourIn, rValue, gValue, bValue, posX, posY, std::ref(args));
    //printf("TF2: args = %p\n", args);
    t1.detach();     

    if(args->jestMalarz != 1){
        printf("%d", args->jestMalarz);
        std::thread t2(Paint, std::ref(args));
        t2.join(); // IMPORTANT: detach makes errors, need to do join
        args->jestMalarz = 1;
        printf("%d", args->jestMalarz);
    }
        
}

void ColourIn(int rValue, int gValue, int bValue, int posX, int posY, MyEventArgs^ args) {
    printf("thread was called with value %d.\n", rValue + gValue + bValue);
    //printf("Colorin: args = %p\n", args);
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
        //args->okienko->RefreshPicture(System::Drawing::Image::FromFile("try4.bmp"));
    }
    


}

void Paint(MyEventArgs^ args)
{
        
    //while (true) {
        // Wait for 1 seconds
        //std::this_thread::sleep_for(std::chrono::seconds(10));
        _sleep(100);

        // Check if the mutex is free
       printf("\npaint\n");
       // mutex->WaitOne();
            // Mutex is free, perform refresh
           //args->okienko->RefreshPicture(System::Drawing::Image::FromFile("C:\\Users\\arkad\\Source\\Repos\\camonday\\KreatorWzorowClean\\try1\\try4.bmp"));

            // Release the mutex
       // mutex->ReleaseMutex();
        
    //}
}

void Refresh(int posX, int posY, int rValue, int gValue, int bValue, picture obraz, MyEventArgs^ args) {
     
    
  //  printf("REFRESH1: args = %p\n", args);
   // String^ path = "try4.bmp";
   // printf("1 ");
    mutex->WaitOne();
   // printf("2 ");
    obraz.fillSquare(posX, posY, rValue, gValue, bValue);
   // printf("3 ");
    mutex->ReleaseMutex();
    //printf("4 ");
    //mutex->WaitOne();
    //printf("5 ");
       // 

        //Okienko^ okienko = args->okienko;

        //GC::Collect();
        //System::Drawing::Image^ updatedImage;
        //printf("6 ");
       // updatedImage = System::Drawing::Image::FromFile(path); // this line gives errorswhen fillSqure is not in mutexes
        //printf("7 ");
       // args->okienko->RefreshPicture(updatedImage);
       
        //delete updatedImage;
        

  // mutex->ReleaseMutex();
   //_sleep(100000);
    _sleep(100);

}

//void fillSquare(intposX,int posY,int rValue,int gValue, int bValue, Okienko okienko)