/*
 * Copyright (C) 2021, 2024 nukeykt
 *
 *  Redistribution and use of this code or any derivative works are permitted
 *  provided that the following conditions are met:
 *
 *   - Redistributions may not be sold, nor may they be used in a commercial
 *     product or activity.
 *
 *   - Redistributions that are modified from the original source must include the
 *     complete source code, including the source code for all components used by a
 *     binary built from the modified sources. However, as a special exception, the
 *     source code distributed need not include anything that is normally distributed
 *     (in either source or binary form) with the major components (compiler, kernel,
 *     and so on) of the operating system on which the executable runs, unless that
 *     component itself accompanies the executable.
 *
 *   - Redistributions must reproduce the above copyright notice, this list of
 *     conditions and the following disclaimer in the documentation and/or other
 *     materials provided with the distribution.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */
#pragma once
#include <stdint.h>

struct MCU;

struct MCU_Timer {
    MCU *mcu;
    MCU_Timer(MCU *mcu): mcu(mcu) {}

    uint8_t timer_tempreg;

    bool timer8_enabled;
    bool timer8_cmiea;
    bool timer8_cmfa;
    bool timer8_cmfa_read;
    uint8_t timer8_tcora;
    uint8_t timer8_tcnt;

    uint16_t timer0_ocra;
    uint16_t timer1_ocra;
    uint16_t timer2_ocra;
    uint16_t timer0_frc;
    uint16_t timer1_frc;
    uint16_t timer2_frc;
    bool timer0_ocfa;
    bool timer1_ocfa;
    bool timer2_ocfa;
    bool timer0_ocfa_read;
    bool timer1_ocfa_read;
    bool timer2_ocfa_read;
    bool timer0_ociea;
    bool timer1_ociea;
    bool timer2_ociea;

    void TIMER_Reset(void);
    void TIMER_Write(uint32_t address, uint8_t data);
    uint8_t TIMER_Read(uint32_t address);
    void TIMER_Clock(uint64_t cycles);

    void TIMER2_Write(uint32_t address, uint8_t data);
    uint8_t TIMER_Read2(uint32_t address);
};
