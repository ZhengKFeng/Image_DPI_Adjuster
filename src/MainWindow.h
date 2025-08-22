#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>

class QLineEdit;
class QLabel;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void openImage();
    void saveImage();
    void updateDPI();

private:
    QImage image;
    QLabel *imageLabel;
    QLineEdit *dpiXEdit;
    QLineEdit *dpiYEdit;
};

#endif // MAINWINDOW_H
