#include <SPI.h>
#include <SD.h>

#define SSpin 5
int opcionElegida;
File miArchivo;
int totalL = 0;
char dato;
String Data = "";  

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
  
  miArchivo = SD.open("/");  // Abre el directorio raíz de la tarjeta SD
  printDirectory(miArchivo, 0);  // Llama a la función para imprimir la estructura de directorios y archivos

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
    Serial.println("Cuenta con un máximo de 10 lineas para elaborar una imagen");
    while (totalL < 10) {
    while (!Serial.available()) {
      // Espera a que haya datos disponibles en el monitor serial
    }

    while (Serial.available() > 0) {
      dato = Serial.read();
      Serial.print(dato);
      Data += dato;
      // Abre el archivo en modo "append"
      miArchivo = SD.open("/miArchivo.txt", FILE_WRITE);
      if (miArchivo) {
        miArchivo.print(Data);
        miArchivo.close();
      } else {
        Serial.print("error al escribir en la tarjeta");
      }
    }
  // Incrementar el contador de líneas
    totalL++;
    delay(1000);
    if(totalL == 10) {
    Serial.println("Dibujo finalizado");
    Serial.println("Elija otra opción");
    }  
  }
  }
  }

void printDirectory(File dir, int numTabs) {
  // Lista y muestra la estructura de directorios y archivos en la tarjeta SD
  while (true) {
    File entry = dir.openNextFile();  // Abre el siguiente archivo o directorio en el directorio actual
    if (!entry) {
      // No hay más archivos
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');  // Agrega sangría para mostrar la estructura de directorios
    }
    Serial.print(entry.name());  // Muestra el nombre del archivo o directorio
    if (entry.isDirectory()) {
      Serial.println("/");  // Si es un directorio, muestra "/"
      printDirectory(entry, numTabs + 1);  // Llama a la función para mostrar el contenido del directorio
    } else {
      // Los archivos tienen tamaños, los directorios no
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);  // Muestra el tamaño del archivo en bytes
    }
    entry.close();  // Cierra el archivo o directorio
  }
}