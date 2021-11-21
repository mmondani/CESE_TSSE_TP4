#include "unity.h"
#include "ringBuffer.h"



#define ARRAY_LEN       10
#define BUFFER_DATA     0x28

static ringBuffer_t rb;
static uint8_t array[ARRAY_LEN];


void setUp (void) 
{
    for (uint8_t i = 0; i < ARRAY_LEN; i++)
    {
        array[i] = 0;
    }

    ringBuffer_init(&rb, array, ARRAY_LEN);
}


/* Luego de inicializar el ringBuffer, los punteros de entrada/salida y la cantidad de bytes deben estar en 0 */
void test_punteros_y_count_inician_en_cero (void) 
{
    ringBuffer_t rb;
    uint8_t array[ARRAY_LEN];

    ringBuffer_init(&rb, array, ARRAY_LEN);

    TEST_ASSERT_EQUAL_UINT(0, rb.ptrIn);
    TEST_ASSERT_EQUAL_UINT(0, rb.ptrOut);
    TEST_ASSERT_EQUAL_UINT(0, rb.count);
}


/* Sin insertar ningún byte en el buffer, debe informar el largo del array como cantidad de bytes libres */
void test_buffer_vacio_informa_todos_los_bytes_libres (void) 
{
    uint32_t bytesLibres = 0;

    bytesLibres = ringBuffer_getFreeSpace(&rb);

    TEST_ASSERT_EQUAL_UINT(ARRAY_LEN, bytesLibres);
}


/* Al insertar un byte en el ringBuffer, este byte se debe escribir en la primera posición del array */
void test_byte_se_inserta_primera_posicion (void) 
{
    ringBuffer_put(&rb, BUFFER_DATA);

    TEST_ASSERT_EQUAL_UINT(BUFFER_DATA, array[0]);
}


/* La cantidad de espacio libre debe diminuir cuando se insertan bytes en el ringBuffer */
void test_cantidad_bytes_libres (void) 
{
    uint32_t bytesLibres = 0;

    ringBuffer_put(&rb, BUFFER_DATA);
    ringBuffer_put(&rb, BUFFER_DATA);
    ringBuffer_put(&rb, BUFFER_DATA);

    bytesLibres = ringBuffer_getFreeSpace(&rb);

    TEST_ASSERT_EQUAL_UINT(ARRAY_LEN - 3, bytesLibres);
}


/* Informar la cantidad de bytes que fueron insertados y todavía no removidos */
void test_cantidad_bytes_pendientes (void) 
{
    uint32_t bytesPendientes = 0;

    ringBuffer_put(&rb, BUFFER_DATA);
    ringBuffer_put(&rb, BUFFER_DATA);
    ringBuffer_put(&rb, BUFFER_DATA);

    bytesPendientes = ringBuffer_getPending(&rb);

    TEST_ASSERT_EQUAL_UINT(3, bytesPendientes);
}


/* Al remover un byte, debe retornar el primer byte pendiente de ser leido */
void test_primer_byte_leido (void) 
{
    uint8_t byteLeido = 0;

    ringBuffer_put(&rb, BUFFER_DATA);
    ringBuffer_put(&rb, BUFFER_DATA + 1);
    ringBuffer_put(&rb, BUFFER_DATA + 2);

    byteLeido = ringBuffer_remove(&rb);

    TEST_ASSERT_EQUAL_UINT8(BUFFER_DATA, byteLeido);
}


/* Al remover un byte, la cantidad de bytes pendientes debe reducirse en uno */
void test_bytes_pendientes_despues_de_ser_leidos (void) 
{
    uint32_t bytesPendientes = 0;

    ringBuffer_put(&rb, BUFFER_DATA);
    ringBuffer_put(&rb, BUFFER_DATA);
    ringBuffer_put(&rb, BUFFER_DATA);

    ringBuffer_remove(&rb);

    bytesPendientes = ringBuffer_getPending(&rb);

    TEST_ASSERT_EQUAL_UINT(2, bytesPendientes);
}


/* Permitir revisar el próximo byte a ser leido sin eliminarlo del ringBuffer */
void test_revisar_sin_eliminar (void) 
{
    uint8_t byteLeido = 0;
    uint32_t bytesPendientes = 0;

    ringBuffer_put(&rb, BUFFER_DATA);
    ringBuffer_put(&rb, BUFFER_DATA + 1);
    ringBuffer_put(&rb, BUFFER_DATA + 2);

    byteLeido = ringBuffer_peek(&rb);
    bytesPendientes = ringBuffer_getPending(&rb);

    TEST_ASSERT_EQUAL_UINT8(3, bytesPendientes);
}


/* Permitir reiniciar el ringBuffer, poniendo en 0 los punteros de entrada/salida y la cantidad de bytes a leer */
void test_reiniciar_ring_buffer (void) 
{
    ringBuffer_put(&rb, BUFFER_DATA);
    ringBuffer_put(&rb, BUFFER_DATA + 1);
    ringBuffer_put(&rb, BUFFER_DATA + 2);

    ringBuffer_flush(&rb);

    TEST_ASSERT_EQUAL_UINT(0, rb.ptrIn);
    TEST_ASSERT_EQUAL_UINT(0, rb.ptrOut);
    TEST_ASSERT_EQUAL_UINT(0, rb.count);
}