#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <memory>
#include <exception>
#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QColor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnCriar, &QPushButton::clicked, this, [this]()
            {
                int nx = ui->spinNx->value();
                int ny = ui->spinNy->value();
                int nz = ui->spinNz->value();

                try
                {
                    escultura = std::make_unique<Sculptor>(nx, ny, nz);

                    //limpar o desenho anterior
                    ui->tabelaDesenho->clearContents();

                    //configurar as dimensoes da grade
                    ui->tabelaDesenho->setRowCount(ny);
                    ui->tabelaDesenho->setColumnCount(nx);

                    //esconder os cabecalho
                    ui->tabelaDesenho->horizontalHeader()->hide();
                    ui->tabelaDesenho->verticalHeader()->hide();

                    //definir o tamanho das celulas
                    ui->tabelaDesenho->horizontalHeader()->setDefaultSectionSize(20);
                    ui->tabelaDesenho->verticalHeader()->setDefaultSectionSize(20);

                    //exibir as linhas da grade
                    ui->tabelaDesenho->setShowGrid(true);

                    //configurar as camadas disponiveis
                    ui->spinCamada->setRange(0, nz - 1);
                    ui->spinCamada->setValue(nz / 2);

                    QString mensagem = QString(
                                           "Escultura criada com sucesso!\n\n"
                                           "Dimensoes: %1 x %2 x %3"
                                           ).arg(nx).arg(ny).arg(nz);

                    QMessageBox::information(this, "Escultor 3D", mensagem);
                }
                catch (const std::exception& erro)
                {
                    QMessageBox::critical(this, "Erro", erro.what());
                }
            });

    connect(ui->tabelaDesenho, &QTableWidget::cellClicked,
            this, [this](int linha, int coluna)
            {
                if (!escultura)
                {
                    return;
                }

                int x = coluna;
                int y = linha;
                int z = ui->spinCamada->value();

                //define a cor azul
                escultura->setColor(0.0, 0.2, 1.0, 1.0);

                //ativa o voxel na matriz tridimensional
                escultura->putVoxel(x, y, z);

                //obtem a celula clicada
                QTableWidgetItem* item =
                    ui->tabelaDesenho->item(linha, coluna);

                //cria um item caso a celula esteja vazia
                if (item == nullptr)
                {
                    item = new QTableWidgetItem();
                    ui->tabelaDesenho->setItem(linha, coluna, item);
                }

                //pinta a celula de azul
                item->setBackground(QColor(0, 51, 255));

                ui->tabelaDesenho->clearSelection();
            });
}

MainWindow::~MainWindow()
{
    delete ui;
}