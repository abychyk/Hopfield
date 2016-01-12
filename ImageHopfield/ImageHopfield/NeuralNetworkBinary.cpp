#include "NeuralNetworkBinary.h"
#include <QColor>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <random>

NeuralNetworkBinary::NeuralNetworkBinary(QImage *img) {
    this->img = img;
    pixelMeans = new std::vector<double>();
    weightMatrix = new std::vector<std::vector<double>>();
    globalWeightMatrix = new std::vector<std::vector<double>>();
    imgsMemoryValues = new std::vector<std::vector<double>>();
    imgsMemory = new std::vector<QImage *>();
}

NeuralNetworkBinary::NeuralNetworkBinary() {
    pixelMeans = new std::vector<double>();
    weightMatrix = new std::vector<std::vector<double>>();
    globalWeightMatrix = new std::vector<std::vector<double>>();
    imgsMemoryValues = new std::vector<std::vector<double>>();
    imgsMemory = new std::vector<QImage *>();
}

void NeuralNetworkBinary::educate(QImage *img) {
    this->img = img;
    imgsMemory->push_back(img);
    parseImageToRGB();
    size = (int)pixelMeans->size();
    imgsMemoryValues->push_back(*pixelMeans);
    createWeightMatrix();
    addToGlobalWeights();

    pixelMeans->clear();
    //pixelMap->clear();
    weightMatrix->clear();
}

QImage *NeuralNetworkBinary::recognize(QImage *img) {
    this->img = img;
    parseImageToRGB();
    out = new std::vector<double>(pixelMeans->size(), 0.0);
    std::vector<double> *outPrev = new std::vector<double>(pixelMeans->size(), 0.0);
    std::vector<bool> *diff = new std::vector<bool>(pixelMeans->size(), false);
    do {
        outPrev = new std::vector<double>(*out);
        multiplyWY();
        activation();
        for (int i = 0; i < pixelMeans->size(); i++)
            diff->at(i) = (outPrev->at(i) != out->at(i)) ? true : false;
    } while (std::find(diff->begin(), diff->end(), true) != diff->end());
    int index = -1;
    for (int i = 0; i < imgsMemoryValues->size(); i++) {
        if (imgsMemoryValues->at(i) == *pixelMeans) {
            index = i;
        }
    }
    pixelMeans->clear();
    out->clear();
    if (index == -1)
        return nullptr;
    return imgsMemory->at(index);
}

QImage *NeuralNetworkBinary::recognizeAsync(QImage *img) {
    this->img = img;
    parseImageToRGB();
    out = new std::vector<double>(pixelMeans->size(), 0.0);
    std::vector<double> *outPrev = new std::vector<double>(pixelMeans->size(), 0.0);
    std::vector<bool> *diff = new std::vector<bool>(pixelMeans->size(), false);
    std::vector<double> *inPrev = new std::vector<double>(*pixelMeans);
    multiplyWY();
    activation();
    int indexInner = 0;
    do {
        outPrev = new std::vector<double>(*out);
        double copyValue = pixelMeans->at(indexInner);
        pixelMeans = new std::vector<double>(*inPrev);
        pixelMeans->at(indexInner) = copyValue;
        inPrev = new std::vector<double>(*pixelMeans);
        multiplyWY();
        activation();
        for (int i = 0; i < pixelMeans->size(); i++)
            diff->at(i) = (outPrev->at(i) != out->at(i)) ? true : false;
        if (indexInner < size - 1)
            indexInner++;
        else
            indexInner = 0;
    } while (std::find(diff->begin(), diff->end(), true) != diff->end());
    int index = 0;
    for (int i = 0; i < imgsMemoryValues->size(); i++) {
        if (imgsMemoryValues->at(i) == *pixelMeans) {
            index = i;
        }
    }
    pixelMeans->clear();
    out->clear();
    return imgsMemory->at(index);
}

void NeuralNetworkBinary::multiplyWY() {
    for (int i = 0; i < size; i++) {
        double tmp = 0;
        for (int j = 0; j < size; j++) {
            tmp += globalWeightMatrix->at(i)[j] * pixelMeans->at(j);
        }
        out->at(i) = (tmp);
    }
}

void NeuralNetworkBinary::activation() {
    for (int i = 0; i < size; i++) {
        pixelMeans->at(i) = actFunction(out->at(i));
    }
}

double NeuralNetworkBinary::actFunction(double in) {
    return (in > 0.0) ? 1.0 : -1.0;
}

void NeuralNetworkBinary::parseImageToRGB() {
    double normalizedValue = 128 * 3;
    std::vector<RGBPixelBinary> *pixelMap = new std::vector<RGBPixelBinary>();
    for (int row = 0; row < img->height(); row++) {
        for (int col = 0; col < img->width(); col++) {
            QColor currColor(img->pixel(row, col));
            RGBPixelBinary pixel;
            pixel.r = currColor.red();
            pixel.g = currColor.green();
            pixel.b = currColor.blue();
            pixelMap->push_back(pixel);
        }
    }
    for (auto& elem : *pixelMap) {
        pixelMeans->push_back(((double)elem.r + (double)elem.g + (double)elem.b) / normalizedValue);
    }
    for (auto& elem : *pixelMeans) {
        elem = (elem > 1.0) ? 1.0 : -1.0;
    }
}

void NeuralNetworkBinary::createWeightMatrix() {
    std::vector<double> tmp;
    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size; i++) {
            if (i != j)
                tmp.push_back(pixelMeans->at(i) * pixelMeans->at(j));
            else
                tmp.push_back(0);
        }
        weightMatrix->push_back(tmp);
        tmp.clear();
    }
}

void NeuralNetworkBinary::addToGlobalWeights() {
    if (globalWeightMatrix->size() == 0) {
        std::vector<double> tmp(size, 0.0);
        for (int i = 0; i < size; i++) {
            globalWeightMatrix->push_back(tmp);
        }
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i != j)
                globalWeightMatrix->at(i)[j] += weightMatrix->at(i)[j];
        }
    }
}

QImage *NeuralNetworkBinary::imageNoise(QImage *img) {
    QImage *noisedImage = img;
    int percentage = 15;
    int height = noisedImage->height();
    int width = noisedImage->width();
    int pixelsNumToNoise = (height * width * percentage) / 100;
    std::mt19937 gen(time(0));
    std::mt19937 gen1(time(0));
    std::uniform_int_distribution<> uidHeight(0, height);
    std::uniform_int_distribution<> uidWidth(0, width);
    std::uniform_int_distribution<> uidColor(0, 255);
    for (int i = 0; i < pixelsNumToNoise; i++) {
        noisedImage->setPixel(uidHeight(gen1), uidWidth(gen), qRgb(uidColor(gen), uidColor(gen1), uidColor(gen)));
    }
    return noisedImage;
}

std::vector<std::vector<double>> *NeuralNetworkBinary::getGlobalWeights() {
    return globalWeightMatrix;
}

void NeuralNetworkBinary::setGlobalWeights(std::vector<std::vector<double>> *weights) {
    this->globalWeightMatrix = weights;
}

NeuralNetworkBinary::~NeuralNetworkBinary() {
    delete globalWeightMatrix;
    globalWeightMatrix = nullptr;
    delete weightMatrix;
    weightMatrix = nullptr;
    delete pixelMeans;
    pixelMeans = nullptr;

    delete imgsMemoryValues;
    imgsMemoryValues = nullptr;
    delete imgsMemory;
    imgsMemory = nullptr;
    //delete out;
    //out = nullptr;
    delete globalWeightMatrix;
    globalWeightMatrix = nullptr;
}