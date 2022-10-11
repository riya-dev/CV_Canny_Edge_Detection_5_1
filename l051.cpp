// cd project5
// cd part1
// g++ -std=c++11 -o l051  -Wall l051.cpp
// ./l051

#include <iostream>
#include <fstream>
#include <sstream>

int width;
int height;

int** maskx(int** grayscale) {
    int** maskX;
    maskX = new int* [height];
    for (int i = 0; i < height; i++)
        maskX[i] = new int[width];

    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            maskX[i][j] = 0;

    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            int a = grayscale[i - 1][j - 1] * -1;
            int b = grayscale[i - 1][j] * 0;
            int c = grayscale[i - 1][j + 1] * 1;

            int d = grayscale[i][j - 1] * -2;
            int e = grayscale[i][j] * 0;
            int f = grayscale[i][j + 1] * 2;

            int g = grayscale[i + 1][j - 1] * -1;
            int h = grayscale[i + 1][j] * 0;
            int k = grayscale[i + 1][j + 1] * 1;

            maskX[i][j] = a + b + c + d + e + f + g + h + k;
        }
    }
    return maskX;
}

int** masky(int** grayscale) {
    int** maskY;
    maskY = new int* [height];
    for (int i = 0; i < height; i++)
        maskY[i] = new int[width];

    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            maskY[i][j] = 0;

    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            int a = grayscale[i - 1][j - 1] * -1;
            int b = grayscale[i][j - 1] * 0;
            int c = grayscale[i + 1][j - 1] * 1;

            int d = grayscale[i - 1][j] * -2;
            int e = grayscale[i][j] * 0;
            int f = grayscale[i + 1][j] * 2;

            int g = grayscale[i - 1][j + 1] * -1;
            int h = grayscale[i][j + 1] * 0;
            int k = grayscale[i + 1][j + 1] * 1;

            maskY[i][j] = a + b + c + d + e + f + g + h + k;
        }
    }
    return maskY;
}

void part1() {
    std::ifstream og("image.ppm");

    std::string next;
    if (og.is_open()) {
        og >> next;
        og >> next;
        width = std::stoi(next);
        og >> next;
        height = std::stoi(next);
        og >> next;
        int maxcolor = std::stoi(next);

        int** ogarray;
        ogarray = new int* [height];
        for (int i = 0; i < height; i++)
            ogarray[i] = new int[width];

        std::ofstream imageg;
        imageg.open("imageg.ppm");
        imageg << "P3 " << width << " " << height << " " << maxcolor << "\n";
        // make array
        int** arrayg;
        arrayg = new int* [height];
        for (int i = 0; i < height; i++)
            arrayg[i] = new int[width];

        std::ofstream imagem;
        imagem.open("imagem.ppm");
        imagem << "P3 " << width << " " << height << " 255\n";
        // make array
        int** arraym;
        arraym = new int* [height];
        for (int i = 0; i < height; i++)
            arraym[i] = new int[width];

        int r;
        int g;
        int b;
        int intensity = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                og >> next;
                r = std::stoi(next);
                og >> next;
                g = std::stoi(next);
                og >> next;
                b = std::stoi(next);
                intensity = (int)((r + g + b) / 3);
                arrayg[i][j] = intensity; //intensity
            }
        }
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j)
                imageg << arrayg[i][j] << " " << arrayg[i][j] << " " << arrayg[i][j] << " ";
            imageg << std::endl;
        }
        imageg << "\n";
        imageg.close();

        int** maskX;
        maskX = new int* [height];
        for (int i = 0; i < height; i++)
            maskX[i] = new int[width];

        int** maskY;
        maskY = new int* [height];
        for (int i = 0; i < height; i++)
            maskY[i] = new int[width];

        maskX = maskx(arrayg);
        maskY = masky(arrayg);

        int** magnitude;
        magnitude = new int* [height];
        for (int i = 0; i < height; i++)
            magnitude[i] = new int[width];

        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                magnitude[i][j] = (int)(sqrt((maskX[i][j] * maskX[i][j]) + (maskY[i][j] * maskY[i][j])));

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (magnitude[i][j] > 100)
                    imagem << 255 << " " << 255 << " " << 255 << " ";
                else
                    imagem << 0 << " " << 0 << " " << 0 << " ";
            }
            imagem << std::endl;
        }
        imagem << "\n";
        imagem.close();

        og.close();
    }
    else
        std::cout << "Unable to open file";
}

int main() {
    part1();
}