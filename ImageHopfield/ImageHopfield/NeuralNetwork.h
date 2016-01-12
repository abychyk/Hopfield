#pragma once
#include <QImage>
#include <vector>

struct RGBPixel {
    int r;
    int g;
    int b;
    RGBPixel() {
        r = 0;
        g = 0;
        b = 0;
    }
};

class NeuralNetwork
{
public:
    NeuralNetwork();
    NeuralNetwork(QImage *img);

    void educate(QImage *img);
    QImage *recognize(QImage *img);
    QImage *recognizeAsync(QImage *img);
    std::vector<std::vector<double>> *getGlobalWeights();
    void setGlobalWeights(std::vector<std::vector<double>> *weights);

    ~NeuralNetwork();
private: 
    QImage *img;
    //std::vector<RGBPixel> *pixelMap;
    std::vector<double> *pixelMeans;
    std::vector<std::vector<double>> *imgsMemoryValues;
    std::vector<QImage *> *imgsMemory;
    std::vector<double> *out;
    std::vector<std::vector<double>> *weightMatrix;
    std::vector<std::vector<double>> *globalWeightMatrix;
    int size;

    void parseImageToRGB();
    void createWeightMatrix();
    void addToGlobalWeights();
    void multiplyWY();
    void activation();
    double actFunction(double in);
};

