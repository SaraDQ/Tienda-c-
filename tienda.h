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
#include "ui_finalizacion.h"
#include <QTranslator>
#include <QInputDialog>
#include <QApplication>
#include <QEvent>

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

    void on_btnAgregar_released();

    void on_btnFinalizar_clicked();

    void on_limpiar_clicked();

    void on_inProducto_currentIndexChanged(int index);

    //Corresponde a las traducciones
    void changeEvent(QEvent * event) override;

private:
    Ui::Tienda *ui;
    QList<Producto*> m_productos;
    void cargarProductos();
    float m_subtotal;
    QString m_detalles;
    QTranslator m_traduccion;


    void calcular(float stProducto); /*Calcula los totales*/
    void limpiar();                  /*Limpia la informacion ingresada*/
    void borrar(char a[]);          /*Esta funcion corresponde a la cedula*/
    bool extraer(char b[]);          /*Funcion correspondiente a la cedula*/
    bool veriPhone(char c[]);       /*Corresponde a la cedula*/
    void guardar();                 /*Guarda datos*/
    void cargar();                  /*Carga los productos de la tienda*/
};
#endif // TIENDA_H
