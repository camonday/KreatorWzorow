#include <cstdint> // for specific size integers
#include <fstream> // for file handling
#include "Image.h" // my header


using namespace std;


class picture {
	Pixel obraz[512][512];
	Pixel wzor[512][512];
public: int newPicture(string nazwa) {

		blkPixel.blue = 0;
		blkPixel.green = 0;
		blkPixel.red = 0;

		for (int i = 0; i < bmpInfoHeader.width; i++) {
			for (int j = 0; j < bmpInfoHeader.height; j++) {
				picture::obraz[i][j] = whitePixel;
			}
		}

		for (int i = 0; i < bmpInfoHeader.width; i++) {
			for (int j = 0; j < bmpInfoHeader.height; j += 5) {
				picture::obraz[i][j] = blkPixel;
			}
		}


		ofstream fout(nazwa, ios::binary);

		fout.write((char*)&bmpHeader, 14);
		fout.write((char*)&bmpInfoHeader, 40);

		// writing pixel data
		for (int i = 0; i < bmpInfoHeader.width; i++) {
			for (int j = 0; j < bmpInfoHeader.height; j++)
				fout.write((char*)&obraz[i][j], 3);
		}
		fout.close();

		return 0;
	}

	int main(int argc, char* argv[]) { 
		newPicture("test.bmp");
		return 0;
	}
};



