/*
 * Programacion orientada a objetos
 * Programa de tienda y facturacion con GUI
 * Autor: Sara Quiguango <squiguango@est.ups.edu.ec>
 * Fecha : 25/01/2022
 */
#include "tienda.h"
#include "ui_tienda.h"
#include "ui_finalizacion.h"

using namespace std;

Tienda::Tienda(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tienda)
{
    ui->setupUi(this);
    // Lista de productos
    cargarProductos();
    // Mostrar los productos en el combo
    foreach (Producto *p, m_productos){
        ui->inProducto->addItem(p->nombre());
    }
    // Configurar cabecera de la tabla
    QStringList cabecera = {"Cantidad", "Producto", "P. unitario", "Subtotal"};
    ui->outDetalle->setColumnCount(4);
    ui->outDetalle->setHorizontalHeaderLabels(cabecera);
    // Establecer el subtotal a 0
    m_subtotal = 0;
    //Establecer los detalles con string
    m_detalles ="";
}

Tienda::~Tienda()
{
    delete ui;
}
/**
 * @brief Tienda::borrar
 * @param a
 */
void Tienda::borrar(char a[]){
    for(int i=0; i<11;i++){
        if (a[i] == '\n')
            a[i] = '\0';
    }
}
/**
 * @brief Tienda::veriPhone
 * @param c
 * @return
 */
bool Tienda::veriPhone(char c[]){
    int limite = strlen(c);
    if(limite == 10){
        ui->inTelefono->setStyleSheet("QLineEdit { background-color :green}");
        return true;

    }
    else{
        ui->inTelefono->setStyleSheet("QLineEdit { background-color :red}");
        return false;
    }

}
/**
 * @brief Tienda::extraer Aqui se hace la validacion de la cedula con sus respectivos colores
 * @param b
 * @return
 */
bool Tienda::extraer(char b[]){
    int v[10], num, limite;
    limite = strlen(b);

    if (limite != 10){
        ui->inCedula->setStyleSheet("QLineEdit { background-color :red}");
        return false;
    }

    if (limite == 10){

        for (int i=0;i<10;i++){

            num = b[i]-48;
            v[i] = num; }

        //Proceso de validacion de cedula
        int vec[10], suma, ultimo, ultimon;
        if (v[0] == 1 || v[0] == 2){
            if (v[2] > 0 && v[2] < 6 ){

                for (int i=0; i<9; i+=2){
                    vec[i] = v[i] *2;
                    if (vec[i] >= 10)
                        vec[i] -= 9;
                }
                for (int i=1; i<9; i+=2){
                    vec[i] = v[i];
                }
                suma= 0;
                for(int i=0; i<10; i++){
                    suma = suma + vec[i];
                }
                if (suma == 10)
                    ultimo = 0;
                else if(suma >10 && suma<20)
                    ultimo = 20;
                else if (suma >20 && suma<30)
                    ultimo = 30;
                else if (suma >30 && suma<40)
                    ultimo = 40;
                else {
                    ui->inCedula->setStyleSheet("QLineEdit { background-color :red}");
                    return false;
                }
                ultimon = ultimo - suma;

                if (ultimon == v[9]){
                    ui->inCedula->setStyleSheet("QLineEdit { background-color :green}");
                    return true;
                }
                else{
                    ui->inCedula->setStyleSheet("QLineEdit { background-color :red}");}
                bool var=true;
                for (int i=0;i<10;i++){
                    if( strcmp(b, "9999999999")){
                        var=false;
                    }
                }
                if(var != false){
                    ui->inCedula->setStyleSheet("QLineEdit { background-color :green}");
                    return true;
                }
                return false;
            }
            else{
                ui->inCedula->setStyleSheet("QLineEdit { background-color :red}");
                bool var=true;
                for (int i=0;i<10;i++){
                    if( strcmp (b, "9999999999")){
                        var=false;
                    }
                }

                if(var != false){
                    ui->inCedula->setStyleSheet("QLineEdit { background-color :green}");
                    return true;
                }
                return false;
            }

        }
    }

}

/**
 * @brief Tienda::cargarProductos Carga la lista de productos de la tienda
 */
void Tienda::cargarProductos()
{
    // Crear productos "quemados" en el código
    m_productos.append(new Producto(1, "Leche", 0.80));
    m_productos.append(new Producto(2, "Pan", 0.15));
    m_productos.append(new Producto(3, "Queso", 2.50));
    // Podría leerse de una base de datos, de un archivo o incluso de Internet
}

void Tienda::calcular(float stProducto)
{
    // Calcular valores
    m_subtotal += stProducto;
     iva = m_subtotal * IVA / 100;
     total = m_subtotal + iva;
    // Mostrar valores en GUI
    ui->outSubtotal->setText("$ " + QString::number(m_subtotal, 'f', 2));
    ui->outIva->setText("$ " + QString::number(iva, 'f', 2));
    ui->outTotal->setText("$ " + QString::number(total, 'f', 2));
}
//Limpiar la informacion ingresada
void Tienda::limpiar()
{
    //Inicializar las variables en cero
    m_subtotal = 0;
    subtotal=0;
    total=0;
    iva=0;
    ui->inCedula->setFocus();
    ui->inDireccion->setPlainText("");
    ui->inNombre->setText("");
    ui->inTelefono->setText("");
    ui->inEmail->setText("");
    cantidad=0;
    ui->inCantidad->setValue(0);
    ui->inCedula->setText("");

    ui->outIva->setText("");
    ui->outSubtotal->setText("");
    ui->outTotal->setText("");

    ui->inTelefono->setStyleSheet("QLineEdit { background-color :white; font: 10pt Consolas; color: rgb(0, 0, 0);}");
    ui->inCedula->setStyleSheet("QLineEdit { background-color :white; font: 10pt Consolas; color: rgb(0, 0, 0);}");
    while (ui->outDetalle->rowCount() > 0)
    {
        ui->outDetalle->removeRow(0);
    }
}

void Tienda::on_inProducto_currentIndexChanged(int index)
{
    // Obtener el precio del producto actual seleccionado
    float precio = m_productos.at(index)->precio();
    // Mostrar el precio del product en la etiqueta
    ui->outPrecio->setText("$ " + QString::number(precio,'f',2));
    // Resetear el spinbox de cantidad
    ui->inCantidad->setValue(0);
}


void Tienda::on_btnAgregar_released()
{
    //Obtener datos de la GUI
    QString nombreC = ui->inNombre->text();
    QString cedula = ui->inCedula->text();
    QString telefono = ui->inTelefono->text();
    QString email = ui->inEmail->text();
    QString direccion = ui->inDireccion->toPlainText();
    std::string tel = telefono.toUtf8().constData();
    std::string utf8_text = cedula.toUtf8().constData();
    char buffer[100];
    strcpy(buffer,utf8_text.c_str());
    char phone[100];
    strcpy(phone,tel.c_str());
    // Validar que no se agregen productos con 0 cantidad
     cantidad = ui->inCantidad->value();
    if (cantidad == 0){
        return;
    }
    //Validar que los datos del cliente esten completos
    if(nombreC == "" || cedula == ""||telefono ==""||email==""||direccion==""){
        QMessageBox::warning(this,"Advertencia","Ingrese todos los datos del cliente porfavor.");
        return;
    }
    borrar(buffer);
    bool aux2 =extraer(buffer);
    bool aux = veriPhone(phone);

    if( aux && aux2){
        // Obtener los datos de la GUI
        int i = ui->inProducto->currentIndex();
        Producto *p = m_productos.at(i);

        // Calcular el subrotal del producto
        subtotal = p->precio() * cantidad;

        // Agregar los datos a la tabla
        int fila = ui->outDetalle->rowCount();
        ui->outDetalle->insertRow(fila);
        ui->outDetalle->setItem(fila, 0, new QTableWidgetItem(QString::number(cantidad)));
        ui->outDetalle->setItem(fila, 1, new QTableWidgetItem(p->nombre()));
        ui->outDetalle->setItem(fila, 2, new QTableWidgetItem(QString::number(p->precio(),'f',2)));
        ui->outDetalle->setItem(fila, 3, new QTableWidgetItem(QString::number(subtotal,'f',2)));

        // Limpiar datos
        ui->inCantidad->setValue(0);
        ui->inProducto->setFocus();

        // Actualizar subtotales
        calcular(subtotal);
    }
}

void Tienda::on_btnFinalizar_clicked()
{

    //Obtener datos de la GUI
    QString nombreC = ui->inNombre->text();
    QString cedula = ui->inCedula->text();
    QString telefono = ui->inTelefono->text();
    QString email = ui->inEmail->text();
    QString iva = ui->outIva->text();
    QString total = ui->outTotal->text();
    QString subtotal = ui->outSubtotal->text();
    QString direccion = ui->inDireccion->toPlainText();
    int filas = ui->outDetalle->rowCount();
    int contador=0;
    QString compras="";
    while(contador!=filas){
        compras+="\t"+ui->outDetalle->item(contador,0)->text()+"\t "+
                ui->outDetalle->item(contador,1)->text()+" \t   "+
                ui->outDetalle->item(contador,2)->text()+" \t   "+
                ui->outDetalle->item(contador,3)->text()+"  \n";
        contador++;
    }
    m_detalles=compras;

    //Validacion para que ingrese datos a la compra del cliente
    if(nombreC == "" || cedula == ""||telefono ==""||email==""||direccion==""){
        QMessageBox::warning(this,"Advertencia","Aun no ingresa datos de la compra.");
        return;
    }
    //Enviar datos a la nueva ventana
    Finalizacion *factura = new Finalizacion(nombreC,cedula,telefono,email,iva,total,subtotal,direccion,m_detalles);
    factura->show();

}

void Tienda::on_limpiar_clicked()
{
    limpiar();
}

