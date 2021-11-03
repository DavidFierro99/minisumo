/*  
 *   Autores: David Fierro / Antonio Marquez
 *   Descripcion: Codigo Minisumo materia microrobotica
*/

#include "parametros.h"
#include "robot_utils.h"


void setup() {
  // Detener motores
  robot_detener();
  
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
  Serial.println("");

  // Delay entre lecturas para estabilidad
  delay(1000);       
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
boolean validacion_linea()
{
  /*
   * Autor:       David Fierro
   * Descripcion: Prueba de sensores de proximidad y de linea 
   *              analogRead(A1): Sensor izquierdo
   *              analogRead(A2): Sensor central
   *              analogRead(A4): Sensor derecho
   * Parametros:  void
   * Retorno:     void
   */
  
  return (analogRead(A1) < UMBRAL_SENSOR_LINEA || analogRead(A2) < UMBRAL_SENSOR_LINEA || analogRead(A4) < UMBRAL_SENSOR_LINEA);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {

  while (digitalRead(DPS) == 0) 
  { 
    // Detener motores
    robot_detener();
    delay(3000);
  }
  
  if (validacion_linea())
  {
    marcha_atras(100);
    delay(500);
  }
  else
  {
    
  }
    

  delay(1);
  
}
