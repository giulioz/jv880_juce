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

enum {
    SM_STATUS_C = 1,
    SM_STATUS_Z = 2,
    SM_STATUS_I = 4,
    SM_STATUS_D = 8,
    SM_STATUS_B = 16,
    SM_STATUS_T = 32,
    SM_STATUS_V = 64,
    SM_STATUS_N = 128
};

struct submcu_t {
    uint16_t pc;
    uint8_t a;
    uint8_t x;
    uint8_t y;
    uint8_t s;
    uint8_t sr;
    uint64_t cycles;
    uint8_t sleep;
};

struct MCU;

struct SubMcu {
    MCU *mcu;
    SubMcu(MCU *mcu) : mcu(mcu) {}

    uint8_t sm_rom[4096];
    uint8_t sm_ram[128];
    uint8_t sm_shared_ram[192];
    uint8_t sm_access[0x18];

    uint8_t sm_p0_dir;
    uint8_t sm_p1_dir;

    uint8_t sm_device_mode[32];
    uint8_t sm_cts;

    uint64_t sm_timer_cycles;
    uint8_t sm_timer_prescaler;
    uint8_t sm_timer_counter;

    submcu_t sm;

    uint8_t uart_rx_gotbyte;
    uint8_t uart_rx_byte;
    uint64_t uart_rx_delay;

    void SM_ErrorTrap(void);
    uint8_t SM_Read(uint16_t address);
    void SM_Write(uint16_t address, uint8_t data);
    void SM_SysWrite(uint32_t address, uint8_t data);
    uint8_t SM_SysRead(uint32_t address);
    uint16_t SM_GetVectorAddress(uint32_t vector);
    void SM_SetStatus(uint32_t condition, uint32_t mask);
    void SM_Reset(void);
    uint8_t SM_ReadAdvance(void);
    uint16_t SM_ReadAdvance16(void);
    uint16_t SM_Read16(uint16_t address);
    void SM_Update_NZ(uint8_t val);
    void SM_PushStack(uint8_t data);
    uint8_t SM_PopStack(void);

    void SM_StartVector(uint32_t vector);
    void SM_HandleInterrupt(void);
    void SM_UpdateTimer(void);
    void SM_PostUART(uint8_t data);
    void SM_UpdateUART(void);
    void SM_Update(uint64_t cycles);
};
