/*
     Autores: David Fierro / Antonio Marquez
     Descripcion: Codigo Minisumo materia microrobotica
*/

#include "parametros.h"
#include "robot_utils.h"


int movimiento = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
boolean validar_linea()
{
  /*
      Autor:        David Fierro
      Descripcion:  Valida si el robot toca o no la linea blanca y genera movimientos correctivos
                      analogRead(A1): Sensor izquierdo
                      analogRead(A2): Sensor central
                      analogRead(A4): Sensor derecho
      Parametros:   void
      Retorno:      ret: Booleano que indica si un sensor tiene contacto con la liena blanca
                      true: No hay contacto con linea blanca
                      false: Hay contacto con linea blanca
  */

  boolean ret = (analogRead(A1) > UMBRAL_SENSOR_LINEA && analogRead(A2) > UMBRAL_SENSOR_LINEA && analogRead(A4) > UMBRAL_SENSOR_LINEA);

  if (!ret)
  {
    switch (movimiento)
    {
      case 1:
        // El robot va hacia adelante
        movimiento = marcha_atras(VELOCIDAD);
        delay(TIEMPO_BACK);
        movimiento = giro_propio_eje(VELOCIDAD, 'R');
        delay(TIEMPO_BACK);
        break;

      case 2:
        // El robot ba hacia atras
        movimiento = marcha_adelante(VELOCIDAD);
        delay(TIEMPO_BACK);
        movimiento = giro_propio_eje(VELOCIDAD, 'R');
        delay(250);
        break;

      case 3:
        // El robot va hacia la izquierda
        movimiento = giro_propio_eje(VELOCIDAD, 'R');
        delay(250);
        break;

      case 4:
        // El robot va hacia la derecha
        movimiento = giro_propio_eje(VELOCIDAD, 'L');
        delay(250);
        break;

      default:
        // Movimiento no especificado, detener robot
        robot_detener();
        delay(250);
    }

  }

  return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
boolean atacar()
{
  /*
     Autor:        David Fierro
     Descripcion:  Si un objeto aparece en uno de los sensores, lo centra y ataca
     Parametros:   velocidad: Velocidad del robot (0 - 100)
     Retorno:      mvt: indice del movimiento que se esta haciendo
  */


  bool obj_izq = digitalRead(SENSOR_DST_IZQ);
  bool obj_cnt = digitalRead(SENSOR_DST_CNT);
  bool obj_der = digitalRead(SENSOR_DST_DER);

  boolean ataque = false;

  if (obj_cnt)
  {
    // Se detecto un objeto en el sensor central, detener robot
    ataque = true;
    movimiento = marcha_adelante(VELOCIDAD);
  }
  else if (obj_izq && !obj_cnt)
  {
    // El objeto esta cargado a la izquierda, girar para centrarlo
    ataque = true;
    movimiento = giro_propio_eje(VELOCIDAD, 'R');
  }
  else if (obj_der && !obj_cnt)
  {
    // El objeto esta cargado a la derecha, girar para centrarlo
    ataque = true;
    movimiento = giro_propio_eje(VELOCIDAD, 'L');
  }
  else
  {
    ataque = false;
  }
  return ataque;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {

  while (digitalRead(DPS) == 0)
  {
    robot_detener();
    // El robot no ha sido activado, no hacer nada
  }

  // Detener motores el tiempo antes del combate
  delay(TIEMPO_START);

  while (digitalRead(DPS) == 1)
  {
    if (validar_linea())
    {
      if (!atacar())
      {
        movimiento = marcha_adelante(VELOCIDAD);
      }
    }
  }





}
