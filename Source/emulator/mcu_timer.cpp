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

uint64_t MCU_Timer::TIMER_NextEventCycles(uint64_t now) const
{
    const uint64_t STEP = 12;
    uint64_t best = UINT64_MAX;

    // timer8 sets timer8_cmfa (and optionally requests CMIA) whenever
    // (cycles & 0x3f) == 0. In this loop cycles is always a multiple of 12, so
    // that condition holds exactly on the multiples of lcm(12, 64) = 192.
    if (timer8_enabled)
    {
        uint64_t next192 = (now / 192 + 1) * 192;
        if (next192 < best)
            best = next192;
    }

    // Each FRT advances frc by +6 per CALL — the cadence is call-count driven,
    // not cycle-value driven — and matches when (frc >> 2) >= ocra at the start
    // of a call, i.e. when frc >= ocra * 4. So the match falls on call j, the
    // smallest j >= 1 with frc + 6 * (j - 1) >= ocra * 4, which is the step at
    // cycle now + 12 * j.
    //
    // A match is only observable from outside the timer when it raises an
    // interrupt (ociea set) or when it flips ocfa from clear to set. When ociea
    // is clear and ocfa is already set the match changes nothing anyone can see:
    // it merely resets frc, which TIMER_AdvanceSkipped reproduces exactly. That
    // is the common case here — this firmware leaves timer2 with ocra == 0 and
    // ociea clear, so it "matches" on every single call while being invisible.
    //
    // frc is 16-bit, so an ocra whose target exceeds 0xffff can never be reached.
    // Where the +6 stride overshoots past 0xffff the real counter wraps and does
    // NOT match, which only ever makes the true event later than predicted —
    // predicting early is safe here, it just ends the skip sooner.
    auto frt_next = [&](uint16_t frc, uint16_t ocra, bool ociea,
                        bool ocfa) -> uint64_t {
        if (!ociea && ocfa)
            return UINT64_MAX;
        uint64_t target = (uint64_t)ocra << 2;
        if (target > 0xffff)
            return UINT64_MAX;
        if ((uint64_t)frc >= target)
            return now + STEP; // matches on the very next call
        uint64_t jm1 = (target - frc + 5) / 6; // ceil((target - frc) / 6) >= 1
        return now + STEP * (jm1 + 1);
    };

    uint64_t t;
    t = frt_next(timer0_frc, timer0_ocra, timer0_ociea, timer0_ocfa);
    if (t < best) best = t;
    t = frt_next(timer1_frc, timer1_ocra, timer1_ociea, timer1_ocfa);
    if (t < best) best = t;
    t = frt_next(timer2_frc, timer2_ocra, timer2_ociea, timer2_ocfa);
    if (t < best) best = t;

    return best;
}

void MCU_Timer::TIMER_AdvanceSkipped(uint64_t n)
{
    // Mirrors TIMER_Clock's per-FRT arithmetic verbatim, minus the interrupt
    // requests and minus timer8. Both omissions are licensed by the caller
    // having stopped at or before TIMER_NextEventCycles(): any match replayed
    // here has ociea clear and ocfa already set, so its request would not exist
    // and its `ocfa |= 0x20` is a no-op; and no skipped step can be a multiple
    // of 192, so timer8 cannot have fired. frc still has to be reproduced
    // exactly, because a match resets it to 0.
    for (uint64_t s = 0; s < n; s++)
    {
        if ((timer0_frc >> 2) >= timer0_ocra)
        {
            timer0_frc = 0;
            timer0_ocfa |= 0x20;
        }
        else
            timer0_frc += 6;

        if ((timer1_frc >> 2) >= timer1_ocra)
        {
            timer1_frc = 0;
            timer1_ocfa |= 0x20;
        }
        else
            timer1_frc += 6;

        if ((timer2_frc >> 2) >= timer2_ocra)
        {
            timer2_frc = 0;
            timer2_ocfa |= 0x20;
        }
        else
            timer2_frc += 6;
    }
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
