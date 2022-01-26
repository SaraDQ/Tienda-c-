#ifndef FINALIZACION_H
#define FINALIZACION_H
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QDialog>
#include <QObject>
#include <QDateTime>

namespace Ui {
class Finalizacion;
}

class Finalizacion : public QDialog
{
    Q_OBJECT

public:
    explicit Finalizacion(QString nombreC,QString cedula,QString telefono,QString email,QString iva,QString total,QString subtotal,QString direccion,QString detalles,QWidget *parent = nullptr);
    ~Finalizacion();
    Ui::Finalizacion *ui;
    void guardar();
    bool consumidor(char a[]);

public slots:
    void on_imprimir_clicked();

private:

};

#endif // FINALIZACION_H
