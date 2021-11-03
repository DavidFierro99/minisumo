
#include <xmotion.h>

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
