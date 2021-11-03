/*
 * Titulo:         Parametros.h
 * Autores:        David Fierro
 * Descripcion:    Archivo en el que se almacenan los parametros definidos por el usuario, cada
 *                 seccion de parametros estará definida en el archivo
*/

#define UMBRAL_SENSOR_LINEA 200

// Digital pins de sensores de distancia
#define SENSOR_DST_IZQ 0
#define SENSOR_DST_CNT 1
#define SENSOR_DST_DER 2


#define DP1 5
#define DP2 6 
#define DPS 7 

// Factor de correccion para hacer que el robot vaya en linea recta. Aumentar si el robot gira a la derecha
#define FC_FWD 1.65

// Factor de correccion para hacer que el robot vaya en linea recta. Aumentar si el robot gira a la derecha
#define FC_BWD 1.5
