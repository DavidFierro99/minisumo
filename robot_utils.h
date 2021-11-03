#include <xmotion.h>
#include "parametros.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void marcha_adelante(int velocidad)
{
  /*
   * Autor:        David Fierro
   * Descripcion:  Funcion que hace avanzar el robot hacia adelante tomando en cuenta el valor de los parametros para que 
   *               vaya en line recta
   * Parametros:   velocidad: Velocidad del robot (0 - 100)
   * Retorno:      void
   */
  
  int velocidad_motores = map(velocidad, 0, 100, 0, 255/FC_FWD);
  
  xmotion.MotorControl(velocidad_motores * FC_FWD, velocidad_motores);
   
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void marcha_atras(int velocidad)
{
  /*
   * Autor:        David Fierro
   * Descripcion:  Funcion que hace avanzar el robot hacia atras tomando en cuenta el valor de los parametros para que 
   *               vaya en line recta
   * Parametros:   velocidad: Velocidad del robot (0 - 100)
   * Retorno:      void
   */

  int velocidad_motores = map(velocidad, 0, 100, -0, -255/FC_BWD);
  
  xmotion.MotorControl(velocidad_motores * FC_BWD, velocidad_motores);
   
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void robot_detener()
{
  /*
   * Autor:        David Fierro
   * Descripcion:  Funcion que detiene el robot
   * Parametros:   void
   * Retorno:      void
   */

  xmotion.StopMotors(10);  

}

void giro_propio_eje(int velocidad, char direccion)
{
  /*
   * Autor:        David Fierro
   * Descripcion:  Funcion que hace girar el robot en su propio eje
   * Parametros:   velocidad: Velocidad del robot (0 - 100)
   *               direccion: Caracter que indica hacia donde se quiere girar (L o R)
   * Retorno:      void
   */

  int v_izq = map(velocidad, 0, 100, 0, 255);
  int v_der = v_izq;

  if(direccion == 'L')
    v_izq*=-1;
  else
    v_der*=-1;
  
  xmotion.MotorControl(v_izq, v_der);
   
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool girando = false;
void seguir_objeto(int velocidad)
{
  /*
   * Autor:        David Fierro
   * Descripcion:  Sigue un objeto sin atacarlo
   * Parametros:   velocidad: Velocidad del robot (0 - 100)
   * Retorno:      void
   */

  bool obj_izq = digitalRead(SENSOR_DST_IZQ);
  bool obj_cnt = digitalRead(SENSOR_DST_CNT);
  bool obj_der = digitalRead(SENSOR_DST_DER);

  

  if(obj_cnt)
  {
    // Se detecto un objeto en el sensor central, detener robot
    girando = false;
    robot_detener();
  }
  else if (obj_izq && !obj_cnt)
  {
    // El objeto esta cargado a la izquierda, girar para centrarlo
    girando = true;
    giro_propio_eje(velocidad, 'R');
  }
  else if (obj_der && !obj_cnt)
  {
    // El objeto esta cargado a la derecha, girar para centrarlo
    girando = true;
    giro_propio_eje(velocidad, 'L');
  }
  else if (!girando)
  {
    // No se detecto objeto alguno y la orden de giro no se ha dado
    // Se define un sentido de giro aleatorio
    if(random(0,2) == 1)
    {
      girando = true;
      giro_propio_eje(velocidad, 'R');
    }
    else
    {
      girando = true;
      giro_propio_eje(velocidad, 'L');
    }
         
  }

}
