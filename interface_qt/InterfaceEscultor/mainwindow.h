#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <memory>
#include "Sculptor.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;

    std::unique_ptr<Sculptor> escultura;
};
#endif // MAINWINDOW_H
