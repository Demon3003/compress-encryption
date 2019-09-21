#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "thread1.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void update(bool i);

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_rle_clicked();

    void on_rle_unarchiver_clicked();

    void on_rc4_clicked();

    void on_rc4_decoding_clicked();

    void on_huffman_clicked();

    void on_huffman_unarchiver_clicked();

    void on_des_clicked();

    void on_des_decoding_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    void huffman();
    void huffman_unarchiver();
    void rle();
    void rle_unarchiver();
    void rc4();
    void rc4_decoding();
    void des_algorithm(char f);
    void showProgressLine();

};

#endif // MAINWINDOW_H
