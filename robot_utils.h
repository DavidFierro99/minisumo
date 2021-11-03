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
    girando = false;
    robot_detener();
  }
  else if (obj_izq && !obj_cnt)
  {
    girando = true;
    xmotion.Left0(velocidad, 1);
  }
  else if (obj_der && !obj_cnt)
  {
    girando = true;
    xmotion.Right0(velocidad, 1);
  }
  else if (!girando)
  {
    if(random(0,2) == 1)
    {
      girando = true;
      xmotion.Right0(velocidad, 1);
    }
    else
    {
      girando = true;
      xmotion.Left0(velocidad, 1);   
    }
         
  }
  
  
    


   

}
