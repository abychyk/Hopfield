#include <QFileDialog>
#include <QTextStream>
#include <QDesktopServices>
#include <QPaintDevice>
#include "imagehopfield.h"

ImageHopfield::ImageHopfield(QWidget *parent) : QMainWindow(parent) {
    isOpened = false;
    isRecognizable = false;
    ui.setupUi(this);
    createActions();
    neuralNetwork = new NeuralNetworkBinary();
    weights = new std::vector<std::vector<double>>();
    img = nullptr;
    msgBox = nullptr;
    maxWidth = 0;
    maxHeight = 0;
}

void ImageHopfield::createActions() {
    connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(pExit()));
    connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(fNew()));
    connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(pAbout()));
    connect(ui.actionOpen_Image, SIGNAL(triggered()), this, SLOT(aOpenImg()));
    connect(ui.actionEducate, SIGNAL(triggered()), this, SLOT(aEducate()));
    connect(ui.actionRecognize, SIGNAL(triggered()), this, SLOT(aRecognize()));
    connect(ui.openImageButton, SIGNAL(clicked()), this, SLOT(aOpenImg()));
    connect(ui.educateButton, SIGNAL(clicked()), this, SLOT(aEducate()));
    connect(ui.recognizeButton, SIGNAL(clicked()), this, SLOT(aRecognize()));
    connect(ui.actionDefault_images, SIGNAL(triggered()), this, SLOT(fLoadDefault()));
    connect(ui.actionRecognize_Async, SIGNAL(triggered()), this, SLOT(aRecognizeAsync()));
    connect(ui.actionNoise, SIGNAL(triggered()), this, SLOT(aNoise()));
    connect(ui.actionView_Help, SIGNAL(triggered()), this, SLOT(pHelp()));
}

void ImageHopfield::pExit() {
    ImageHopfield::close();
}

void ImageHopfield::pAbout() {
    msgBox = new QMessageBox();
    msgBox->setWindowTitle(tr("Info"));
    msgBox->setText(tr("This program was developed by <strong>Alex Bychyk</strong>."));
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setIcon(QMessageBox::Question);
    msgBox->exec();
}

void ImageHopfield::fNew() {
    this->img = nullptr;
    neuralNetwork = new NeuralNetworkBinary();
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui.inputImageGraphicsView->setScene(scene);
    ui.outputImageGraphicsView->setScene(scene);
    maxWidth = 0;
    maxHeight = 0;
}

void ImageHopfield::aNoise() {
    if (isOpened) {
        this->img = neuralNetwork->imageNoise(img);
        QGraphicsScene *scene = new QGraphicsScene(this);
        ui.inputImageGraphicsView->setScene(scene);
        scene->addPixmap(QPixmap::fromImage(*img));
        ui.inputImageGraphicsView->setScene(scene);
    } else {
        errorMessage(tr("You have not opened any image for noising!"));
    }
}

void ImageHopfield::aOpenImg() {
    QString currentFilter = "PNG (*.png)";
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Open Image File",
        QDir::rootPath(),
        tr("JPG (*.jpg *.jpeg);;PNG (*.png)"),
        &currentFilter);
    img = new QImage(filePath);
    if (img->width() < ui.inputImageGraphicsView->width() && img->height() < ui.inputImageGraphicsView->height() && maxHeight == 0 && maxWidth == 0) {
        QGraphicsScene *scene = new QGraphicsScene(this);
        ui.inputImageGraphicsView->setScene(scene);
        scene->addPixmap(QPixmap::fromImage(*img));
        ui.inputImageGraphicsView->setScene(scene);
        maxWidth = img->width();
        maxHeight = img->height();
        isOpened = true;
    } else if (img->width() == maxWidth && img->height() == maxHeight) {
        QGraphicsScene *scene = new QGraphicsScene(this);
        ui.inputImageGraphicsView->setScene(scene);
        scene->addPixmap(QPixmap::fromImage(*img));
        ui.inputImageGraphicsView->setScene(scene);
        isOpened = true;
    } else {
        if (maxHeight == 0 && maxWidth == 0) {
            QString msgStr = "Too large image!<br>Max width = " + QString::number(ui.inputImageGraphicsView->width()) +
                "<br>Max heigth = " + QString::number(ui.inputImageGraphicsView->height());
            errorMessage(msgStr);
        } else {
            QString msgStr = "Incorrect size of an image!<br>Needed width = " + QString::number(maxWidth) +
                "<br>Loaded image width = " + QString::number(img->width()) +
                "<br>Needed heigth = " + QString::number(maxHeight) +
                "<br>Loaded image height = " + QString::number(img->height());
            errorMessage(msgStr);
        }
        delete img;
        img = nullptr;
        QGraphicsScene *scene = new QGraphicsScene(this);
        ui.inputImageGraphicsView->setScene(scene);
        isOpened = false;
    }
}

void ImageHopfield::aEducate() {
    if (isOpened) {
        neuralNetwork->educate(img);
        isRecognizable = true;
    }
    else {
        errorMessage(tr("You have not opened any image for work!"));
    }
}

void ImageHopfield::aRecognize() {
    if (isOpened) {
        QImage *recognizedImg = neuralNetwork->recognize(img);
        if (recognizedImg != nullptr) {
            QGraphicsScene *scene = new QGraphicsScene(this);
            ui.outputImageGraphicsView->setScene(scene);
            scene->addPixmap(QPixmap::fromImage(*recognizedImg));
            //scene->addPixmap(QPixmap::fromImage(*neuralNetwork->recognize(img)));
            ui.outputImageGraphicsView->setScene(scene);
        } else {
            infoMessage(tr("The image is not recognized!"));
        }
    } else {
        if (!isOpened)
            errorMessage(tr("You have not opened any image for work!"));
        else if (!isRecognizable)
            errorMessage(tr("The memory is empty!<br>Educate neural network first!"));
    }
}

void ImageHopfield::aRecognizeAsync() {
    if (isOpened) {
        QImage *recognizedImg = neuralNetwork->recognizeAsync(img);
        if (recognizedImg != nullptr) {
            QGraphicsScene *scene = new QGraphicsScene(this);
            ui.outputImageGraphicsView->setScene(scene);
            scene->addPixmap(QPixmap::fromImage(*recognizedImg));
            ui.outputImageGraphicsView->setScene(scene);
        } else {
            infoMessage(tr("The image is not recognized!"));
        }
    } else {
    if (!isOpened)
        errorMessage(tr("You have not opened any image for work!"));
    else if (!isRecognizable)
        errorMessage(tr("The memory is empty!<br>Educate neural network first!"));
    }
}

void ImageHopfield::fLoadDefault() {
    QString path = QDir::currentPath() + tr("/Default Images/");
    QDir imgDir(path);
    QStringList filter;
    filter << "*.jpg" << "*.png" << "*.jpeg";
    QFileInfoList fileList = imgDir.entryInfoList(filter, QDir::Files);
    for (int i = 0; i < fileList.size(); i++) {
        QString filePath = fileList[i].absoluteFilePath();
        img = new QImage(filePath);
        if (i == 0) {
            maxWidth = img->width();
            maxHeight = img->height();
        }
        neuralNetwork->educate(img);
    }
    isRecognizable = true;
    img = nullptr;
}

void ImageHopfield::pHelp() {
    QString path = QDir::currentPath() + tr("/Doc/Hopfield.pdf");
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

void ImageHopfield::errorMessage(QString textMessage) {
    msgBox = new QMessageBox();
    msgBox->setWindowTitle(tr("Error"));
    QString msgStr = textMessage;
    msgBox->setText(msgStr);
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setIcon(QMessageBox::Critical);
    msgBox->exec();
}

void ImageHopfield::infoMessage(QString textMessage) {
    msgBox = new QMessageBox();
    msgBox->setWindowTitle(tr("Info"));
    QString msgStr = textMessage;
    msgBox->setText(msgStr);
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setIcon(QMessageBox::Information);
    msgBox->exec();
}

ImageHopfield::~ImageHopfield() {
    delete msgBox;
    msgBox = nullptr;
    delete neuralNetwork;
    neuralNetwork = nullptr;
    delete img;
    img = nullptr;
    delete weights;
    weights = nullptr;
}
