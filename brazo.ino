// Pablo Riveros
//
#include <Servo.h>


//Funcion para cambiar los valores predeterminados de el program
void cambiarValores(int& v1, int& v2, int& v3, int& v4, int &v5, int &v6, int &v7, int &v8);
void puno();
void saludar();
void tirarObjeto();
void tomarObjeto();
void moverServos();
void mostrarValores();
void regresarAPosicionInicial();

//Declaro una matriz para los servos
Servo servos[4];
//palabra para mover los servos
String palabraClave = "inicia";
//palabra que se recibe de la consola
String palabraRecibida;
//palabra clave para camibar valores de los servos
String Cambiar = "cambiar";
//palabra clave para ver los valores en el monitor
String ver = "ver";
//Otras palabras clave para hacer movimientos predeterminados
String a = "puno";
String b = "saludar";
String c = "tomar";
String d ="tirar";
String otrasFunciones= "otras";
 //Variable para terminar un mensaje de error
//bool error =false;

//Mensajes
bool mensaje = true;

// Valores predeterminados de los servos en 0
//primer y segundo movimiento
int valores[8] = {90, 90, 90, 90, 90, 90 ,90, 90};



void setup()
{
  //inicio serial
Serial.begin(9600);
  //Declaro los pines de los servos
  servos[0].attach(5);
  
  servos[1].attach(9);
 
  servos[2].attach(10);
   
  servos[3].attach(11);
}
//Variables para indicarle a un mensaje cuando repetirse
unsigned long previousMillis =0;
const long interval = 8000;

void loop()
{   
  //primeros mensajes
  if(mensaje)
  {
     Serial.println("Escribe 'inicia', para mover los servos.");
    Serial.println("Escriba 'cambiar', para poner otros valores a los servos");
    Serial.println("Escriba 'ver', para ver los valores de los servos");
    Serial.println("O escriba alguna de estas funciones:");
    Serial.println("*puno\n*saludar\n*tomar\n*tirar");
  mensaje= false;
}
  
 //comprueba si hay datos en el monitor
 //Asigna a la variable 'palbraRecibida' la palabra que se envia desde el monitor
   if (Serial.available()) {
    palabraRecibida = Serial.readString();
    palabraRecibida.trim();
     //Comparación de la 'palbraRecibida' con los comandos predeterminados, para ejecutar su código.
     if( palabraRecibida == Cambiar){
       Serial.println("Escribe primero los primeros movimietos de los servos, y luego los segundos");
       Serial.println("Los primeros 4 numeros son para el primer movimiento, y los otros 4 para el segundo");
       Serial.println("A la Base corresponden los numeros 1 y 5");
       Serial.println("A el pirmer brazo corresponden son los numeros 2 y 6");
       Serial.println("A el segundo brazo corresponden los numeros 3 y 7");
       Serial.println("A la pinza corresponden los numeros 4 y 8");
       Serial.println("Recuerda que el rango es de 0 a 180");
       Serial.println("Ingrese los valores (separados por espacio):");
   
       cambiarValores(valores[0], valores[1], valores[2], valores[3], valores[4], valores[5], valores[6], valores[7]); //llama a la funcion cambiarValores.
   //Asignar valores a la variable valores[], en caso de que sea mayor de 180
      if(valores[3] >= 90){
      valores[3] = 90;
      }
      
      if (valores [7] >= 90){
        valores[7] =90;
      }
     }   

    else if(palabraRecibida == ver){
       mostrarValores();
     }

    //comprueba si la palabra recibida es igual a la palabra clave
    //para iniciar el programa
    else if (palabraRecibida == palabraClave) {
      Serial.println(" ¡Comenzando!");
      
      //mueve los servos  
      moverServos();
      regresarAPosicionInicial();
    } 
    else if(palabraRecibida == a){
      puno();
    }
      else if(palabraRecibida == b){
      saludar();
    }
      else if(palabraRecibida == c){
      tomarObjeto();
    }
      else if(palabraRecibida == d){
      tirarObjeto();
    }
      else if(palabraRecibida == otrasFunciones){
       Serial.println("Escriba alguna de estas funciones:");
    Serial.println("*puno\n*saludar\n*tomar\n*tirar");
    }

  //Muestra mensajes si no coincdela palabra recibida con la clave
  else{
  unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
        Serial.println("Escribe 'inicia', 'cambiar', 'ver' o 'otras'");
        }
      }
    }

}

// Función para cambiar los valores
void cambiarValores(int& v1, int& v2, int& v3, int& v4, int &v5, int &v6, int &v7, int &v8) {
  // Leer los valores con un contador y un pequeño retraso
  for (int i = 0; i < 8; i++) {
      valores[i] = Serial.parseInt();
      delay(800); // Pequeño retraso para leer los valores en el monitor

      // Ejecuta unos mensajes si están fuera del rango
      if (valores[i] > 180) {
          Serial.print("Error. El valor ingresado para el servo ");
          Serial.print(i + 1);
          Serial.println("\nFUERA DE RANGO\nes mayor a 180. Se ha ajustado a 180 grados.");
          valores[i] = 180;
      } else if (valores[i] < 0) {
          Serial.print("Error. El valor ingresado para el servo ");
          Serial.print(i + 1);
          Serial.println("\nFUERA DE RANGO\nes menor que 0. Se ha ajustado a 0 grados.");
          valores[i] = 0;
      }
 while (!(Serial.available() >= 1)) {
    Serial.read();
  }
  //Vacia el buffer completamente leyendo y descartando los datos a el no asignarle un variable
  Serial.flush(); //Vacia el buffer de "transmisión"

}
 Serial.println("Valores actualizados");
}
//Fucnión para ver valores
void mostrarValores(){
Serial.println("Valores asignados a los servos:");
int newServo = 0;
  for (int i = 0; i < 8; i++) {
    if(i < 4){
      Serial.print("Servo ");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.println(valores[i]);
    }
    if(i>=4){
      Serial.print("Servo ");
      Serial.print(newServo+1);
      Serial.print(": ");
      Serial.println(valores[i]);
      newServo++;
    }
  }
}

//Función para mover los servos
void moverServos(){
  int newServo = 0;
  for(int i = 0; i < 8; i++){
    if(i < 4){
      servos[i].write(valores[i]);
      delay(1000);
      Serial.print("Servo ");
      Serial.print(i + 1);
      Serial.print(" movido a: ");
      Serial.println(valores[i]);
    }
    if(i>=4){
      servos[newServo].write(valores[i]);
      delay(1000);
      Serial.print("Servo ");
      Serial.print(newServo+1);
      Serial.print(" movido a: ");
      Serial.println(valores[i]);
      newServo++;
    }
    
  }
}

// Función para regresar a la posición inicial
void regresarAPosicionInicial() {
    Serial.println("Regresando a la posición inicial...");
    for (int j = 0; j < 4; j++) {
        servos[j].write(90); // Regresa cada servo a 90 grados
        delay(1000); // Espera un segundo entre movimientos
        Serial.print("Servo ");
        Serial.print(j + 1);
        Serial.println(" regresado a 90 grados.");
    }
}

void tomarObjeto(){
  valores[0] = 90;
  delay(50);
  valores[1] = 170;
    delay(50);
  valores[2] = 0;
    delay(50);
  valores[3] = 0;
    delay(50);
  valores[4] = 0;
    delay(50);
  valores[5] = 120;
    delay(50);
  valores[6] = 0;
    delay(50);
  valores[7] = 90;

    int newServo = 0;
  for(int i = 0; i < 8; i++){
    if(i < 4){
      servos[i].write(valores[i]);
      delay(1000);
      Serial.print("Servo ");
      Serial.print(i + 1);
      Serial.print(" movido a: ");
      Serial.println(valores[i]);
    }
    if(i>=4){
      servos[newServo].write(valores[i]);
      delay(1000);
      Serial.print("Servo ");
      Serial.print(newServo+1);
      Serial.print(" movido a: ");
      Serial.println(valores[i]);
      newServo++;
    }
  }
 delay(1000);
  regresarAPosicionInicial();
}

void tirarObjeto(){
   valores[0] = 90;
  delay(50);
  valores[1] =90;
    delay(50);
  valores[2] = 90;
    delay(500);
  valores[3] = 0;
    delay(100);
  valores[4] = 0;
    delay(50);
  valores[5] =90;
    delay(50);
  valores[6] = 180;
    delay(50);
  valores[7] = 90;

    int newServo = 0;

  for(int i = 0; i < 8; i++){
    if(i < 4){
      servos[i].write(valores[i]);
      delay(1000);
      Serial.print("Servo ");
      Serial.print(i + 1);
      Serial.print(" movido a: ");
      Serial.println(valores[i]);
    }
    if(i>=4){
      servos[newServo].write(valores[i]);
      delay(1000);
      Serial.print("Servo ");
      Serial.print(newServo+1);
      Serial.print(" movido a: ");
      Serial.println(valores[i]);
      newServo++;
    }
 
  }
    delay(1000);
    regresarAPosicionInicial();
}

void saludar(){
    valores[0] = 90;
  delay(50);
  valores[1] = 90;
    delay(50);
  valores[2] = 90;
    delay(50);
  valores[3] = 0;
  delay(50);
  valores[4] = 90;
  delay(50);
  valores[5] = 90;
  delay(50);
  valores[6] = 90;
  delay(50);
  valores[7] = 90;

    int newServo = 0;
  for(int i = 0; i < 8; i++){
    if(i < 4){
      servos[i].write(valores[i]);
      delay(1000);
      Serial.print("Servo ");
      Serial.print(i + 1);
      Serial.print(" movido a: ");
      Serial.println(valores[i]);
    }
    if(i>=4){
      servos[newServo].write(valores[i]);
      delay(1000);
      Serial.print("Servo ");
      Serial.print(newServo+1);
      Serial.print(" movido a: ");
      Serial.println(valores[i]);
      newServo++;
    }

  }
 delay(1000);
     regresarAPosicionInicial();
}
void puno(){
    valores[0] = 90;
  delay(50);
  valores[1] = 90;
    delay(50);
  valores[2] = 0;
    delay(50);
  valores[3] = 0;
    delay(50);
  valores[4] = 90;
    delay(50);
  valores[5] = 120;
    delay(50);
  valores[6] = 0;
    delay(50);
  valores[7] = 90;

    int newServo = 0;
  for(int i = 0; i < 8; i++){
    if(i < 4){
      servos[i].write(valores[i]);
      delay(1000);
      Serial.print("Servo ");
      Serial.print(i + 1);
      Serial.print(" movido a: ");
      Serial.println(valores[i]);
    }
    if(i>=4){
      servos[newServo].write(valores[i]);
      delay(1000);
      Serial.print("Servo ");
      Serial.print(newServo+1);
      Serial.print(" movido a: ");
      Serial.println(valores[i]);
      newServo++;
    }
  } 
 delay(1000);
     regresarAPosicionInicial();
}
