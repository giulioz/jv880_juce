/*
  ==============================================================================

    dataStructures.h
    Created: 20 Aug 2024 4:35:29pm
    Author:  Giulio Zausa

  ==============================================================================
*/

#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct Tone {
  uint8_t flags;
  // 0-1: wave group
  // 7: tone switch
  uint8_t waveNumber;
  uint8_t fxmConfig; // 7:enable low:depth
  uint8_t velocityRangeLow;
  uint8_t velocityRangeUp;
  uint8_t unk_0x05;
  uint8_t unk_0x06;
  uint8_t unk_0x07;
  uint8_t unk_0x08;
  uint8_t unk_0x09;
  uint8_t unk_0x0A;
  uint8_t unk_0x0B;
  uint8_t unk_0x0C;
  uint8_t unk_0x0D;
  uint8_t unk_0x0E;
  uint8_t unk_0x0F;
  uint8_t unk_0x10;
  uint8_t unk_0x11;
  uint8_t unk_0x12;
  uint8_t unk_0x13;
  uint8_t unk_0x14;
  uint8_t unk_0x15;
  uint8_t unk_0x16;
  uint8_t lfo1Flags;
  // 0-1-2: waveform
  // 3-4-5: offset
  // 6: synchro
  // 7: fade in/out
  uint8_t lfo1Rate;
  uint8_t lfo1Delay;
  uint8_t lfo1Fade;
  uint8_t lfo2Flags;
  uint8_t lfo2Rate;
  uint8_t lfo2Delay;
  uint8_t lfo2Fade;
  uint8_t lfo1PitchDepth;
  uint8_t lfo1TvfDepth;
  uint8_t lfo1TvaDepth;
  uint8_t lfo2PitchDepth;
  uint8_t lfo2TvfDepth;
  uint8_t lfo2TvaDepth;
  int8_t pitchCoarse;
  int8_t pitchFine;
  uint8_t tvaPanningKFRandomPitch; // high:tva panning low:random pitch
  uint8_t tvpTimeKFKeyfollow;
  uint8_t tvpVelocity;
  uint8_t tvpT1T4Velocity;
  uint8_t tvpEnvDepth;
  uint8_t tvpEnvTime1;
  uint8_t tvpEnvLevel1;
  uint8_t tvpEnvTime2;
  uint8_t tvpEnvLevel2;
  uint8_t tvpEnvTime3;
  uint8_t tvpEnvLevel3;
  uint8_t tvpEnvTime4;
  uint8_t tvpEnvLevel4;
  uint8_t tvfCutoff;
  uint8_t tvfResonance;       // 7: soft/hard
  uint8_t tvfTimeKFKeyfollow; // check
  uint8_t tvfVeloCurveLpfHpf; // (check) 3-4: LPF/HPF
  uint8_t tvfVelocity;        // check
  uint8_t tvfT1T4Velocity;
  uint8_t tvfEnvDepth;
  uint8_t tvfEnvTime1;
  uint8_t tvfEnvLevel1;
  uint8_t tvfEnvTime2;
  uint8_t tvfEnvLevel2;
  uint8_t tvfEnvTime3;
  uint8_t tvfEnvLevel3;
  uint8_t tvfEnvTime4;
  uint8_t tvfEnvLevel4;
  uint8_t tvaLevel;
  uint8_t tvaPan;
  uint8_t unk_0x45;
  uint8_t tvaTimeKFDelayTimeKeyfollow; // (check again) low:key follow
  uint8_t tvaDelayModeVeloCurve;       // low:velo curve
  uint8_t tvaVelocity;
  uint8_t tvaT1T4Velocity; // check again
  uint8_t tvaEnvTime1;
  uint8_t tvaEnvLevel1;
  uint8_t tvaEnvTime2;
  uint8_t tvaEnvLevel2;
  uint8_t tvaEnvTime3;
  uint8_t tvaEnvLevel3;
  uint8_t tvaEnvTime4;
  uint8_t drySend;
  uint8_t reverbSend;
  uint8_t chorusSend;
} __attribute__((__packed__)); // 84 bytes
#pragma pack(pop)

#pragma pack(push, 1)
struct Patch {
  char name[12];
  uint8_t recChorConfig;
  // 0-3: rev type
  // 4-5: chorus type
  // 6:   ??
  // 7:   velocity switch
  uint8_t reverbLevel;
  uint8_t reverbTime;
  uint8_t reverbFeedback;
  uint8_t chorusLevel; // 7: chorus mode
  uint8_t chorusDepth;
  uint8_t chorusRate;
  uint8_t chorusFeedback;
  uint8_t analogFeel;
  uint8_t level;
  uint8_t pan;
  uint8_t bendRange;
  uint8_t flags;
  // 0: ??
  // 1: ??
  // 2: ??
  // 3: ??
  // 4: portamento mode
  // 5: solo legato
  // 6: portamento switch
  // 7: key assign
  uint8_t portamentoTime; // 7: portamento type
  Tone tones[4];
} __attribute__((__packed__)); // 362 bytes
#pragma pack(pop)
