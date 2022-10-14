#ifndef  DYNA_FRAME_COUNTER_H
#define  DYNA_FRAME_COUNTER_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    size_t frames;
    float timer;
    bool report;
} FrameCounter;

void fc_sync(FrameCounter* fc, float delta);
void fc_print(FrameCounter* fc);

#endif //DYNA_FRAME_COUNTER_H