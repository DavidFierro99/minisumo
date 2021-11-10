/*
 * Titulo:         robot_tests.h
 * Autores:        David Fierro
 * Descripcion:    Archivo en el que se almacenan las funciones de pruebas del robot
*/

#include "parametros.h"



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool girando = false;
int seguir_objeto()
{
  /*
     Autor:        David Fierro
     Descripcion:  Sigue un objeto sin atacarlo
     Parametros:   void
     Retorno:      mvt: indice del movimiento que se esta haciendo
  */

  bool obj_izq = digitalRead(SENSOR_DST_IZQ);
  bool obj_cnt = digitalRead(SENSOR_DST_CNT);
  bool obj_der = digitalRead(SENSOR_DST_DER);
  int mvt = 0;

  if (obj_cnt)
  {
    // Se detecto un objeto en el sensor central, detener robot
    girando = false;
    robot_detener();
  }
  else if (obj_izq && !obj_cnt)
  {
    // El objeto esta cargado a la izquierda, girar para centrarlo
    girando = true;
    giro_propio_eje(VELOCIDAD_BUSQUEDA, 'R');
  }
  else if (obj_der && !obj_cnt)
  {
    // El objeto esta cargado a la derecha, girar para centrarlo
    girando = true;
    giro_propio_eje(VELOCIDAD_BUSQUEDA, 'L');
  }
  else if (!girando)
  {
    // No se detecto objeto alguno y la orden de giro no se ha dado
    // Se define un sentido de giro aleatorio
    girando = true;
    giro_aleatorio();
  }
  return mvt;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void prueba_sensores()
{
  /*
     Autor:       David Fierro
     Descripcion: Prueba de sensores de proximidad y de linea
     Parametros:  void
     Retorno:     void
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
  Serial.print("SENSOR_DST_IZQ: ");
  Serial.print(digitalRead(SENSOR_DST_IZQ));
  Serial.print("         ");
  Serial.print("SENSOR_DST_CNT: ");
  Serial.print(digitalRead(SENSOR_DST_CNT));
  Serial.print("         ");
  Serial.print("SENSOR_DST_DER: ");
  Serial.print(digitalRead(SENSOR_DST_DER));
  Serial.println("");

  // Delay entre lecturas para estabilidad
  delay(1000);
}
