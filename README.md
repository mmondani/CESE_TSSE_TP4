CESE - TSSE: TP4 - Testing Unitario
=======================

Este repositorio contiene un test unitario para el módulo ringBuffer del trabajo final del posgrado. Este módulo se encarga de implementar un buffer circular que puede contener uint8_t.

El test unitario fue implementado utilizando ceedling.

## Requisitos

El buffer circular implementado debe cumplir los siguientes requisitos

- Luego de inicializar el ringBuffer, los punteros de entrada/salida y la cantidad de bytes deben estar en 0.
- Sin insertar ningún byte en el buffer, debe informar el largo del array como cantidad de bytes libres.
- Al insertar un byte en el ringBuffer, este byte se debe escribir en la primera posición del array.
- La cantidad de espacio libre debe disminuir cuando se insertan bytes en el ringBuffer.
- Informar la cantidad de bytes que fueron insertados y todavía no removidos.
- Al remover un byte, debe retornar el primer byte pendiente de ser leido.
- Al remover un byte, la cantidad de bytes pendientes debe reducirse en uno.
- Permitir revisar el próximo byte a ser leido sin eliminarlo del ringBuffer.
- Permitir reiniciar el ringBuffer, poniendo en 0 los punteros de entrada/salida y la cantidad de bytes a leer