#ifndef IMAGEHOPFIELD_H
#define IMAGEHOPFIELD_H

#include <QtWidgets/QMainWindow>
#include <QMessageBox>

#include "ui_imagehopfield.h"
#include "NeuralNetworkBinary.h"

class ImageHopfield : public QMainWindow
{
    Q_OBJECT

public:
    ImageHopfield(QWidget *parent = 0);
    ~ImageHopfield();

private:
    Ui::ImageHopfieldClass ui;
    //init qmenubar actions
    void createActions();
    //about message
    QMessageBox *msgBox;
    //Hopfield neural network pointer
    NeuralNetworkBinary *neuralNetwork;
    //NeuralNetworkBinary *nnB;
    //loaded image
    QImage *img;
    //weights
    std::vector<std::vector<double>> *weights;
    //is image opened
    bool isOpened;
    //is image is in a memory
    bool isRecognizable;
    //error message window
    void errorMessage(QString textMessage);
    //info message window
    void infoMessage(QString textMessage);
    //max height of image
    int maxHeight;
    //max widht of image
    int maxWidth;
private slots:
    void pExit();          //program exit;
    void fNew();           //file new
    void pAbout();         //program about
    void aOpenImg();       //action open image
    void aEducate();       //action educate()
    void aRecognize();     //action recognize synchronized
    void aRecognizeAsync();//action recognize asynchronized
    void fLoadDefault();   //loads default images and educates network
    void aNoise();         //noise an image
    void pHelp();          //help to the program
};

#endif // IMAGEHOPFIELD_H
