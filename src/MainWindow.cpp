#include "MainWindow.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QImageWriter>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    imageLabel = new QLabel("No image loaded", this);
    imageLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(imageLabel);

    dpiXEdit = new QLineEdit(this);
    dpiYEdit = new QLineEdit(this);
    dpiXEdit->setPlaceholderText("DPI X");
    dpiYEdit->setPlaceholderText("DPI Y");
    layout->addWidget(dpiXEdit);
    layout->addWidget(dpiYEdit);

    QPushButton *updateButton = new QPushButton("Update DPI", this);
    QPushButton *saveButton = new QPushButton("Save Image", this);
    layout->addWidget(updateButton);
    layout->addWidget(saveButton);

    setCentralWidget(central);

    // Menu
    QMenu *fileMenu = menuBar()->addMenu("File");
    QAction *openAction = fileMenu->addAction("Open");
    QAction *saveAction = fileMenu->addAction("Save");

    connect(openAction, &QAction::triggered, this, &MainWindow::openImage);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveImage);
    connect(updateButton, &QPushButton::clicked, this, &MainWindow::updateDPI);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveImage);
}

void MainWindow::openImage() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image", "", "Images (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty()) {
        image.load(fileName);
        imageLabel->setPixmap(QPixmap::fromImage(image).scaled(400, 400, Qt::KeepAspectRatio));
    }
}

void MainWindow::updateDPI() {
    if (image.isNull()) {
        QMessageBox::warning(this, "Error", "No image loaded!");
        return;
    }

    bool okX, okY;
    int dpiX = dpiXEdit->text().toInt(&okX);
    int dpiY = dpiYEdit->text().toInt(&okY);

    if (!okX || !okY) {
        QMessageBox::warning(this, "Error", "Invalid DPI values!");
        return;
    }

    image.setDotsPerMeterX(dpiX / 0.0254); // DPI → dots per meter
    image.setDotsPerMeterY(dpiY / 0.0254);

    imageLabel->setPixmap(QPixmap::fromImage(image).scaled(400, 400, Qt::KeepAspectRatio));
}

void MainWindow::saveImage() {
    if (image.isNull()) {
        QMessageBox::warning(this, "Error", "No image loaded!");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Save Image", "", "PNG (*.png);;JPEG (*.jpg)");
    if (!fileName.isEmpty()) {
        if (!image.save(fileName)) {
            QMessageBox::warning(this, "Error", "Failed to save image!");
        }
    }
}
