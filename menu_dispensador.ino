#include <Arduino.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

/* direcciones de utilizadas de la memoria EEPROM */

#define direccion_1 0 //Direccion para el parametro inicial del tiempo
#define direccion_2 1 //Direccion para el parametro inicial del precio
#define direccion_3 2 //Direccion para el parametro inicial del tiempo de enjuague
#define direccion_4 3 //Direccion para el parametro inicial de la fecha?
#define direccion_5 4 //Direccion para definir el tiempo
#define direccion_6 5 //Direccion para definir el precio
#define direccion_7 6 //Direccion para definir el timepo de enjuague
#define direccion_8 7 //Direccion para definir la fecha??

/*Botones Utilizados para la configuracion*/

#define boton_1     8 //Posicion del boton 1
#define boton_2     9 //Posicion del boton 2
#define boton_3     10 //Posicion del boton 3
#define boton_4     11 //Posicion del boton 4

/*Parametros base */

const int tiempo_i = 10;
const int precio_i = 10;
const int enjuague_i = 10;
const int fecha_i = 10;


/*Instrucciones para desplegar en pantalla(regresa la opcion deseada)*/

int Instrucciones(){

  int x;

  Serial.println("Presione el boton 1 para cambiar el timepo, 2 para cambiar el precio, 3 para cambiar el tiempo de enjuague, 4 para cambiar la Fecha y 5 para salir");

/*Si presionamos alguno de los botones seleccionados se almacena en la varible X y la retornamos*/

  if(boton_1){
    x = 1;
  }
  else if(boton_2){
    x = 2;
  }
  else if(boton_3){
    x = 3;
  }
  else if(boton_4){
    x = 4;
  }
  return x;
}

/*funcion que determina el timepo determinado por el usuario*/

void Tiempos (){

/*Variables auxiliares para desplegar y cambiar el timepo*/
  int tiempo_a = 0; 
  int tiempo_b = 0;

  tiempo_b = EEPROM.read(direccion_5);

  lcd.setCursor(0, 0);
  lcd.print("Oprima arriba y abajo para ajustar el tiempo");
  lcd.setCursor(2, 8);

  if (tiempo_b == 255)
  {
    lcd.print(tiempo_i);
  }
  else
  {
    lcd.print(tiempo_b);
  }
  
/*Se ejecuta el siguiente bucle hasta que se presiones el boton 3*/
  do
  {
/*Al tiempo base de le suma una unidad */
  lcd.clear();
    if(boton_1){

      if (tiempo_a == 0){                                          //Cuando comenzamos a cambiar el tiempo, al variable auxiliar inica en 0, utilizamos esta condicion para agregarle una unidad al presionar el boton
        tiempo_a = tiempo_a + (EEPROM.read(direccion_1) + 1);
        lcd.clear();
        lcd.print(tiempo_a);
      }
      else{                                                        //Despues la variable auxiliar ya tiene valores almacenado y utilizamos esta condicion para agregarle una unidad al presionar el boton
        tiempo_a = tiempo_a + 1;
        lcd.clear();
        lcd.print(tiempo_a);                                   
      }

    }
/*Al tiempo base de le resta una unidad */
    else if (boton_2){

      if (tiempo_a == 0){                                         //Cuando comenzamos a cambiar el tiempo, al variable auxiliar inica en 0, utilizamos esta condicion para quitarle una unidad al presionar el boton
        tiempo_a = tiempo_a + (EEPROM.read(direccion_1) - 1);
        lcd.clear();
        lcd.print(tiempo_a);
      }
      else{
        tiempo_a = tiempo_a - 1;                                  //Despues la variable auxiliar ya tiene valores almacenado y utilizamos esta condicion para quitarle una unidad al presionar el boton
        lcd.clear();
        lcd.print(tiempo_a);      
      }

    }
  } while (boton_3 != 0);                                         
  EEPROM.write(direccion_5, tiempo_a);

}

/*funcion que determina el precio determinado por el usuario*/

void Precios(){

  int precio_a = 0;

  Serial.println("Oprima arriba y abajo para ajustar el precio");
/*Se ejecuta el siguiente bucle hasta que se presiones el boton 3*/
  do
  {
/*Al precio base de le suma una unidad */
    if(boton_1){
      if (precio_a == 0){                                       //Cuando comenzamos a cambiar el precio, al variable auxiliar inica en 0, utilizamos esta condicion para agregarle una unidad al presionar el boton
        precio_a = precio_a + (EEPROM.read(direccion_2) + 1);
      }
      else{                                                     //Despues la variable auxiliar ya tiene valores almacenado y utilizamos esta condicion para agregarle una unidad al presionar el boton
        precio_a = precio_a + 1;
      }
    }
/*Al precio base de le resta una unidad */
    else if (boton_2){
      if (precio_a == 0){                                       //Cuando comenzamos a cambiar el precio, al variable auxiliar inica en 0, utilizamos esta condicion para quitarle una unidad al presionar el boton
  
        precio_a = precio_a + (EEPROM.read(direccion_2) - 1);
      }
      else{
        precio_a = precio_a - 1;                                //Despues la variable auxiliar ya tiene valores almacenado y utilizamos esta condicion para quitarle una unidad al presionar el boton
      }
    }
  } while (boton_3 != true);
  
  EEPROM.write(direccion_6, precio_a);

}

/*funcion que determina el tiempo de enjuague determinado por el usuario*/

void Enjuague(){

  int enjuague_a = 0;
/*Se ejecuta el siguiente bucle hasta que se presiones el boton 3*/
  Serial.println("Oprima arriba y abajo para ajustar el timepo de enjuague");
  do
  {
/*Al tiempo de enjuague base de le suma una unidad */
    if(boton_1){
      if (enjuague_a == 0){
        enjuague_a = enjuague_a + (EEPROM.read(direccion_3) + 1);
      }
      else{
        enjuague_a = enjuague_a + 1;
      }
    }
/*Al tiempo de enjuague base de le resta una unidad */
    else if (boton_2){
      if (enjuague_a == 0){
        enjuague_a = enjuague_a + (EEPROM.read(direccion_3) - 1);
      }
      else{
        enjuague_a = enjuague_a - 1;
      }
    }
  } while (boton_3 != true);
  
  EEPROM.write(direccion_7, enjuague_a);

}

/*Establece los parametros iniciales*/

void Calibrar(){
  EEPROM.write(direccion_1, tiempo_i);
  EEPROM.write(direccion_2, precio_i);
  EEPROM.write(direccion_3, enjuague_i);
  EEPROM.write(direccion_4, fecha_i);

  pinMode(boton_1, INPUT);
  pinMode(boton_2, INPUT);
  pinMode(boton_3, INPUT);
  pinMode(boton_4, INPUT);

  lcd.begin(16,4);
  lcd.print("Hola");
}

/*Funcion para desplegar el menu*/

void menu(){
  int i = 0;
  do
  {
    
		i = Instrucciones();

    switch (i)
    {
    case 1:
      Tiempos();
      break;
    case 2:
      Precios();
      break;
    case 3:
      Enjuague();
      break;
    case 4:
      
      break;
    
    case 5:
      i = 5;
      break;

    default:
      Serial.println("Error, intente de nuevo");
      i = 0;
      break;
    }
  } while ( i < 5);
}

void setup() {

  Calibrar();

}

void loop() {

}
