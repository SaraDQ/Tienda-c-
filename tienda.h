#ifndef TIENDA_H
#define TIENDA_H
#include "iostream"
#include <QDebug>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <cmath>
#include <cstdlib>
#include <string>

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QMainWindow>

#include "producto.h"
#include "finalizacion.h"

#define IVA 12

QT_BEGIN_NAMESPACE
namespace Ui { class Tienda; }
QT_END_NAMESPACE

class Tienda : public QMainWindow
{
    Q_OBJECT

public:
    Tienda(QWidget *parent = nullptr);
    ~Tienda();
    float subtotal;
    float total;
    float iva;
    int cantidad;

private slots:
    void on_inProducto_currentIndexChanged(int index);

    void on_btnAgregar_released();

    void on_btnFinalizar_clicked();

    void on_limpiar_clicked();

private:
    Ui::Tienda *ui;
    QList<Producto*> m_productos;
    void cargarProductos();
    float m_subtotal;
    QString m_detalles;

    void calcular(float stProducto);
    void limpiar();
    void borrar(char a[]);
    bool extraer(char b[]);
    bool veriPhone(char c[]);
    void guardar();

};
#endif // TIENDA_H
