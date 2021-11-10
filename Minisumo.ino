/*
     Autores: David Fierro / Antonio Marquez
     Descripcion: Codigo Minisumo materia microrobotica
*/

#include "parametros.h"
#include "robot_utils.h"
#include "robot_tests.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  // Detener motores
  robot_detener();

  // Iniciar monitor serial
  Serial.begin(9600);

  // Declaracion de pines para sensores de distnacia
  pinMode(SENSOR_DST_IZQ, INPUT);
  pinMode(SENSOR_DST_CNT, INPUT);
  pinMode(SENSOR_DST_DER, INPUT);
  
  // Declaracion de pines para dipswitch interno de funciones
  pinMode(DP1, INPUT);
  pinMode(DP2, INPUT);
  pinMode(DPS, INPUT); 

  digitalWrite(DP1, HIGH);
  digitalWrite(DP2, HIGH);
  digitalWrite(DPS, HIGH);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {

  while (digitalRead(DPS) == 0)
  {
    // El robot no ha sido activado, no hacer nada
    robot_detener();
    movimiento = 0;
  }

  // Detener motores el tiempo antes del combate
  delay(TIEMPO_START);

  while (digitalRead(DPS) == 1)
  {
    // Verifica si se ha pisado una linea blanca
    if (validar_linea() == true)
    {
      // Verifica hay un enemigo que atacar
      if (atacar() == false)
      {
        // No hay enemigo ni está en linea, correr estrategia
        marcha_adelante(VELOCIDAD_BUSQUEDA);
      }
    }
    
    delay(1);
  }
}
