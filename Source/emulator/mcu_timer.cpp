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
#include <stdint.h>
#include <string.h>
#include "mcu.h"
#include "mcu_timer.h"

void MCU_Timer::TIMER_Reset(void)
{
    timer_tempreg = 0;

    timer8_enabled = false;
    timer8_cmiea = false;
    timer8_cmfa = false;
    timer8_cmfa_read = false;
    timer8_tcora = 0;
    timer8_tcnt = 0;

    timer0_ocra = 0;
    timer1_ocra = 0;
    timer2_ocra = 0;
    timer0_frc = 0;
    timer1_frc = 0;
    timer2_frc = 0;
    timer0_ocfa = false;
    timer1_ocfa = false;
    timer2_ocfa = false;
    timer0_ocfa_read = false;
    timer1_ocfa_read = false;
    timer2_ocfa_read = false;
    timer0_ociea = false;
    timer1_ociea = false;
    timer2_ociea = false;
}

void MCU_Timer::TIMER_Write(uint32_t address, uint8_t data)
{
    switch (address)
    {
    case DEV_FRT1_TCR:
        timer0_ociea = data == 0b00100000;
        break;
    case DEV_FRT2_TCR:
        timer1_ociea = data == 0b00100000;
        break;
    case DEV_FRT3_TCR:
        timer2_ociea = data == 0b00100000;
        break;
    case DEV_FRT1_TCSR:
        if ((data & 0x20) == 0 && timer0_ocfa_read)
        {
            timer0_ocfa = false;
            timer0_ocfa_read = false;
            MCU_Interrupt_SetRequest(mcu, INTERRUPT_SOURCE_FRT0_OCIA, 0);
        }
        break;
    case DEV_FRT2_TCSR:
        if ((data & 0x20) == 0 && timer1_ocfa_read)
        {
            timer1_ocfa = false;
            timer1_ocfa_read = false;
            MCU_Interrupt_SetRequest(mcu, INTERRUPT_SOURCE_FRT1_OCIA, 0);
        }
        break;
    case DEV_FRT3_TCSR:
        if ((data & 0x20) == 0 && timer2_ocfa_read)
        {
            timer2_ocfa = false;
            timer2_ocfa_read = false;
            MCU_Interrupt_SetRequest(mcu, INTERRUPT_SOURCE_FRT2_OCIA, 0);
        }
        break;
    case DEV_FRT1_OCRAH:
    case DEV_FRT2_OCRAH:
    case DEV_FRT3_OCRAH:
        timer_tempreg = data;
        break;
    case DEV_FRT1_OCRAL:
        timer0_ocra = (timer_tempreg << 8) | data;
        break;
    case DEV_FRT2_OCRAL:
        timer1_ocra = (timer_tempreg << 8) | data;
        break;
    case DEV_FRT3_OCRAL:
        timer2_ocra = (timer_tempreg << 8) | data;
        break;
    }
}

uint8_t MCU_Timer::TIMER_Read(uint32_t address)
{
    uint8_t ret;
    switch (address)
    {
    case DEV_FRT1_TCSR:
        ret = 0b01110001;
        timer0_ocfa_read |= timer0_ocfa;
        return ret;
    case DEV_FRT2_TCSR:
        ret = 0b01110001;
        timer1_ocfa_read |= timer1_ocfa;
        return ret;
    case DEV_FRT3_TCSR:
        ret = 0b01110001;
        timer2_ocfa_read |= timer2_ocfa;
        return ret;
    }
    return 0xff;
}

void MCU_Timer::TIMER2_Write(uint32_t address, uint8_t data)
{
    switch (address)
    {
    case DEV_TMR_TCR:
        timer8_enabled = data & 1;
        timer8_cmiea = data >> 6;
        break;
    case DEV_TMR_TCSR:
        if ((data & 0x40) == 0 && timer8_cmfa)
        {
            timer8_cmfa = false;
            timer8_cmfa_read = false;
            MCU_Interrupt_SetRequest(mcu, INTERRUPT_SOURCE_TIMER_CMIA, 0);
        }
        break;
    case DEV_TMR_TCORA:
        timer8_tcora = data;
        break;
    case DEV_TMR_TCNT:
        timer8_tcnt = data;
        break;
    }
}
uint8_t MCU_Timer::TIMER_Read2(uint32_t address)
{
    if (address == DEV_TMR_TCSR)
    {
        uint8_t ret = timer8_cmfa ? 0b11100000 : 0b10100000;
        timer8_cmfa_read |= timer8_cmfa;
        return ret;
    }
    return 0xff;
}

void MCU_Timer::TIMER_Clock(uint64_t cycles)
{
    if (timer8_enabled && (cycles & 0x3f) == 0)
    {
        timer8_cmfa = true;
        if (timer8_cmiea)
            MCU_Interrupt_SetRequest(mcu, INTERRUPT_SOURCE_TIMER_CMIA, 1);
    }

    {
        bool matcha = (timer0_frc >> 2) >= timer0_ocra;
        if (matcha)
            timer0_frc = 0;
        else
            timer0_frc += 6;

        if (matcha)
            timer0_ocfa |= 0x20;
        if (timer0_ociea && matcha)
            MCU_Interrupt_SetRequest(mcu, INTERRUPT_SOURCE_FRT0_OCIA, 1);
    }
    {
        bool matcha = (timer1_frc >> 2) >= timer1_ocra;
        if (matcha)
            timer1_frc = 0;
        else
            timer1_frc += 6;

        if (matcha)
            timer1_ocfa |= 0x20;
        if (timer1_ociea && matcha)
            MCU_Interrupt_SetRequest(mcu, INTERRUPT_SOURCE_FRT1_OCIA, 1);
    }
    {
        bool matcha = (timer2_frc >> 2) >= timer2_ocra;
        if (matcha)
            timer2_frc = 0;
        else
            timer2_frc += 6;

        if (matcha)
            timer2_ocfa |= 0x20;
        if (timer2_ociea && matcha)
            MCU_Interrupt_SetRequest(mcu, INTERRUPT_SOURCE_FRT2_OCIA, 1);
    }
}
