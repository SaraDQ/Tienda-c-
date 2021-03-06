#include "finalizacion.h"
#include "ui_finalizacion.h"

Finalizacion::Finalizacion(QString nombreC,QString cedula,
                           QString telefono,QString email,QString iva,
                           QString total,QString subtotal,QString direccion,
                           QString detalles, QWidget *parent) :
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

Finalizacion::~Finalizacion(){delete ui;}

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
        salida <<"_______________________________________________________________"<<"\n";
        salida << tr("              F A C T U R A  D E  V E N T A             ")<<"\n";
        salida <<"_______________________________________________________________"<<"\n";
        salida << tr("                Sara Nicole Quiguango Diaz              ")<<"\n";
        salida << tr("                     Ruc.175412304589                   ")<<"\n\n";
        salida << tr("                  ventasTienda@gmail.com              ")<<"\n";
        salida <<"_______________________________________________________________"<<"\n";
        salida << tr("Cliente: ");
        std::string cedu = ui->lbl_cedula->text().toUtf8().constData();
        char buffer[100];
        strcpy(buffer,cedu.c_str());
        if(consumidor(buffer)){
            salida << tr("Consumidor Final")<<"\n";
            salida << tr("RUC: ") + ui->lbl_cedula->text()<<"\t\t";
            salida << tr("Dirección: ")<<tr(" Dirección")<<"\n";
            salida << tr("Número: ")<<tr("Número")<<"\t";
            salida << tr("\tE-mail: ")<<tr("Email")<<"\n";
        }
        else{
            salida << ui->lbl_nombre->text()<<"\n";
            salida << tr("RUC: " )+ ui->lbl_cedula->text()<<"\t\t";
            salida << tr("Dirección: ")+ui->lbl_direccion->text()<<"\n";
            salida << tr("Número: ")+ui->lbl_telefono->text()<<"\t";
            salida << tr("E-mail: ")+ui->lbl_correo->text()<<"\n";
        }
        salida <<"_______________________________________________________________"<<"\n";
        salida <<tr("    Cantidad")<<tr("    Producto")<<tr("  P.Unitario")<<tr("     Subtotal")<<"\n";
        salida <<"_______________________________________________________________"<<"\n";
        salida << ui->outCompras->toPlainText()<<"\n";
        salida <<"_______________________________________________________________"<<"\n";
        salida << tr("\t\t\t\tSubtotal: ")+ui->outSubtotal_->text()<<"\n";
        salida << tr("\t\t\t\tIVA (12%): ")+ui->outIVA_->text()<<"\n";
        salida << tr("\t\t\t\tTOTAL: ")+ui->outTotal_->text()<<"\n";
        salida <<"_______________________________________________________________"<<"\n";
        salida <<tr("Gracias por su compra.                                         ")<<"\n";
        salida <<"_______________________________________________________________"<<"\n";
    }
    else {
        // Mensaje de error si no se puede abrir el archivo
        QMessageBox::warning(this,
                             tr("Guardar datos"),
                             tr("No se pudo guardar los datos"));
    }
    //Mensaje de informacion para saber que se hizo correctamente la impresion de la factura
    QMessageBox::information(this,
                         tr("Datos"),
                         tr("Datos guardados"));
    // Cerrar el archivo
    archivo.close();
}
