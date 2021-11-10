/*
   Titulo:         robot_utils.h
   Autores:        David Fierro
   Descripcion:    Archivo en el que se almacenan las funciones del robot
*/

#include <xmotion.h>
#include "parametros.h"

// Variable global que guarda el valor del movimiento de tobot, es usado para el movimiento correctivo
int movimiento = 0;

boolean giro_pendiente = false;

int timer_giro = 0;
int tiempo_giro = 0;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void marcha_adelante(int vel)
{
  /*
     Autor:        David Fierro
     Descripcion:  Funcion que hace avanzar el robot hacia adelante tomando en cuenta el valor de los parametros para que
                   vaya en linea recta
     Parametros:   vel: Velocidad deseada para la accion (0 - 100)
     Retorno:      void
  */

  // Asignacion de valores para velocidad de cada motor
  int velocidad_motores = map(vel, 0, 100, 0, 255 / FC_FWD);

  // Si el robor esta en produccion, activa motores, caso contrario imprime en monitor serial
  if (PRODUCCION == true)
    xmotion.MotorControl(velocidad_motores * FC_FWD, velocidad_motores);
  else
    Serial.println("Marcha adelante");

  // Se guarda el movimiento generado en variable global
  movimiento = MVT_FWD;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void marcha_atras(int vel)
{
  /*
     Autor:        David Fierro
     Descripcion:  Funcion que hace avanzar el robot hacia atras tomando en cuenta el valor de los parametros para que
                   vaya en linea recta
     Parametros:   vel: Velocidad deseada para la accion (0 - 100)
     Retorno:      void
  */

  // Asignacion de valores para velocidad de cada motor
  int velocidad_motores = map(vel, 0, 100, -0, -255 / FC_BWD);

  // Si el robor esta en produccion, activa motores, caso contrario imprime en monitor serial
  if (PRODUCCION == true)
    xmotion.MotorControl(velocidad_motores * FC_BWD, velocidad_motores);
  else
    Serial.println("Marcha atras");

  // Se guarda el movimiento generado en variable global
  movimiento = MVT_BWD;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void giro_propio_eje(int vel, char direccion)
{
  /*
     Autor:        David Fierro
     Descripcion:  Funcion que hace girar el robot en su propio eje
     Parametros:   vel: Velocidad deseada para la accion (0 - 100)
                   direccion: Caracter que indica hacia donde se quiere girar (L o R)
     Retorno:      void
  */

  int v_izq = map(vel, 0, 100, 0, 255);
  int v_der = v_izq;

  if (direccion == 'L')
  {
    // El motor izquierdo debe ir hacia atras
    v_izq *= -1;
    // Se guarda el movimiento generado en variable global
    movimiento = MVT_LFT;
  }
  else
  {
    // El motor derecho debe ir hacia atras
    v_der *= -1;
    // Se guarda el movimiento generado en variable global
    movimiento = MVT_RGT;
  }

  if (PRODUCCION == true)
    xmotion.MotorControl(v_izq, v_der);
  else
    Serial.println("Giro " + String(direccion));
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void robot_detener()
{
  /*
     Autor:        David Fierro
     Descripcion:  Funcion que detiene el robot
     Parametros:   void
     Retorno:      void
  */

  xmotion.StopMotors(1);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void giro_aleatorio()
{
  /*
     Autor:        David Fierro
     Descripcion:  Funcion hace girar al robot hacia una direccion aleatoria
     Parametros:   void
     Retorno:      void
  */

  // Esta funcion solo da un 1 o 0, dependiendo del valor, se gira el robot hacia cada sentido
  if (random(0, 2) == 1)
    giro_propio_eje(VELOCIDAD_BUSQUEDA, 'R');
  else
    giro_propio_eje(VELOCIDAD_BUSQUEDA, 'L');

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
boolean atacar()
{
  /*
      Autor:        David Fierro
      Descripcion:  Si un objeto aparece en uno de los sensores, lo centra y ataca
      Parametros:   velocidad: Velocidad del robot (0 - 100)
      Retorno:      ataque: booleano que indica estado de ataque, cuando está atacando ignora estrategias
                      true:   el robot est atacando
                      false:  el robot no encontró algo que atacar
  */


  // Lectura de sensores de distancia
  bool obj_izq = digitalRead(SENSOR_DST_IZQ);
  bool obj_cnt = digitalRead(SENSOR_DST_CNT);
  bool obj_der = digitalRead(SENSOR_DST_DER);

  // Inicializacion de bandera
  boolean ataque = false;

  if (obj_cnt && obj_der && obj_izq)
  {
    // Se detecto un objeto centrado, acelerar a velocidad de ataque
    ataque = true;
    marcha_adelante(VELOCIDAD_ATAQUE);
  }
  else if (obj_izq && !obj_cnt)
  {
    // El objeto esta cargado a la izquierda, girar para centrarlo
    ataque = true;
    giro_propio_eje(VELOCIDAD_ATAQUE, 'R');
  }
  else if (obj_der && !obj_cnt)
  {
    // El objeto esta cargado a la derecha, girar para centrarlo
    ataque = true;
    giro_propio_eje(VELOCIDAD_ATAQUE, 'L');
  }

  return ataque;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void correccion_movimiento()
{
  /*
      Autor:        David Fierro
      Descripcion:  Asigna el movimiento contrario para evitar salir del dojo, despues del movimiento de correccion
                    genera un giro en sentido aleatorio
      Parametros:   void
      Retorno:      void
  */

  if (movimiento == MVT_BWD)
  {
    // El robot va hacia atras, la correccion es ir hacia adelante
    marcha_adelante(VELOCIDAD_BUSQUEDA);
  }
  else
  {
    // El robot va hacia atras
    marcha_atras(VELOCIDAD_BUSQUEDA);
  }

  // Delay simple para salir de la linea
  delay(TIEMPO_BACK);

  // Una vez fuera de peligro se inicia un giro en sentido aleatorio
  giro_aleatorio();
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
       Retorno:      !contacto_linea: Booleano que indica si un sensor tiene contacto con la liena blanca
                       true: No hay contacto con linea blanca
                       false: Hay contacto con linea blanca
  */

  // Asigna el valor de los sensores de linea
  int contacto_linea = (analogRead(A1) < UMBRAL_SENSOR_LINEA);
  contacto_linea |= (analogRead(A2) < UMBRAL_SENSOR_LINEA) << 1;
  contacto_linea |= (analogRead(A4) < UMBRAL_SENSOR_LINEA) << 2;


  if (contacto_linea != 0b000)
  {
    giro_pendiente = true;

    switch (contacto_linea)
    {
      case 0b001:
        // Unicamente el sensor derecho ha tocado la linea
        // Girar levemente para hacer que el robot quede lo mas centrado posible antes de enviar movimiento correctivo
        giro_propio_eje(VELOCIDAD_BUSQUEDA, 'L');
        delay(TIEMPO_BACK / 5);

        // Movimiento correctivo
        correccion_movimiento();
        break;

      case 0b100:
        // Unicamente el sensor derecho ha tocado la linea
        // Girar levemente para hacer que el robot quede lo mas centrado posible antes de enviar movimiento correctivo
        giro_propio_eje(VELOCIDAD_BUSQUEDA, 'R');
        delay(TIEMPO_BACK / 5);

        // Movimiento correctivo
        correccion_movimiento();
        break;

      default:
        // Cualquier otra combinacion de sensores ha tocado la linea
        // Movimiento correctivo
        correccion_movimiento();
    }

    // Inicializa el timer de giro y configura un tiempo de giro aleatorio
    timer_giro = 0;
    tiempo_giro = random(TIEMPO_GIRO_MIN, TIEMPO_GIRO_MAX);

  }
  else if (giro_pendiente == true)
  {
    // Ha ocurrido el movimiento correctivo, ahora es necesario que el robot gire para cambiar de direccion
    // Este enfoque es mejor que un delay porque permite detectar y atacar objetos en cualquier etapa de giro

    // Se sobreescribe varible de sensores para evitar que se realice el movimiento de estrategia
    contacto_linea = true;

    if (timer_giro < tiempo_giro)
    {
      // El tiempo de giro aun no ha transcurrido
      // Aumentar el timer de giro
      timer_giro++;

      // Verifica si hay algun enemigo cerca
      atacar();

      // SOLO PARA DESARROLLO: Muestra el valor del timer
      if (PRODUCCION == false)
        Serial.println("Timer giro: " + String(timer_giro));
    }
    else
    {
      // El tiempo de giro ha finalizado

      // Las variables necesarias se restablecen
      giro_pendiente = false;
      tiempo_giro = 0;
    }

  }

  return !contacto_linea;
}
