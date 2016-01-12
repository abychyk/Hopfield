/********************************************************************************
** Form generated from reading UI file 'imagehopfield.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEHOPFIELD_H
#define UI_IMAGEHOPFIELD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageHopfieldClass
{
public:
    QAction *actionExit;
    QAction *actionNew;
    QAction *actionAbout;
    QAction *actionView_Help;
    QAction *actionOpen_Image;
    QAction *actionEducate;
    QAction *actionRecognize;
    QAction *actionDefault_images;
    QAction *actionRecognize_Async;
    QAction *actionNoise;
    QWidget *centralWidget;
    QPushButton *openImageButton;
    QPushButton *educateButton;
    QPushButton *recognizeButton;
    QGraphicsView *inputImageGraphicsView;
    QLabel *inputImageLabel;
    QGraphicsView *outputImageGraphicsView;
    QLabel *outputImageLabel;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menuHelp;
    QMenu *menuEdit;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *ImageHopfieldClass)
    {
        if (ImageHopfieldClass->objectName().isEmpty())
            ImageHopfieldClass->setObjectName(QStringLiteral("ImageHopfieldClass"));
        ImageHopfieldClass->resize(1191, 946);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ImageHopfieldClass->sizePolicy().hasHeightForWidth());
        ImageHopfieldClass->setSizePolicy(sizePolicy);
        actionExit = new QAction(ImageHopfieldClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Images/Resources/Exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon);
        actionNew = new QAction(ImageHopfieldClass);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Images/Resources/New_file.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon1);
        actionNew->setShortcutContext(Qt::WindowShortcut);
        actionAbout = new QAction(ImageHopfieldClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Images/Resources/About.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon2);
        actionView_Help = new QAction(ImageHopfieldClass);
        actionView_Help->setObjectName(QStringLiteral("actionView_Help"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Images/Resources/Help.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionView_Help->setIcon(icon3);
        actionOpen_Image = new QAction(ImageHopfieldClass);
        actionOpen_Image->setObjectName(QStringLiteral("actionOpen_Image"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Images/Resources/Open Image.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen_Image->setIcon(icon4);
        actionEducate = new QAction(ImageHopfieldClass);
        actionEducate->setObjectName(QStringLiteral("actionEducate"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/Images/Resources/Educate.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEducate->setIcon(icon5);
        actionRecognize = new QAction(ImageHopfieldClass);
        actionRecognize->setObjectName(QStringLiteral("actionRecognize"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/Images/Resources/Synchronized.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRecognize->setIcon(icon6);
        actionDefault_images = new QAction(ImageHopfieldClass);
        actionDefault_images->setObjectName(QStringLiteral("actionDefault_images"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/Images/Resources/Load default.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDefault_images->setIcon(icon7);
        actionRecognize_Async = new QAction(ImageHopfieldClass);
        actionRecognize_Async->setObjectName(QStringLiteral("actionRecognize_Async"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/Images/Resources/Recognize.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRecognize_Async->setIcon(icon8);
        actionNoise = new QAction(ImageHopfieldClass);
        actionNoise->setObjectName(QStringLiteral("actionNoise"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/Images/Resources/sound-volume-wave-acoustics-128.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNoise->setIcon(icon9);
        centralWidget = new QWidget(ImageHopfieldClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        openImageButton = new QPushButton(centralWidget);
        openImageButton->setObjectName(QStringLiteral("openImageButton"));
        openImageButton->setGeometry(QRect(510, 350, 171, 51));
        educateButton = new QPushButton(centralWidget);
        educateButton->setObjectName(QStringLiteral("educateButton"));
        educateButton->setEnabled(true);
        educateButton->setGeometry(QRect(530, 450, 131, 51));
        educateButton->setAutoDefault(false);
        educateButton->setFlat(false);
        recognizeButton = new QPushButton(centralWidget);
        recognizeButton->setObjectName(QStringLiteral("recognizeButton"));
        recognizeButton->setGeometry(QRect(510, 560, 171, 51));
        inputImageGraphicsView = new QGraphicsView(centralWidget);
        inputImageGraphicsView->setObjectName(QStringLiteral("inputImageGraphicsView"));
        inputImageGraphicsView->setGeometry(QRect(20, 70, 471, 781));
        inputImageLabel = new QLabel(centralWidget);
        inputImageLabel->setObjectName(QStringLiteral("inputImageLabel"));
        inputImageLabel->setGeometry(QRect(170, 20, 181, 31));
        QFont font;
        font.setPointSize(10);
        inputImageLabel->setFont(font);
        outputImageGraphicsView = new QGraphicsView(centralWidget);
        outputImageGraphicsView->setObjectName(QStringLiteral("outputImageGraphicsView"));
        outputImageGraphicsView->setGeometry(QRect(700, 70, 471, 781));
        outputImageLabel = new QLabel(centralWidget);
        outputImageLabel->setObjectName(QStringLiteral("outputImageLabel"));
        outputImageLabel->setGeometry(QRect(860, 20, 191, 31));
        outputImageLabel->setFont(font);
        ImageHopfieldClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ImageHopfieldClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1191, 31));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        ImageHopfieldClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ImageHopfieldClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ImageHopfieldClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menu->addAction(actionNew);
        menu->addSeparator();
        menu->addAction(actionExit);
        menuHelp->addAction(actionView_Help);
        menuHelp->addAction(actionAbout);
        menuEdit->addAction(actionOpen_Image);
        menuEdit->addAction(actionEducate);
        menuEdit->addAction(actionRecognize);
        menuEdit->addAction(actionRecognize_Async);
        menuEdit->addSeparator();
        menuEdit->addAction(actionDefault_images);
        menuEdit->addAction(actionNoise);
        mainToolBar->addAction(actionNew);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionOpen_Image);
        mainToolBar->addAction(actionEducate);
        mainToolBar->addAction(actionRecognize);
        mainToolBar->addAction(actionRecognize_Async);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionDefault_images);
        mainToolBar->addAction(actionNoise);

        retranslateUi(ImageHopfieldClass);

        educateButton->setDefault(false);


        QMetaObject::connectSlotsByName(ImageHopfieldClass);
    } // setupUi

    void retranslateUi(QMainWindow *ImageHopfieldClass)
    {
        ImageHopfieldClass->setWindowTitle(QApplication::translate("ImageHopfieldClass", "\320\241\321\226\321\202\320\272\320\260 \320\245\320\276\320\277\321\204\321\226\320\273\320\264\320\260", 0));
        actionExit->setText(QApplication::translate("ImageHopfieldClass", "\320\222\320\270\321\205\321\226\320\264", 0));
        actionExit->setShortcut(QApplication::translate("ImageHopfieldClass", "Ctrl+Q", 0));
        actionNew->setText(QApplication::translate("ImageHopfieldClass", "\320\235\320\276\320\262\320\270\320\271", 0));
        actionNew->setShortcut(QApplication::translate("ImageHopfieldClass", "Ctrl+N", 0));
        actionAbout->setText(QApplication::translate("ImageHopfieldClass", "\320\237\321\200\320\276 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\321\203", 0));
        actionView_Help->setText(QApplication::translate("ImageHopfieldClass", "\320\237\320\276\320\264\320\270\320\262\320\270\321\202\320\270\321\201\321\217 \320\264\320\276\320\277\320\276\320\274\320\276\320\263\321\203", 0));
        actionView_Help->setShortcut(QApplication::translate("ImageHopfieldClass", "F1", 0));
        actionOpen_Image->setText(QApplication::translate("ImageHopfieldClass", "\320\222\321\226\320\264\320\272\321\200\320\270\321\202\320\270 \320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\275\321\217", 0));
        actionOpen_Image->setShortcut(QApplication::translate("ImageHopfieldClass", "Ctrl+O", 0));
        actionEducate->setText(QApplication::translate("ImageHopfieldClass", "\320\235\320\260\320\262\321\207\320\270\321\202\320\270", 0));
        actionEducate->setShortcut(QApplication::translate("ImageHopfieldClass", "Ctrl+E", 0));
        actionRecognize->setText(QApplication::translate("ImageHopfieldClass", "\320\240\320\276\320\267\320\277\321\226\320\267\320\275\320\260\321\202\320\270 \321\201\320\270\320\275\321\205\321\200\320\276\320\275\320\275\320\276", 0));
        actionRecognize->setShortcut(QApplication::translate("ImageHopfieldClass", "Ctrl+R", 0));
        actionDefault_images->setText(QApplication::translate("ImageHopfieldClass", "\320\241\321\202\320\260\320\275\320\264\320\260\321\200\321\202\320\275\321\226 \320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\275\321\217", 0));
        actionDefault_images->setShortcut(QApplication::translate("ImageHopfieldClass", "Ctrl+D", 0));
        actionRecognize_Async->setText(QApplication::translate("ImageHopfieldClass", "\320\240\320\276\320\267\320\277\321\226\320\267\320\275\320\260\321\202\320\270 \320\260\321\201\320\270\320\275\321\205\321\200\320\276\320\275\320\275\320\276", 0));
        actionNoise->setText(QApplication::translate("ImageHopfieldClass", "\320\227\320\260\321\210\321\203\320\274\320\273\320\265\320\275\320\275\321\217", 0));
        openImageButton->setText(QApplication::translate("ImageHopfieldClass", "\320\222\321\226\320\264\320\272\321\200\320\270\321\202\320\270 \320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\275\321\217", 0));
        educateButton->setText(QApplication::translate("ImageHopfieldClass", "\320\235\320\260\320\262\321\207\320\270\321\202\320\270", 0));
        recognizeButton->setText(QApplication::translate("ImageHopfieldClass", "\320\240\320\276\320\267\320\277\321\226\320\267\320\275\320\260\321\202\320\270 \321\201\320\270\320\275\321\205\321\200\320\276\320\275\320\275\320\276", 0));
        inputImageLabel->setText(QApplication::translate("ImageHopfieldClass", "\320\222\321\205\321\226\320\264\320\275\320\265 \320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\275\321\217", 0));
        outputImageLabel->setText(QApplication::translate("ImageHopfieldClass", "\320\222\320\270\321\205\321\226\320\264\320\275\320\265 \320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\275\321\217", 0));
        menu->setTitle(QApplication::translate("ImageHopfieldClass", "\320\244\320\260\320\271\320\273", 0));
        menuHelp->setTitle(QApplication::translate("ImageHopfieldClass", "\320\224\320\276\320\277\320\276\320\274\320\276\320\263\320\260", 0));
        menuEdit->setTitle(QApplication::translate("ImageHopfieldClass", "\320\240\320\265\320\264\320\260\320\263\321\203\320\262\320\260\320\275\320\275\321\217", 0));
    } // retranslateUi

};

namespace Ui {
    class ImageHopfieldClass: public Ui_ImageHopfieldClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEHOPFIELD_H
