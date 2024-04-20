/*
  IdLib Text
  Copyright (C) 2018-2024 Michael Heilmann. All rights reserved.

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#define IDLIB_PROCESS_PRIVATE (1)
#include "idlib/text/utf8_decoder.h"

#include <assert.h>

int
idlib_utf8_decoder_initialize
  (
    idlib_utf8_decoder* decoder,
    void const* bytes,
    size_t number_of_bytes
  )
{
  decoder->start = bytes;
  decoder->end = ((uint8_t*)bytes) + number_of_bytes;
  decoder->current = decoder->start;
  decoder->state = IDLIB_UTF8_DECODER_STATE_START_OF_INPUT;
  decoder->code_point = '\0';
  return IDLIB_SUCCESS;
}

int
idlib_utf8_decoder_uninitialize
  (
    idlib_utf8_decoder* decoder
  )
{
  if (!decoder) {
    return IDLIB_ARGUMENT_INVALID;
  }
  return IDLIB_SUCCESS;
}

int
idlib_utf8_decoder_next
  (
    idlib_utf8_decoder* decoder
  )
{
  if (!decoder) {
    return IDLIB_ARGUMENT_INVALID;
  }
  if (decoder->state == IDLIB_UTF8_DECODER_STATE_END_OF_INPUT || decoder->state == IDLIB_UTF8_DECODER_STATE_ERROR) {
    return IDLIB_SUCCESS;
  }
  if (decoder->current == decoder->end) {
    decoder->state = IDLIB_UTF8_DECODER_STATE_END_OF_INPUT;
    decoder->code_point = '\0';
    return IDLIB_SUCCESS;
  }
  decoder->state = IDLIB_UTF8_DECODER_STATE_NORMAL;
  uint32_t code_point = 0;
  uint8_t *current = (uint8_t*)decoder->current;
  size_t n = 0;
  if (((*current) & 0x80) == 0x00) {
    // To determine if the first Byte is in the range 0xxx xxxx,
    // mask the Byte with 1000 0000 / 0x80. If the result is 0,
    // then the first Byte is in the range 0xxx xxxx.
    n = 0;
    code_point = *current;
  } else if (((*current) & 0xE0) == 0xC0) {
    // To determine if the first Byte is in the range 110x xxxx,
    // mask the Byte with 11100000 / 0xE0. If the result is 1100 0000 / 0xC0,
    // then the first Byte is in the range 110x xxxx.
    n = 1;
    code_point = ((*current) & 0x1F) << 6;    // 0x1F = 11111
  } else if (((*current) & 0xF0) == 0xE0) {
    // To determine if the first Byte is in the range 1110 xxxx,
    // mask the Byte with 1111 0000 / 0xF0. If the result is 1110 0000 / 0xE0,
    // then the first Byte is in the range 1110 xxxx.
    n = 2;
    code_point = ((*current) & 0x0f) << 12; // 0xf = 1111
  } else if (((*current) & 0xF8) == 0xF0) {
    // To determine if the first Byte is in the range 1111 0xxx,
    // mask the Byte with 1111 1000 / 0xF8. If the result is 1111 0000 / 0xF0,
    // then the first Byte is in th range 1111 0xxx.
    n = 3;
    code_point = ((*current) & 0x7) << 18; // 0x7 = 111
  } else {
    decoder->state = IDLIB_UTF8_DECODER_STATE_ERROR;
    decoder->code_point = '\0';
    return IDLIB_SUCCESS;
  }
   
  assert(0 <= n && n <= 3);
  
  current++;
  for (size_t i = 0; i < n; ++i) {
    if (current == decoder->end) {
      decoder->state = IDLIB_UTF8_DECODER_STATE_ERROR;
      decoder->code_point = '\0';
      return IDLIB_SUCCESS;
    }
     if (((*current) & 0xC0) != 0x80) {
      decoder->state = IDLIB_UTF8_DECODER_STATE_ERROR;
      decoder->code_point = '\0';
      return IDLIB_SUCCESS;
    }
     code_point |= ((*current) & 0x3F) << ((n-1-i)*6);
    current++;
  }
  
  decoder->current = current;
  decoder->code_point = code_point;
  
  return IDLIB_SUCCESS;
}

int
idlib_utf8_decoder_get
  ( 
    idlib_utf8_decoder* decoder,
    idlib_utf8_decoder_result* result
  )
{
  if (!decoder || !result) {
    return IDLIB_ARGUMENT_INVALID;
  }
  result->state = decoder->state;
  result->code_point = decoder->code_point;
  return IDLIB_SUCCESS;
}

int
idlib_utf8_decoder_set_input
  (
    idlib_utf8_decoder* decoder,
    void const* bytes,
    size_t number_of_bytes
  )
{
  if (!decoder || !bytes) {
    return IDLIB_ARGUMENT_INVALID;
  }
  decoder->start = bytes;
  decoder->end = ((uint8_t*)bytes) + number_of_bytes;
  decoder->current = decoder->start;
  decoder->state = IDLIB_UTF8_DECODER_STATE_START_OF_INPUT;
  decoder->code_point = '\0';
  return IDLIB_SUCCESS;
}
