/*  
 *   Autores: David Fierro / Antonio Marquez
 *   Descripcion: Codigo Minisumo materia microrobotica
*/

#include <xmotion.h>
#include "Parametros.h"


void setup() {
  xmotion.StopMotors(100); // Detener motores
  
  // Iniciar monitor serial
  Serial.begin(9600);

  
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(4, INPUT);

  pinMode(DP1, INPUT); //Dipswitch 1 Declared as Input
  pinMode(DP2, INPUT); //Dipswitch 2 Declared as Input
  pinMode(DPS, INPUT); //Dipswitch 3 Declared as Input
  
  digitalWrite(DP1, HIGH); // Dipswitch Inputs are High (Pull-up made)
  digitalWrite(DP2, HIGH);
  digitalWrite(DPS, HIGH);

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void marcha_adelante(int tiempo)
{
  /*
   * Autor:        David Fierro
   * Parametros:   tiempo: int que indica el tiempo por el que se va a correr el robot
   * Retorno:      void
   */

  xmotion.Right0(RM_FWD_VAL, tiempo);
   
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void prueba_sensores()
{
  /*
   * Autor:       David Fierro
   * Descripcion: Prueba de sensores de proximidad y de linea 
   * Parametros:  void
   * Retorno:     void
   */
   
  int sensorA1 = analogRead(A1);
  int sensorA2 = analogRead(A2);
  int sensorA4 = analogRead(A4);
  
  // Imprime los valores de los sensores
  Serial.println("Entradas analogicas");
  Serial.print("A1: ");
  Serial.print(sensorA1);
  Serial.print("         ");
  Serial.print("A2: ");
  Serial.print(sensorA2);
  Serial.print("         ");
  Serial.print("A4: ");
  Serial.println(sensorA4);
  Serial.println("Entradas digitales");
  Serial.print("D0: ");
  Serial.print(digitalRead(0));
  Serial.print("         ");
  Serial.print("D1: ");
  Serial.print(digitalRead(1));
  Serial.print("         ");
  Serial.print("D2: ");
  Serial.print(digitalRead(2));
  Serial.print("         ");
  Serial.print("D4: ");
  Serial.println(digitalRead(4));

  // Delay entre lecturas para estabilidad
  delay(1000);       
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
 

 /* while (digitalRead(PIN_START) == 0) // Button push is waited. When Button is pushed, it gives 1 value.
  { 
    Serial.print(digitalRead(PIN_START));
    xmotion.UserLed2(100); //Blink User Led 2 100millisecond Intervals.
  }*/

  prueba_sensores();
  delay(100);
  
}
