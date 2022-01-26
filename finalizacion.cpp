#include "finalizacion.h"
#include "ui_finalizacion.h"

Finalizacion::Finalizacion(QString nombreC,QString cedula,QString telefono,QString email,QString iva,QString total,QString subtotal,QString direccion,QString detalles, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Finalizacion)
{
    ui->setupUi(this);
    //Nombre de la ventana
    setWindowTitle("Factura de la compra");

    //Enviando la información a la nueva ventana Finalizacion
    ui->lbl_nombre->setText(nombreC);
    ui->lbl_cedula->setText(cedula);
    ui->lbl_correo->setText(email);

    ui->lbl_direccion->setText(direccion);
    ui->lbl_telefono->setText(telefono);
    ui->outIVA_->setText(iva);
    ui->outSubtotal_->setText(subtotal);
    ui->outTotal_->setText(total);
    ui->outCompras->setPlainText(detalles);
}

Finalizacion::~Finalizacion()
{
    delete ui;
}

//Metodo para la verificacion de consumidor final
bool Finalizacion::consumidor(char b[]){
    bool var=true;
    for (int i=0;i<10;i++){
        if( strcmp (b, "9999999999")){
            var=false;
        }
    }

    if(var == false){
        return false;
    }
    else{
        return true;
    }
}

void Finalizacion::on_imprimir_clicked(){

    //Aqui se hace la impresion del nombre del texto a imprimir con fecha y hora
    QString current = QDateTime::currentDateTime().toString("ddMMyyyy_hhmmss");
    QFile archivo(current+".txt");
    if(archivo.open(QIODevice::WriteOnly|QIODevice::Text)){
        QTextStream datosA(&archivo);
        // Crear un 'stream' de texto
        QTextStream salida(&archivo);
        // Enviar los datos ingresados a la factura
        salida << "---------------------F A C T U R A-------------------------"<<"\n";
        salida << "Cliente: ";
        std::string cedu = ui->lbl_cedula->text().toUtf8().constData();
        char buffer[100];
        strcpy(buffer,cedu.c_str());
        if(consumidor(buffer)){
            salida << "Consumidor Final"<<"\n";
            salida << "RUC: " + ui->lbl_cedula->text()<<"\t\t";
            salida << "Dirección: "<<" Dirección"<<"\n";
            salida << "Número: "<<"Número"<<"\t";
            salida << "\tE-mail: "<<"Email\n";
        }
        else{
            salida << ui->lbl_nombre->text()<<"\n";
            salida << "RUC: " + ui->lbl_cedula->text()<<"\t\t";
            salida << "Dirección: "+ui->lbl_direccion->text()<<"\n";
            salida << "Número: "+ui->lbl_telefono->text()<<"\t";
            salida << "E-mail: "+ui->lbl_correo->text()<<"\n";
        }
        salida <<"--------------------------------------------------------\n";
        salida <<"    Cantidad"<<"    Producto"<<"  P.Unitario"<<"     Subtotal\n";
        salida <<"--------------------------------------------------------\n";
        salida << ui->outCompras->toPlainText()<<"\n";
        salida << "--------------------------------------------------------"<<"\n";
        salida << "\t\t\t\tSubtotal: "+ui->outSubtotal_->text()<<"\n";
        salida << "\t\t\t\tIVA (12%): "+ui->outIVA_->text()<<"\n";
        salida << "\t\t\t\tTOTAL: "+ui->outTotal_->text()<<"\n";
        salida <<"--------------------------------------------------------";
    }
    else {
        // Mensaje de error si no se puede abrir el archivo
        QMessageBox::warning(this,
                             "Guardar datos",
                             "No se pudo guardar los datos");
    }
    //Mensaje de informacion para saber que se hizo correctamente la impresion de la factura
    QMessageBox::information(this,
                         "Datos",
                         "Datos guardados");
    // Cerrar el archivo
    archivo.close();
}
