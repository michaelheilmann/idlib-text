#if !defined(ENCODER_H_INCLUDED)
#define ENCODER_H_INCLUDED

#include "idlib/text/utf8_symbols.h"

#define IDLIB_UTF8_ENCODER_STATE_ONE_BYTE (1)
#define IDLIB_UTF8_ENCODER_STATE_TWO_BYTE (2)
#define IDLIB_UTF8_ENCODER_STATE_THREE_BYTE (3)
#define IDLIB_UTF8_ENCODER_STATE_FOUR_BYTE (4)
#define IDLIB_UTF8_ENCODER_STATE_START_OF_INPUT (5)
#define IDLIB_UTF8_ENCODER_STATE_END_OF_INPUT (6)
#define IDLIB_UTF8_ENCODER_STATE_ERROR (7)

typedef struct idlib_utf8_encoder_result {
  uint8_t state;
  uint8_t bytes[4];
} idlib_utf8_encoder_result;

typedef struct idlib_utf8_encoder {
  uint32_t const* start;
  uint32_t const* end;
  uint32_t const* current;
  idlib_utf8_encoder_result result;
} idlib_utf8_encoder;

int
idlib_utf8_encoder_initialize
  (
    idlib_utf8_encoder* encoder,
    void const* code_points,
    size_t number_of_code_points
  );

int
idlib_utf8_encoder_uninitialize
  (
    idlib_utf8_encoder* encoder
  );

int
idlib_utf8_encoder_next
  (
    idlib_utf8_encoder* encoder
  );

int
idlib_utf8_encoder_get
  (
    idlib_utf8_encoder* encoder,
    idlib_utf8_encoder_result* result
  );

int
idlib_utf8_encoder_set_input
  (
    idlib_utf8_encoder* encoder,
    void const* code_points,
    size_t number_of_code_points
  );

#endif // IDLIB_TEXT_UTF8_ENCODER_H_INCLUDED