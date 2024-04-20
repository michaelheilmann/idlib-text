#include "idlib/text/utf8_encoder.h"

int
idlib_utf8_encoder_initialize
  (
    idlib_utf8_encoder* encoder,
    void const* code_points,
    size_t number_of_code_points
  )
{
  encoder->start = code_points;
  encoder->end = ((uint32_t*)code_points) + number_of_code_points;
  encoder->current = encoder->start;
  encoder->result.state = IDLIB_UTF8_ENCODER_STATE_START_OF_INPUT;
  for (size_t i = 0; i < 4; ++i) {
    encoder->result.bytes[i] = '\0';
  }
  return IDLIB_SUCCESS;
}

int
idlib_utf8_encoder_uninitialize
  (
    idlib_utf8_encoder* encoder
  )
{
  if (!encoder) {
    return IDLIB_ARGUMENT_INVALID;
  }
  return IDLIB_SUCCESS;
}

int
idlib_utf8_encoder_next
  (
    idlib_utf8_encoder* encoder
  )
{ 
  if (encoder->result.state == IDLIB_UTF8_ENCODER_STATE_END_OF_INPUT || encoder->result.state == IDLIB_UTF8_ENCODER_STATE_ERROR) {
    return IDLIB_SUCCESS;
  }
  if (encoder->current == encoder->end) {
    encoder->result.bytes[0] = 0;
    encoder->result.bytes[1] = 0;
    encoder->result.bytes[2] = 0;
    encoder->result.bytes[3] = 0;
    encoder->result.state = IDLIB_UTF8_ENCODER_STATE_END_OF_INPUT;
    return IDLIB_SUCCESS;
  }
  if (0x0 <= *encoder->current && *encoder->current <= 0x7F) {
    encoder->result.bytes[0] = (uint8_t)*encoder->current;
    encoder->result.state = IDLIB_UTF8_ENCODER_STATE_ONE_BYTE;
    encoder->current++;
  } else if (0x80 <= *encoder->current && *encoder->current <= 0x7FF) {
    uint32_t x = *encoder->current;
    encoder->result.bytes[0] = 0xC0 | ((x & 0x7C0) >> 6);
    encoder->result.bytes[1] = 0x80 | ((x & 0x03F) >> 0);
    encoder->result.bytes[2] = 0;
    encoder->result.bytes[3] = 0;
    encoder->result.state = IDLIB_UTF8_ENCODER_STATE_TWO_BYTE;
    encoder->current++;
  } else if (0x800 <= *encoder->current && *encoder->current <= 0xFFFF) {
    uint32_t x = *encoder->current;
    encoder->result.bytes[0] = 0xE0 | ((x & 0xF000) >> 12);
    encoder->result.bytes[1] = 0x80 | ((x & 0x0FC0) >> 6);
    encoder->result.bytes[2] = 0x80 | ((x & 0x003F) >> 0);
    encoder->result.bytes[3] = 0;
    encoder->result.state = IDLIB_UTF8_ENCODER_STATE_THREE_BYTE;
    encoder->current++;
  } else if (0x10000 <= *encoder->current && *encoder->current <= 0x10FFFF) {
    uint32_t x = *encoder->current;
    encoder->result.bytes[0] = 0xF0 | ((x & 0x1C0000) >> 18);
    encoder->result.bytes[1] = 0x80 | ((x & 0x03F000) >> 12);
    encoder->result.bytes[2] = 0x80 | ((x & 0x000FC0) >> 6);
    encoder->result.bytes[3] = 0x80 | ((x & 0x00003F) >> 0);
    encoder->result.state = IDLIB_UTF8_ENCODER_STATE_FOUR_BYTE;
    encoder->current++;
  } else {
    encoder->result.bytes[0] = 0;
    encoder->result.bytes[1] = 0;
    encoder->result.bytes[2] = 0;
    encoder->result.bytes[3] = 0;
    encoder->result.state = IDLIB_UTF8_ENCODER_STATE_ERROR;
  }
  return IDLIB_SUCCESS;
}

int
idlib_utf8_encoder_get
  ( 
    idlib_utf8_encoder* encoder,
    idlib_utf8_encoder_result* result
  )
{
  *result = encoder->result;
  return IDLIB_SUCCESS;
}

int
idlib_utf8_encoder_set_input
  (   
    idlib_utf8_encoder* encoder,
    void const* code_points,
    size_t number_of_code_points
  )
{
  encoder->start = code_points;
  encoder->end = ((uint32_t*)code_points) + number_of_code_points;
  encoder->current = encoder->start;
  encoder->result.state = IDLIB_UTF8_ENCODER_STATE_START_OF_INPUT;
  for (size_t i = 0; i < 4; ++i) {
    encoder->result.bytes[i] = '\0';
  }
  return IDLIB_SUCCESS;
}
