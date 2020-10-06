#pragma once

typedef enum {
  SUB128 = 0,
  SUB64,
  SUB32,
}SUBSAMPLE;

void Sample(size_t num_images, SUBSAMPLE sub_sample);