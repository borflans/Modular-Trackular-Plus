#pragma once

#include "AudioStream.h"

class Synth;

class PolySynth : public AudioStream
{
  public:
    PolySynth(void)
      : AudioStream(0, NULL)
    { // PNEM
        for (float& gain : muteGain)
            gain = 1.0f;
    }

    void init(Synth* trackerSynth);
    void setGain(int idx, float gainDB);

    // PNEM: Synth Mute
    void setMuted(int idx, bool muted);
    bool isMuted(int idx) const;
    static void applyMute(float* const* buffers, int count, float from, float target);

    virtual void update(void) override;

    static constexpr int kSend1Offset = 2 * kSynthParts;
    static constexpr int kSend2Offset = 3 * kSynthParts;
    static constexpr int kRightChannelOffset = kSynthParts;

  private:
    Synth* trackerSynth = nullptr;
    bool isBlocked = true;
    float gainDB[kSynthParts] = {};

    // PNEM: Synth Mute
    volatile bool muted[kSynthParts] = {};
    float muteGain[kSynthParts];

    uint8_t overloadCooldownBlocks = 0;
};
