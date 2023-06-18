// Copyright 2023 Arkadia Kowalczyk
#ifndef TRY1_IMAGE_H_
#define TRY1_IMAGE_H_

#include <cstdint>  // for specific size integers
#include <string>

    class picture {
     public:
             int newPicture(std::string nazwa);
             int fillSquare(int x, int y, int rValue, int gValue, int bValue);
             int redraw();

     private:
            std::string nazwa = "try4.bmp";
    };

#endif  // TRY1_IMAGE_H_
