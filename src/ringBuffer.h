#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include <stdint.h>

/**
 * Estructura para representar un buffer circular
 */
typedef struct
{
	uint8_t* buffer;                /**< array que contiene los bytes del ringBuffer */
	uint32_t len;                   /**< largo del array buffer */
	uint32_t ptrIn;                 /**< posición del array buffer donde se va a escribir el próximo byte */
	uint32_t ptrOut;                /**< posición del array buffer donde se va a leer el próximo byte */
	volatile uint8_t count;         /**< cantidad de bytes pendientes de ser leídos en el ringBuffer */
}ringBuffer_t;

/**
 * @brief Inicializa el buffer circular
 * 
 * @param rb puntero a una estructura de tipo ringBuffer_t
 * @param buffer puntero a un array de uint8_t que va a ser usado por el ringBuffer para almacenar los bytes
 * @param len largo del array buffer
 */
void ringBuffer_init (ringBuffer_t* rb, uint8_t* buffer, uint32_t len);

/**
 * @brief Devuelve la cantidad de bytes libres en el ringBuffer rb
 * 
 * @param rb puntero a una estructura de tipo ringBuffer_t
 * 
 * @return cantidad de bytes libres
 */
uint32_t ringBuffer_getFreeSpace (ringBuffer_t* rb);

/**
 * @brief Devuelve la cantidad de bytes pendientes de ser leidos en el ringBuffer rb
 * 
 * @param rb puntero a una estructura de tipo ringBuffer_t
 * 
 * @return cantidad de bytes pendientes de ser leidos
 */
uint32_t ringBuffer_getPending (ringBuffer_t* rb);

/**
 * @brief Inserta un byte en el ringBuffer rb
 * 
 * @param rb puntero a una estructura de tipo ringBuffer_t
 * @param data byte a insertar en el ringBuffer rb
 */
void ringBuffer_put (ringBuffer_t* rb, uint8_t data);

/**
 * @brief Retorna el primer byte pendiente de ser leído.
 * 
 * Para garantizar que el byte retornado sea válido, antes de llamar a esta función
 * llamar a ringBuffer_getPending para comprobar que hay bytes pendientes.
 * El byte retornado se descarta en el ringBuffer, por lo que no puede volver a ser leído.
 * 
 * @param rb puntero a una estructura de tipo ringBuffer_t
 * 
 * @return primer byte pendiente de ser leído
 */
uint8_t ringBuffer_remove (ringBuffer_t* rb);

/**
 * @brief Retorna el primer byte pendiente de ser leído.
 * 
 * Para garantizar que el byte retornado sea válido, antes de llamar a esta función
 * llamar a ringBuffer_getPending para comprobar que hay bytes pendientes.
 * El byte retornado no se descarta en el ringBuffer.
 * 
 * @param rb puntero a una estructura de tipo ringBuffer_t
 * 
 * @return primer byte pendiente de ser leído
 */
uint8_t ringBuffer_peek (ringBuffer_t* rb);

/**
 * @brief Resetea el ringBuffer
 * 
 * @param rb puntero a una estructura de tipo ringBuffer_t
 */
void ringBuffer_flush (ringBuffer_t* rb);


#endif /* RINGBUFFER_H_ */