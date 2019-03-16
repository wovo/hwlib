/**
 * \file
 * \brief     Due / sam3x8e native SPI.
 * \author    Chris Smeele
 * \date      2016-10-09
 * \copyright Copyright (c) 2016, Chris Smeele
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at 
 * http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#include "hwlib.hpp"

namespace due {

    // Calculate PCS field value from a NPCS value (formula taken from libsam).
    constexpr uint32_t SPI_PCS(uint32_t npcs) {
        return (~(1 << npcs) & 0xf) << 16;
    }

    /**
     * \brief Due / sam3x8e native SPI bus.
     *
     * Note: This SPI class is limited to one device on the SPI bus.
     * CS for the connected peripheral must be on due pin d10.
     */
    class spi_bus_due : public hwlib::spi_bus {

        uint8_t write_byte(hwlib::pin_out &sel, uint16_t data) {
            // Wait for tx register empty.
            while ((SPI0->SPI_SR & SPI_SR_TXEMPTY) == 0);

            // Send data.
            SPI0->SPI_TDR = data | SPI_PCS(0);

            // Wait for transmit data register empty.
            while ((SPI0->SPI_SR & SPI_SR_TDRE) == 0);

            // Wait for rx register full.
            while ((SPI0->SPI_SR & SPI_SR_RDRF) == 0 );

            // Return read value.
            return SPI0->SPI_RDR & 0xffff;
        }

    public:
        /**
         * \brief Write and read data.
         *
         * Note: This request does not yield, contrary to the
         * bitbanged SPI in hwlib.
         * 
         * \warning `sel` is not used, CS must be on d10!
         */
        void write_and_read( hwlib::pin_out &sel,
                            size_t n,
                            const uint8_t data_out[],
                            uint8_t data_in[]) override {

            for (size_t i = 0; i < n; i++)
                data_in[i] = write_byte(sel, data_out[i]);
        }

        spi_bus_due() {
            // Disable SPI.
            SPI0->SPI_CR = SPI_CR_SPIDIS;

            // Configure SPI pins.
            auto config_pin = [](uint32_t pin) {
                // PIO AB select.
                PIOA->PIO_ABSR &= (~pin & PIOA->PIO_ABSR);

                // PIO disable.
                PIOA->PIO_PDR = pin;

                // Disable interrupts.
                PIOA->PIO_IDR = pin;

                // Enable pull-up.
                PIOA->PIO_PUER = pin;
            };

            // Note: CS0 is pin d10 on the due.
            config_pin(PIO_PA28A_SPI0_NPCS0);
            config_pin(PIO_PA25A_SPI0_MISO);
            config_pin(PIO_PA26A_SPI0_MOSI);
            config_pin(PIO_PA27A_SPI0_SPCK);

            // Enable SPI peripheral clock.
            if ((PMC->PMC_PCSR0 & (1 << ID_SPI0)) != (1 << ID_SPI0))
                PMC->PMC_PCER0 = 1 << ID_SPI0;

            // Perform a SPI software reset twice, like SAM does.
            SPI0->SPI_CR = SPI_CR_SWRST;
            SPI0->SPI_CR = SPI_CR_SWRST;

            // Set configuration.
            SPI0->SPI_MR = (0x21           // WDRBT enabled, PS Fixed, Master.
                            | SPI_PCS(0)); // Select first peripheral (NPCS0 - CS on Due pin d10).

            // Configure peripheral 0 (CS0).
            // XXX: These clock values are just a guess but they seem
            // to work for the SD and OLED, see
            // https://github.com/cjsmeele/Picus/blob/master/src/sdspi.cc
            SPI0->SPI_CSR[0] = (  (uint32_t)32 << 24
                                | (uint32_t)32 << 16
                                | (uint32_t)16 << 8 // baud rate divisor thingy.
                                | 0x2);             // CPOL = 0, NCHPA = 1

            // Enable SPI.
            SPI0->SPI_CR = SPI_CR_SPIEN;

            // Enjoy super fast SPI performance.
        }
    };
}
