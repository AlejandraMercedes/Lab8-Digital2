#include <SPI.h>
#include <SD.h>

#define SSpin 5
int opcionElegida;
File miArchivo;
int totalL = 0;
char dato;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Inicializando tarjeta...");

  if(!SD.begin(SSpin)) {
    Serial.println("fallo en inicialización");
    return;
  }
  Serial.println("Inicialización correcta");
  Serial.println("Opciones disponibles:");
  Serial.println("Opción 1: Mañana a las 6!");
  Serial.println("Opción 2: Manzana");
  Serial.println("Opción 3: Husky");
  Serial.println("Opción 4: Crear mi propia imagen");
  Serial.println("Opción 5: Visualizar mi propia imagen");


}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10); 

    
  while (!Serial.available()) {
  // Esperar a que haya datos disponibles en el monitor serial
  }
  opcionElegida = Serial.parseInt();

  if(opcionElegida  == 1){
     File archivo = SD.open("/Alas6.txt");
      if (archivo) {
        Serial.println(" ");
        Serial.println("/Alas6.txt");
        while (archivo.available()) {
          Serial.write(archivo.read());
        }
        archivo.close();
      } else {
        Serial.println("Error al intentar abrir el archivo");
      }
  }

   if(opcionElegida  == 2){
     File archivo = SD.open("/Manzana.txt");
      if (archivo) {
        Serial.println(" ");
        Serial.println("/Manzana.txt");
        while (archivo.available()) {
          Serial.write(archivo.read());
        }
        archivo.close();
      } else {
        Serial.println("Error al intentar abrir el archivo");
      }
  }

  if(opcionElegida  == 3){
     File archivo = SD.open("/husky.txt");
      if (archivo) {
        Serial.println(" ");
        Serial.println("/husky.txt");
        while (archivo.available()) {
          Serial.write(archivo.read());
        }
        archivo.close();
      } else {
        Serial.println("Error al intentar abrir el archivo");
      }
  }

  if(opcionElegida == 5){
   // Leer Opcion 5
     File archivo = SD.open("/miArchivo.txt");
      if (archivo) {
        Serial.println(" ");
        Serial.println("Imagen Propia ");
        while (archivo.available()) {
          Serial.write(archivo.read());
        }
        archivo.close();
      } else {
        Serial.println("Error al intentar abrir el archivo");
      }
  }


  if(opcionElegida == 4){
    Serial.println("Cuenta con un máximo de 15 lineas para elaborar una imagen");
    while (totalL < 15) {
    while (!Serial.available()) {
      // Espera a que haya datos disponibles en el monitor serial
    }

    while (Serial.available() > 0) {
      dato = Serial.read();
      Serial.print(dato);
      // Abre el archivo en modo "append"
      miArchivo = SD.open("/miArchivo.txt");
      if (miArchivo) {
        miArchivo.print(dato);
        miArchivo.close();
      } else {
        Serial.print("error al escribir en la tarjeta");
      }
    }
  // Incrementar el contador de líneas
    Serial.print("Linea: ");
    Serial.println(totalL);
    totalL++;
    if(totalL == 16) {
    Serial.print("Dibujo finalizado");
    }  
  }
  }
  }