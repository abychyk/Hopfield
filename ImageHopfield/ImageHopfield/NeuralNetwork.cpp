#include "NeuralNetwork.h"
#include <QColor>
#include <cmath>
#include <algorithm>
#include <chrono>

NeuralNetwork::NeuralNetwork(QImage *img) {
    this->img = img;
    //pixelMap = new std::vector<RGBPixel>();
    pixelMeans = new std::vector<double>();
    weightMatrix = new std::vector<std::vector<double>>();
    globalWeightMatrix = new std::vector<std::vector<double>>();
    imgsMemoryValues = new std::vector<std::vector<double>>();
    imgsMemory = new std::vector<QImage *>();
    //out = new std::vector<double>(pixelMeans->size(), 0.0);
}

NeuralNetwork::NeuralNetwork() {
    //pixelMap = new std::vector<RGBPixel>();
    pixelMeans = new std::vector<double>();
    weightMatrix = new std::vector<std::vector<double>>();
    globalWeightMatrix = new std::vector<std::vector<double>>();
    imgsMemoryValues = new std::vector<std::vector<double>>();
    imgsMemory = new std::vector<QImage *>();
    //out = new std::vector <double>();
}

void NeuralNetwork::educate(QImage *img) {
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

QImage *NeuralNetwork::recognize(QImage *img) {  
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
    int index = 0;
    for (int i = 0; i < imgsMemoryValues->size(); i++) {
        if (imgsMemoryValues->at(i) == *pixelMeans) {
            index = i;
        }
    }
    return imgsMemory->at(index);
}

QImage *NeuralNetwork::recognizeAsync(QImage *img) {
    this->img = img;
    parseImageToRGB();
    out = new std::vector<double>(pixelMeans->size(), 0.0);
    std::vector<double> *outPrev = new std::vector<double>(pixelMeans->size(), 0.0);
    std::vector<bool> *diff = new std::vector<bool>(pixelMeans->size(), false);
    //outPrev = new std::vector<double>(*out);
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
        /*outPrev = new std::vector<double>(*out);
        multiplyWY();
        activation();*/

        for (int i = 0; i < pixelMeans->size(); i++)
            diff->at(i) = (outPrev->at(i) != out->at(i)) ? true : false;
        if (indexInner < size - 1)
            indexInner++;
        else
            indexInner = 0;
    } while (std::find(diff->begin(), diff->end(), true) != diff->end());
    int index = 0;
    for (int i = 0; i < imgsMemoryValues->size(); i++) {
        if (imgsMemoryValues->at(i) == *out) {
            index = i;
        }
    }
    return imgsMemory->at(index);
}

void NeuralNetwork::multiplyWY() {
    double max = 0.0;
    //for (int i = 0; i < globalWeightMatrix->size(); i++) {
    for (int i = 0; i < size; i++) {
        double tmp = *std::max_element(globalWeightMatrix->at(i).begin(), globalWeightMatrix->at(i).end());;
        if (max < tmp)
            max = tmp;
    }
    //for (int i = 0; i < globalWeightMatrix->size(); i++) {
    for (int i = 0; i < size; i++) {
        double tmp = 0;
        //for (int j = 0; j < globalWeightMatrix->size(); j++) {
        for (int j = 0; j < size; j++) {
            tmp += globalWeightMatrix->at(i)[j] / max * pixelMeans->at(j);
        }
        out->at(i) = (tmp);
    }
}

void NeuralNetwork::activation() {
    //for (int i = 0; i < out->size(); i++) {
    for (int i = 0; i < size; i++) {
        pixelMeans->at(i) = actFunction(out->at(i));
    }
}

double NeuralNetwork::actFunction(double in) {
    double alpha = 0.004;
    double res = 1.0 / (1.0 + std::exp(-alpha * in));
    return res;
}

void NeuralNetwork::parseImageToRGB() {
    double normalizedValue = 256;
    //added here cause it is never used outside
    std::vector<RGBPixel> *pixelMap = new std::vector<RGBPixel>();
    for (int row = 0; row < img->height(); row++) {
        for (int col = 0; col < img->width(); col++) {
            QColor currColor(img->pixel(row, col));
            RGBPixel pixel;
            pixel.r = currColor.red();
            pixel.g = currColor.green();
            pixel.b = currColor.blue();
            pixelMap->push_back(pixel);
        }
    }
    for (auto& elem : *pixelMap) {
        pixelMeans->push_back(((double)elem.r + (double)elem.g + (double)elem.b) / normalizedValue);
    }
}

void NeuralNetwork::createWeightMatrix() {
    //int size = (int)pixelMeans->size();
    std::vector<double> tmp;
    
    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size; i++) {
            if (i != j)
                tmp.push_back(pixelMeans->at(i) * pixelMeans->at(j));
            else
                tmp.push_back(0);
        }
        weightMatrix->push_back(tmp);
        //trying to modify to the threads (adding by index to make strong consistency of writing operation)
        //weightMatrix->at(j) = tmp;
        tmp.clear();
    }
    /*const int numberOfThreads = 4;
    int divideSize[numberOfThreads];
    if (pixelMeans->size() % numberOfThreads == 0)
        for (int i = 0; i < numberOfThreads; i++)
            divideSize[i] = pixelMeans->size() / numberOfThreads;
    else {
        for (int i = 0; i < numberOfThreads - 1; i++)
            divideSize[i] = pixelMeans->size() / numberOfThreads;
        divideSize[3] = pixelMeans->size() - divideSize[0];
    }
    std::vector<WeightMatrixThread *> pool;
    for (int i = 0; i < numberOfThreads; i++) {
        if (divideSize[3] != divideSize[0]) {
            if (i == numberOfThreads - 1) {
                WeightMatrixThread *thread = new WeightMatrixThread(weightMatrix, pixelMeans, i * divideSize[0], ((i + 1) * divideSize[0]) + (divideSize[i] - divideSize[0]));
                pool.push_back(thread);
                thread->start();
            } else {
                WeightMatrixThread *thread = new WeightMatrixThread(weightMatrix, pixelMeans, i * divideSize[i], (i + 1) * divideSize[i]);
                pool.push_back(thread);
                thread->start();
            }
        } else {
            WeightMatrixThread *thread = new WeightMatrixThread(weightMatrix, pixelMeans, i * divideSize[i], (i + 1) * divideSize[i]);
            pool.push_back(thread);
            thread->start();
        }
    }
    for (auto thread : pool) {
        thread->wait();
    }*/
}

void NeuralNetwork::addToGlobalWeights() {
    //int size = (int)weightMatrix->size();
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

std::vector<std::vector<double>> *NeuralNetwork::getGlobalWeights() {
    return globalWeightMatrix;
}

void NeuralNetwork::setGlobalWeights(std::vector<std::vector<double>> *weights) {
    this->globalWeightMatrix = weights;
}

NeuralNetwork::~NeuralNetwork() {
    delete globalWeightMatrix;
    globalWeightMatrix = nullptr;
    delete weightMatrix;
    weightMatrix = nullptr;
    //delete pixelMap;
    //pixelMap = nullptr;
    delete pixelMeans;
    pixelMeans = nullptr;
    
    delete imgsMemoryValues;
    imgsMemoryValues = nullptr;
    delete imgsMemory;
    imgsMemory = nullptr;
    delete out;
    out = nullptr;
    delete globalWeightMatrix;
    globalWeightMatrix = nullptr;
}