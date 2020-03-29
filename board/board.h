/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*
 * This file has been automatically generated using ChibiStudio board
 * generator plugin. Do not edit manually.
 */

#ifndef BOARD_H
#define BOARD_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*
 * Setup for CLoud mini Power Meter v1.0 board.
 */

/*
 * Board identifier.
 */
#define BOARD_MINI_POWER_METER
#define BOARD_NAME                  "mini Power Meter"

/*
 * Board oscillators-related settings.
 * NOTE: LSE not fitted.
 * NOTE: HSE not fitted.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                0U
#endif

#define STM32_LSEDRV                (3U << 3U)

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                0U
#endif

#define STM32_HSE_BYPASS

/*
 * MCU type as defined in the ST header.
 */
#define STM32F072xB

/*
 * IO pins assignments.
 */
#define GPIOA_LED1                  0U
#define GPIOA_LED2                  1U
#define GPIOA_UART1_TX              2U
#define GPIOA_UART1_RX              3U
#define GPIOA_BQ_PG                 4U
#define GPIOA_BQ_STAT               5U
#define GPIOA_BQ_CE                 6U
#define GPIOA_BQ_PSEL               7U
#define GPIOA_BQ_QON                8U
#define GPIOA_BQ_INT                9U
#define GPIOA_YB24_IRQ              10U
#define GPIOA_USB_DM                11U
#define GPIOA_USB_DP                12U
#define GPIOA_SWDIO                 13U
#define GPIOA_SWCLK                 14U
#define GPIOA_BUTTON4               15U

#define GPIOB_BUTTON1               0U
#define GPIOB_BUTTON2               1U
#define GPIOB_BUTTON3               2U
#define GPIOB_YB24_SCK              3U
#define GPIOB_YB24_SDO              4U
#define GPIOB_YB24_SDI              5U
#define GPIOB_I2C1_SCL              6U
#define GPIOB_I2C1_SDA              7U
#define GPIOB_YB24_CE               8U
#define GPIOB_YB24_CS               9U
#define GPIOB_OLED_DC               10U
#define GPIOB_OLED_RES              11U
#define GPIOB_OLED_CS               12U
#define GPIOB_OLED_SCK              13U
#define GPIOB_PIN14                 14U
#define GPIOB_OLED_SDA              15U

#define GPIOC_PIN13                 13U
#define GPIOC_OSC32_IN              14U
#define GPIOC_OSC32_OUT             15U

#define GPIOF_OSC_IN                0U
#define GPIOF_OSC_OUT               1U

/*
 * IO lines assignments.
 */
#define LINE_BUTTON1                PAL_LINE(GPIOB, GPIOB_BUTTON1)
#define LINE_BUTTON2                PAL_LINE(GPIOB, GPIOB_BUTTON2)
#define LINE_BUTTON3                PAL_LINE(GPIOB, GPIOB_BUTTON3)
#define LINE_BUTTON4                PAL_LINE(GPIOA, GPIOA_BUTTON4)
#define LINE_USB_DM                 PAL_LINE(GPIOA, GPIOA_USB_DM)
#define LINE_USB_DP                 PAL_LINE(GPIOA, GPIOA_USB_DP)
#define LINE_SWDIO                  PAL_LINE(GPIOA, GPIOA_SWDIO)
#define LINE_SWCLK                  PAL_LINE(GPIOA, GPIOA_SWCLK)
#define LINE_YB24_IRQ               PAL_LINE(GPIOA, GPIOA_YB24_IRQ)
#define LINE_YB24_SCK               PAL_LINE(GPIOB, GPIOB_YB24_SCK)
#define LINE_YB24_SDO               PAL_LINE(GPIOB, GPIOB_YB24_SDO)
#define LINE_YB24_SDI               PAL_LINE(GPIOB, GPIOB_YB24_SDI)
#define LINE_YB24_CE                PAL_LINE(GPIOB, GPIOB_YB24_CE)
#define LINE_YB24_CS                PAL_LINE(GPIOB, GPIOB_YB24_CS)
#define LINE_BQ_PG                  PAL_LINE(GPIOA, GPIOA_BQ_PG)
#define LINE_BQ_STAT                PAL_LINE(GPIOA, GPIOA_BQ_STAT)
#define LINE_BQ_CE                  PAL_LINE(GPIOA, GPIOA_BQ_CE)
#define LINE_BQ_PSEL                PAL_LINE(GPIOA, GPIOA_BQ_PSEL)
#define LINE_BQ_QON                 PAL_LINE(GPIOA, GPIOA_BQ_QON)
#define LINE_BQ_INT                 PAL_LINE(GPIOA, GPIOA_BQ_INT)
#define LINE_LED1                   PAL_LINE(GPIOA, GPIOA_LED1)
#define LINE_LED2                   PAL_LINE(GPIOA, GPIOA_LED2)
#define LINE_UART1_TX               PAL_LINE(GPIOA, GPIOA_UART1_TX)
#define LINE_UART1_RX               PAL_LINE(GPIOA, GPIOA_UART1_RX)
#define LINE_I2C1_SCL               PAL_LINE(GPIOB, GPIOB_I2C1_SCL)
#define LINE_I2C1_SDA               PAL_LINE(GPIOB, GPIOB_I2C1_SDA)
#define LINE_OLED_DC                PAL_LINE(GPIOB, GPIOB_OLED_DC)
#define LINE_OLED_RES               PAL_LINE(GPIOB, GPIOB_OLED_RES)
#define LINE_OLED_CS                PAL_LINE(GPIOB, GPIOB_OLED_CS)
#define LINE_OLED_SCK               PAL_LINE(GPIOB, GPIOB_OLED_SCK)
#define LINE_OLED_SDA               PAL_LINE(GPIOB, GPIOB_OLED_SDA)



/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_VERYLOW(n)       (0U << ((n) * 2U))
#define PIN_OSPEED_LOW(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_MEDIUM(n)        (2U << ((n) * 2U))
#define PIN_OSPEED_HIGH(n)          (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))

/*
 * GPIOA setup:
 *
 * PA0  - LED1                      (output pushpull maximum).
 * PA1  - LED2                      (output pushpull maximum).
 * PA2  - UART_TX                   (alternate 0).
 * PA3  - UART_RX                   (alternate 0).
 * PA4  - BQ_PG                     (input pullup).
 * PA5  - BQ_STAT                   (input pullup).
 * PA6  - BQ_CE                     (output pushpull maximum).
 * PA7  - BQ_PSEL                   (output pushpull maximum).
 * PA8  - BQ_QON                    (input pullup).//TODO
 * PA9  - BQ_INT                    (input pullup).
 * PA10 - YB24_IRQ                  (input pullup).
 * PA11 - USB_DM                    (input floating).
 * PA12 - USB_DP                    (input floating).
 * PA13 - SWDIO                     (alternate 0).
 * PA14 - SWCLK                     (alternate 0).
 * PA15 - BUTTON4                   (input pullup).
 */
#define VAL_GPIOA_MODER             (PIN_MODE_OUTPUT(GPIOA_LED1) |         \
                                     PIN_MODE_OUTPUT(GPIOA_LED2) |           \
                                     PIN_MODE_ALTERNATE(GPIOA_UART1_TX) |           \
                                     PIN_MODE_ALTERNATE(GPIOA_UART1_RX) |           \
                                     PIN_MODE_INPUT(GPIOA_BQ_PG) |           \
                                     PIN_MODE_INPUT(GPIOA_BQ_STAT) |           \
                                     PIN_MODE_OUTPUT(GPIOA_BQ_CE) |           \
                                     PIN_MODE_OUTPUT(GPIOA_BQ_PSEL) |           \
                                     PIN_MODE_INPUT(GPIOA_BQ_QON) |           \
                                     PIN_MODE_INPUT(GPIOA_BQ_INT) |           \
                                     PIN_MODE_INPUT(GPIOA_YB24_IRQ) |          \
                                     PIN_MODE_INPUT(GPIOA_USB_DM) |         \
                                     PIN_MODE_INPUT(GPIOA_USB_DP) |         \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK) |      \
                                     PIN_MODE_INPUT(GPIOA_BUTTON4))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_LED1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_LED2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_UART1_TX) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_UART1_RX) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_BQ_PG) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_BQ_STAT) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_BQ_CE) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_BQ_PSEL) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_BQ_QON) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_BQ_INT) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_YB24_IRQ) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_USB_DM) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_USB_DP) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWDIO) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWCLK) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_BUTTON4))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_MEDIUM(GPIOA_LED1) |     \
                                     PIN_OSPEED_MEDIUM(GPIOA_LED2) |       \
                                     PIN_OSPEED_MEDIUM(GPIOA_UART1_TX) |       \
                                     PIN_OSPEED_MEDIUM(GPIOA_UART1_RX) |       \
                                     PIN_OSPEED_MEDIUM(GPIOA_BQ_PG) |       \
                                     PIN_OSPEED_MEDIUM(GPIOA_BQ_STAT) |       \
                                     PIN_OSPEED_MEDIUM(GPIOA_BQ_CE) |       \
                                     PIN_OSPEED_MEDIUM(GPIOA_BQ_PSEL) |       \
                                     PIN_OSPEED_MEDIUM(GPIOA_BQ_QON) |       \
                                     PIN_OSPEED_MEDIUM(GPIOA_BQ_INT) |       \
                                     PIN_OSPEED_MEDIUM(GPIOA_YB24_IRQ) |      \
                                     PIN_OSPEED_HIGH(GPIOA_USB_DM) |     \
                                     PIN_OSPEED_HIGH(GPIOA_USB_DP) |     \
                                     PIN_OSPEED_HIGH(GPIOA_SWDIO) |         \
                                     PIN_OSPEED_HIGH(GPIOA_SWCLK) |         \
                                     PIN_OSPEED_MEDIUM(GPIOA_BUTTON4))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_PULLUP(GPIOA_LED1) |     \
                                     PIN_PUPDR_PULLUP(GPIOA_LED2) |         \
                                     PIN_PUPDR_PULLUP(GPIOA_UART1_TX) |         \
                                     PIN_PUPDR_PULLUP(GPIOA_UART1_RX) |         \
                                     PIN_PUPDR_PULLUP(GPIOA_BQ_PG) |         \
                                     PIN_PUPDR_PULLUP(GPIOA_BQ_STAT) |         \
                                     PIN_PUPDR_PULLUP(GPIOA_BQ_CE) |         \
                                     PIN_PUPDR_PULLUP(GPIOA_BQ_PSEL) |         \
                                     PIN_PUPDR_PULLUP(GPIOA_BQ_QON) |         \
                                     PIN_PUPDR_PULLUP(GPIOA_BQ_INT) |         \
                                     PIN_PUPDR_PULLUP(GPIOA_YB24_IRQ) |        \
                                     PIN_PUPDR_FLOATING(GPIOA_USB_DM) |     \
                                     PIN_PUPDR_FLOATING(GPIOA_USB_DP) |     \
                                     PIN_PUPDR_PULLUP(GPIOA_SWDIO) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOA_SWCLK) |      \
                                     PIN_PUPDR_PULLUP(GPIOA_BUTTON4))
#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(GPIOA_LED1) |           \
                                     PIN_ODR_HIGH(GPIOA_LED2) |             \
                                     PIN_ODR_HIGH(GPIOA_UART1_TX) |             \
                                     PIN_ODR_HIGH(GPIOA_UART1_RX) |             \
                                     PIN_ODR_HIGH(GPIOA_BQ_PG) |             \
                                     PIN_ODR_HIGH(GPIOA_BQ_STAT) |             \
                                     PIN_ODR_HIGH(GPIOA_BQ_CE) |             \
                                     PIN_ODR_HIGH(GPIOA_BQ_PSEL) |             \
                                     PIN_ODR_HIGH(GPIOA_BQ_QON) |             \
                                     PIN_ODR_HIGH(GPIOA_BQ_INT) |             \
                                     PIN_ODR_HIGH(GPIOA_YB24_IRQ) |            \
                                     PIN_ODR_HIGH(GPIOA_USB_DM) |           \
                                     PIN_ODR_HIGH(GPIOA_USB_DP) |           \
                                     PIN_ODR_HIGH(GPIOA_SWDIO) |            \
                                     PIN_ODR_HIGH(GPIOA_SWCLK) |            \
                                     PIN_ODR_HIGH(GPIOA_BUTTON4))
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_LED1, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_LED2, 0U) |          \
                                     PIN_AFIO_AF(GPIOA_UART1_TX, 0U) |          \
                                     PIN_AFIO_AF(GPIOA_UART1_RX, 0U) |          \
                                     PIN_AFIO_AF(GPIOA_BQ_PG, 0U) |          \
                                     PIN_AFIO_AF(GPIOA_BQ_STAT, 0U) |          \
                                     PIN_AFIO_AF(GPIOA_BQ_CE, 0U) |          \
                                     PIN_AFIO_AF(GPIOA_BQ_PSEL, 0U))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_BQ_QON, 0U) |          \
                                     PIN_AFIO_AF(GPIOA_BQ_INT, 0U) |          \
                                     PIN_AFIO_AF(GPIOA_YB24_IRQ, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_USB_DM, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_USB_DP, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_SWDIO, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_BUTTON4, 0U))

/*
 * GPIOB setup:
 *
 * PB0  - BUTTON1                   (input pullup).
 * PB1  - BUTTON2                   (input pullup).
 * PB2  - BUTTON3                   (input pullup).
 * PB3  - YB24_SCK                  (input pullup).
 * PB4  - YB24_SDO                  (input pullup).
 * PB5  - YB24_SDI                  (input pullup).
 * PB6  - I2C1_SCL                  (input pullup).
 * PB7  - I2C1_SDA                  (input pullup).
 * PB8  - YB24_CE                   (input pullup).
 * PB9  - YB24_CS                   (input pullup).
 * PB10 - OLED_DC                   (input pullup).
 * PB11 - OLED_RES                  (input pullup).
 * PB12 - OLED_CS                   (input pullup).
 * PB13 - OLED_SCK                  (alternate 0).
 * PB14 - PIN14                     (alternate 0).
 * PB15 - OLED_SDA                  (input pullup).
 */
#define VAL_GPIOB_MODER             (PIN_MODE_INPUT(GPIOB_BUTTON1) |           \
                                     PIN_MODE_INPUT(GPIOB_BUTTON2) |           \
                                     PIN_MODE_INPUT(GPIOB_BUTTON3) |           \
                                     PIN_MODE_INPUT(GPIOB_YB24_SCK) |           \
                                     PIN_MODE_INPUT(GPIOB_YB24_SDO) |           \
                                     PIN_MODE_INPUT(GPIOB_YB24_SDI) |           \
                                     PIN_MODE_INPUT(GPIOB_I2C1_SCL) |           \
                                     PIN_MODE_INPUT(GPIOB_I2C1_SDA) |           \
                                     PIN_MODE_INPUT(GPIOB_YB24_CE) |           \
                                     PIN_MODE_INPUT(GPIOB_YB24_CS) |           \
                                     PIN_MODE_INPUT(GPIOB_OLED_DC) |          \
                                     PIN_MODE_INPUT(GPIOB_OLED_RES) |          \
                                     PIN_MODE_INPUT(GPIOB_OLED_CS) |          \
                                     PIN_MODE_INPUT(GPIOB_OLED_SCK) |   \
                                     PIN_MODE_INPUT(GPIOB_PIN14) |  \
                                     PIN_MODE_INPUT(GPIOB_OLED_SDA))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_BUTTON1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_BUTTON2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_BUTTON3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_YB24_SCK) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_YB24_SDO) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_YB24_SDI) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_I2C1_SCL) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_I2C1_SDA) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_YB24_CE) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_YB24_CS) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_OLED_DC) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_OLED_RES) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_OLED_CS) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_OLED_SCK) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN14) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_OLED_SDA))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_HIGH(GPIOB_BUTTON1) |       \
                                     PIN_OSPEED_HIGH(GPIOB_BUTTON2) |       \
                                     PIN_OSPEED_HIGH(GPIOB_BUTTON3) |          \
                                     PIN_OSPEED_HIGH(GPIOB_YB24_SCK) |          \
                                     PIN_OSPEED_HIGH(GPIOB_YB24_SDO) |          \
                                     PIN_OSPEED_HIGH(GPIOB_YB24_SDI) |       \
                                     PIN_OSPEED_HIGH(GPIOB_I2C1_SCL) |       \
                                     PIN_OSPEED_HIGH(GPIOB_I2C1_SDA) |       \
                                     PIN_OSPEED_HIGH(GPIOB_YB24_CE) |       \
                                     PIN_OSPEED_HIGH(GPIOB_YB24_CS) |       \
                                     PIN_OSPEED_HIGH(GPIOB_OLED_DC) |      \
                                     PIN_OSPEED_HIGH(GPIOB_OLED_RES) |      \
                                     PIN_OSPEED_HIGH(GPIOB_OLED_CS) |      \
                                     PIN_OSPEED_HIGH(GPIOB_OLED_SCK) |   \
                                     PIN_OSPEED_HIGH(GPIOB_PIN14) |  \
                                     PIN_OSPEED_HIGH(GPIOB_OLED_SDA))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_FLOATING(GPIOB_BUTTON1) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_BUTTON2) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_BUTTON3) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_YB24_SCK) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_YB24_SDO) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_YB24_SDI) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_I2C1_SCL) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_I2C1_SDA) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_YB24_CE) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_YB24_CS) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_OLED_DC) |        \
                                     PIN_PUPDR_FLOATING(GPIOB_OLED_RES) |        \
                                     PIN_PUPDR_FLOATING(GPIOB_OLED_CS) |        \
                                     PIN_PUPDR_FLOATING(GPIOB_OLED_SCK) |   \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN14) |  \
                                     PIN_PUPDR_FLOATING(GPIOB_OLED_SDA))
#define VAL_GPIOB_ODR               (PIN_ODR_HIGH(GPIOB_BUTTON1) |             \
                                     PIN_ODR_HIGH(GPIOB_BUTTON2) |             \
                                     PIN_ODR_HIGH(GPIOB_BUTTON3) |             \
                                     PIN_ODR_HIGH(GPIOB_YB24_SCK) |             \
                                     PIN_ODR_HIGH(GPIOB_YB24_SDO) |             \
                                     PIN_ODR_HIGH(GPIOB_YB24_SDI) |             \
                                     PIN_ODR_HIGH(GPIOB_I2C1_SCL) |             \
                                     PIN_ODR_HIGH(GPIOB_I2C1_SDA) |             \
                                     PIN_ODR_HIGH(GPIOB_YB24_CE) |             \
                                     PIN_ODR_HIGH(GPIOB_YB24_CS) |             \
                                     PIN_ODR_HIGH(GPIOB_OLED_DC) |            \
                                     PIN_ODR_HIGH(GPIOB_OLED_RES) |            \
                                     PIN_ODR_HIGH(GPIOB_OLED_CS) |            \
                                     PIN_ODR_HIGH(GPIOB_OLED_SCK) |         \
                                     PIN_ODR_HIGH(GPIOB_PIN14) |        \
                                     PIN_ODR_HIGH(GPIOB_OLED_SDA))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_BUTTON1, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_BUTTON2, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_BUTTON3, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_YB24_SCK, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_YB24_SDO, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_YB24_SDI, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_I2C1_SCL, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_I2C1_SDA, 0U))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_YB24_CE, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_YB24_CS, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_OLED_DC, 0U) |         \
                                     PIN_AFIO_AF(GPIOB_OLED_RES, 0U) |         \
                                     PIN_AFIO_AF(GPIOB_OLED_CS, 0U) |         \
                                     PIN_AFIO_AF(GPIOB_OLED_SCK, 0U) |      \
                                     PIN_AFIO_AF(GPIOB_PIN14, 0U) |     \
                                     PIN_AFIO_AF(GPIOB_OLED_SDA, 0U))

/*
 * GPIOC setup:
 *
 * PC13 - PIN13                     (input pullup).
 * PC14 - OSC32_IN                  (input floating).
 * PC15 - OSC32_OUT                 (input floating).
 */
#define VAL_GPIOC_MODER             (PIN_MODE_OUTPUT(GPIOC_PIN13) |       \
                                     PIN_MODE_INPUT(GPIOC_OSC32_IN) |       \
                                     PIN_MODE_INPUT(GPIOC_OSC32_OUT))
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_PIN13) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_IN) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_OUT))
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_HIGH(GPIOC_PIN13) |       \
                                     PIN_OSPEED_HIGH(GPIOC_OSC32_IN) |      \
                                     PIN_OSPEED_HIGH(GPIOC_OSC32_OUT))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_FLOATING(GPIOC_PIN13) |    \
                                     PIN_PUPDR_FLOATING(GPIOC_OSC32_IN) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_OSC32_OUT))
#define VAL_GPIOC_ODR               (PIN_ODR_HIGH(GPIOC_PIN13) |          \
                                     PIN_ODR_HIGH(GPIOC_OSC32_IN) |         \
                                     PIN_ODR_HIGH(GPIOC_OSC32_OUT))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_PIN13, 0U) |       \
                                     PIN_AFIO_AF(GPIOC_OSC32_IN, 0U) |      \
                                     PIN_AFIO_AF(GPIOC_OSC32_OUT, 0U))

/*
 * GPIOF setup:
 *
 * PF0  - OSC_IN                    (input floating).
 * PF1  - OSC_OUT                   (input floating).
 */
#define VAL_GPIOF_MODER             (PIN_MODE_INPUT(GPIOF_OSC_IN) |         \
                                     PIN_MODE_INPUT(GPIOF_OSC_OUT))
#define VAL_GPIOF_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOF_OSC_IN) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_OSC_OUT))
#define VAL_GPIOF_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOF_OSC_IN) |     \
                                     PIN_OSPEED_VERYLOW(GPIOF_OSC_OUT))
#define VAL_GPIOF_PUPDR             (PIN_PUPDR_FLOATING(GPIOF_OSC_IN) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_OSC_OUT))
#define VAL_GPIOF_ODR               (PIN_ODR_HIGH(GPIOF_OSC_IN) |           \
                                     PIN_ODR_HIGH(GPIOF_OSC_OUT))
#define VAL_GPIOF_AFRL              (PIN_AFIO_AF(GPIOF_OSC_IN, 0U) |        \
                                     PIN_AFIO_AF(GPIOF_OSC_OUT, 0U))

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* BOARD_H */
