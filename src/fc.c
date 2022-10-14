#include <stdio.h>

#include "fc.h"

void fc_sync(FrameCounter* fc, float delta) {
    
    if(!fc->report) {
        if(fc->timer >= 1.0F) {
            fc->frames = 0;
            fc->timer  = 0.0F;
        }

        fc->timer += delta;
        fc->frames += 1;

        if(fc->timer >= 1.0F) {
            fc->report = true;
        }
    }
}

void fc_print(FrameCounter* fc) {
    if(fc->report) {
        printf("[FPS]: %ld\n", fc->frames);
        fc->report = false;
    }
}