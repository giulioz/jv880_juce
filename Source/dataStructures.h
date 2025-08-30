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
struct Tone
{
  uint8_t flags; // 0-1: wave group | 7: tone on/off
  uint8_t waveNumber;
  uint8_t fxmConfig; // 7: enable | 1-6: depth
  uint8_t velocityRangeLow;
  uint8_t velocityRangeUp;
  uint8_t matrixModDestAB;
  uint8_t matrixModDestCD;
  uint8_t matrixModSensA;
  uint8_t matrixModSensB;
  uint8_t matrixModSensC;
  uint8_t matrixModSensD;
  uint8_t matrixAftDestAB;
  uint8_t matrixAftDestCD;
  uint8_t matrixAftSensA;
  uint8_t matrixAftSensB;
  uint8_t matrixAftSensC;
  uint8_t matrixAftSensD;
  uint8_t matrixExpDestAB;
  uint8_t matrixExpDestCD;
  uint8_t matrixExpSensA;
  uint8_t matrixExpSensB;
  uint8_t matrixExpSensC;
  uint8_t matrixExpSensD;
  uint8_t lfo1Flags; // 0-1-2: waveform | 3-4-5: offset | 6: key sync | 7: fade in/out
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
  uint8_t tvaPanKFpitchRandom; // high: tva panning | low: random pitch
  uint8_t tvpKFtvaTimeKF;
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
  uint8_t tvaDelayTime;
  uint8_t tvaTimeKFDelayTimeKeyfollow; // (check again) low: key follow
  uint8_t tvaDelayModeVeloCurve;       // low: velo curve
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
}; // 84 bytes
#pragma pack(pop)

#pragma pack(push, 1)
struct Patch
{
  char name[12];
  uint8_t recChorConfig; // 0-3: rev type | 4-5: chorus type | 6: ? | 7: velocity
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
  uint8_t flags; // 0-3: ? | 4: porta mode | 5: solo legato | 6: porta switch | 7: key assign
  uint8_t portamentoTime; // 7: porta type

  Tone tones[4];
}; // 362 bytes
#pragma pack(pop)

#pragma pack(push, 1)
struct RhythmTone
{
  uint8_t flags; // 0-1: wave group | 7: tone on/off
  uint8_t waveNumber;
  uint8_t muteGroup; // 5: envelope mode
  uint8_t pitchCoarse;
  uint8_t pitchFine;
  uint8_t bendRange; // 0-3: pitch time velocity | 4-7: bend range
  uint8_t pitchRandom;
  uint8_t tvpVelocity;
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
  uint8_t tvfVelocity;
  uint8_t tvfTimeVelLpfHpf; // (check) 4-5: LPF/HPF
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
  uint8_t tvaVelocity;
  uint8_t tvaTimeVelocity;
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
}; // 44 bytes
#pragma pack(pop)

#pragma pack(push, 1)
struct Rhythm
{
  RhythmTone tones[61];
}; // 2684 bytes
#pragma pack(pop)
