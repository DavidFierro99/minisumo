/*
 * Titulo:         Parametros.h
 * Autores:        David Fierro
 * Descripcion:    Archivo en el que se almacenan los parametros definidos por el usuario, cada
 *                 seccion de parametros estará definida en el archivo
*/

// Umbral minimo del valor de linea blanca, debajo de este valor se considera que la linea es blanca
#define UMBRAL_SENSOR_LINEA 300

// Tiempo en el que inicia el combate
#define TIEMPO_START 5000

// Tiempo en milisegundos en el que se aleja el robot de una linea
#define TIEMPO_BACK 350

// Pines digitales de sensores de distancia
#define SENSOR_DST_IZQ 0
#define SENSOR_DST_CNT 1
#define SENSOR_DST_DER 2

// Pines digitales del dipswitch integrado
#define DP1 5
#define DP2 6 
#define DPS 7 

// Factor de correccion para hacer que el robot vaya en linea recta. Aumentar si el robot gira a la derecha
#define FC_FWD 1.05

// Factor de correccion para hacer que el robot vaya en linea recta. Aumentar si el robot gira a la derecha
#define FC_BWD 1.25

// Velocidad por defecto
#define VELOCIDAD 100

// Constantes de movimiento
#define MVT_FWD 1
#define MVT_BWD 2
#define MVT_LFT 3
#define MVT_RGT 4
