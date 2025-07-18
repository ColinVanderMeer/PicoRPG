#include "audio.h"
#include <mod_play.h>
#include <sound_i2s.h>

void update_mod_player(void)
{
  static int8_t *last_buffer;
  static unsigned char tmp_buffer[SOUND_I2S_BUFFER_NUM_SAMPLES];

  int8_t *buffer = sound_i2s_get_next_buffer();
  if (buffer != last_buffer) {
    last_buffer = buffer;

    // send MOD player output to tmp_buffer:
    mod_play_step(tmp_buffer, SOUND_I2S_BUFFER_NUM_SAMPLES);

    // copy tmp_buffer to I2S output buffer:
    for (int i = 0; i < SOUND_I2S_BUFFER_NUM_SAMPLES; i++) {
      int8_t sample = tmp_buffer[i] - 128;  // make it a signed 8-bit sample
      *buffer++ = sample;
      *buffer++ = sample;
      *buffer++ = sample;
      *buffer++ = sample;
    }
  }
}
