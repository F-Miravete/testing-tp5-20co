/************************************************************************************************
Copyright (c) 2024, Flavio Miravete <flavio.miravete@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

/** @file
 ** @brief Modulo de Testeos (ceedling)
 **/

/* === Headers files inclusions =============================================================== */

#include "unity.h"
#include "leds.h"

/* === Macros definitions ====================================================================== */

#define TEST_ALL_LEDS_OFF 0x00
#define TEST_ALL_LEDS_ON  0xFF
#define TEST_LED01        1
#define TEST_LED02        2
#define TEST_LED03        3
#define TEST_LED04        4
#define TEST_LED05        5
#define TEST_LED06        6
#define TEST_LED07        7
#define TEST_LED08        8
#define TEST_LED09        9
#define TEST_LED10        10
#define TEST_LED11        11
#define TEST_LED12        12
#define TEST_LED13        13
#define TEST_LED14        14
#define TEST_LED15        15
#define TEST_LED16        16

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

static uint16_t leds_virtuales;

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */

void setUp(void) {
    leds_init(&leds_virtuales);
}

/**
 * @brief Test 1
 *        Al iniciar el controlador los leds deben quedar apagados sin importar el estado anterior
 *
 * @param  -
 * @return -
 */
void test_todos_los_leds_inician_apagados(void) {
    leds_virtuales = 0xFF;
    leds_init(&leds_virtuales);
    TEST_ASSERT_EQUAL_UINT16(TEST_ALL_LEDS_OFF, leds_virtuales);
}

/**
 * @brief Test 2
 *        Con todos los leds apagados prender el led 3 y verificar que el bit 2 se pone en 1 y el
 * resto de bits permanece en 0
 *
 * @param  -
 * @return -
 */
void test_prender_un_led(void) {
    leds_turn_on(TEST_LED03);
    // Bit 2 en alto
    TEST_ASSERT_BIT_HIGH((TEST_LED03 - 1), leds_virtuales);
    // Todos los otros bits estan en bajo
    TEST_ASSERT_BITS_LOW(~(1 << (TEST_LED03 - 1)), leds_virtuales);
}

/**
 * @brief Test 3
 *        Apagar un led prendido y ver que efectivamente se apaga y que el resto no cambia
 *
 * @param  -
 * @return -
 */
void test_apagar_un_led(void) {
    leds_turn_on(TEST_LED05);
    leds_turn_off(TEST_LED05);
    TEST_ASSERT_EQUAL_UINT16(TEST_ALL_LEDS_OFF, leds_virtuales);
}

/**
 * @brief Test 4
 *        Prendo 2 leds y apago 1 y verifico que solo quede 1 encendido
 *
 * @param  -
 * @return -
 */
void test_prender_apagar_leds(void) {
    leds_turn_on(TEST_LED02);
    leds_turn_on(TEST_LED05);
    leds_turn_off(TEST_LED02);
    TEST_ASSERT_EQUAL_UINT16(0x10, leds_virtuales);
}

/**
 * @brief Test 5
 *        Con todos los leds apagados prender un led y verificar que al consultar el estado del
 * mismo me informa que esta prendido. Lo mismo pero apagando.
 *
 * @param  -
 * @return -
 */
void test_leer_estado_de_leds(void) {
    leds_turn_on(TEST_LED06);
    TEST_ASSERT_TRUE(leds_get_status(TEST_LED06));
    leds_turn_off(TEST_LED06);
    TEST_ASSERT_FALSE(leds_get_status(TEST_LED06));
}

/**
 * @brief Test 6
 *        Prender todos los leds que estan apagados y verificar que estan los 16 encendidos
 *
 * @param  -
 * @return -
 */
void test_prender_todos_los_leds(void) {
    leds_turn_on_all();
    TEST_ASSERT_EQUAL_UINT16(TEST_ALL_LEDS_ON, leds_virtuales);
}

/**
 * @brief Test 7
 *        Apagar todos los leds que estan encendidos y verificar que estan los 16 apagados
 *
 * @param  -
 * @return -
 */
void test_apagar_todos_los_leds(void) {
    // Enciende todos los leds
    leds_turn_on_all();
    // Apaga todos los leds
    leds_turn_off_all();
    TEST_ASSERT_EQUAL_UINT16(TEST_ALL_LEDS_OFF, leds_virtuales);
}

/**
 * @brief Test 8
 *        Comprobar los valores limites (Led 1 y Led 16)
 *
 * @param  -
 * @return -
 */
void test_comprobar_limites(void) {
    leds_turn_on(TEST_LED16);
    TEST_ASSERT_BIT_HIGH((TEST_LED16 - 1), leds_virtuales);
    leds_turn_on(TEST_LED01);
    TEST_ASSERT_BIT_HIGH((TEST_LED01 - 1), leds_virtuales);
}

/**
 * @brief Test 9
 *        Comprobar valores prohibidos (numero de led > 16 o numero de led < 1) para la funcion:
 * leds_turn_on()
 *
 * @param  -
 * @return -
 */
void test_comprobar_prohibidos_turn_on(void) {
    // verifica 2 valore por encima de 16 y 2 valores por debajo de 1
    leds_turn_on(TEST_LED16 + 1);
    leds_turn_on(TEST_LED16 + 17);
    leds_turn_on(TEST_LED01 - 1);
    leds_turn_on(TEST_LED01 - 17);
    TEST_ASSERT_EQUAL_UINT16(TEST_ALL_LEDS_OFF, leds_virtuales);
}

/**
 * @brief Test 10
 *        Comprobar valores prohibidos (numero de led > 16 o numero de led < 1) para la funcion:
 * leds_turn_off()
 *
 * @param  -
 * @return -
 */
void test_comprobar_prohibidos_turn_off(void) {
    leds_turn_on_all();
    // verifica 2 valore por encima de 16 y 2 valores por debajo de 1
    leds_turn_off(TEST_LED16 + 1);
    leds_turn_off(TEST_LED16 + 17);
    leds_turn_off(TEST_LED01 - 1);
    leds_turn_off(TEST_LED01 - 17);
    // leds_turn_off(LED02);
    TEST_ASSERT_EQUAL_UINT16(TEST_ALL_LEDS_ON, leds_virtuales);
}

/**
 * @brief Test 11
 *        Comprobar valores prohibidos (numero de led > 16 o numero de led < 1) para la funcion:
 * leds_get_status()
 *
 * @param  -
 * @return -
 */
void test_comprobar_prohibidos_get_status() {
    leds_turn_on_all();
    // verifica 2 valore por encima de 16 y 2 valores por debajo de 1
    TEST_ASSERT_FALSE(leds_get_status(TEST_LED16 + 1));
    TEST_ASSERT_FALSE(leds_get_status(TEST_LED16 + 17));
    TEST_ASSERT_FALSE(leds_get_status(TEST_LED01 - 1));
    TEST_ASSERT_FALSE(leds_get_status(TEST_LED01 - 17));
}
/* === End of documentation ==================================================================== */
