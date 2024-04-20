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

#if !defined(IDLIB_TEXT_UTF8_DECODER_H_INCLUDED)
#define IDLIB_TEXT_UTF8_DECODER_H_INCLUDED

#include "idlib/text/utf8_symbols.h"

#define IDLIB_UTF8_DECODER_STATE_NORMAL (0)
#define IDLIB_UTF8_DECODER_STATE_START_OF_INPUT (1)
#define IDLIB_UTF8_DECODER_STATE_END_OF_INPUT (2)
#define IDLIB_UTF8_DECODER_STATE_ERROR (3)


typedef struct idlib_utf8_decoder_result {
  uint32_t state;
  uint32_t code_point;
} idlib_utf8_decoder_result;

typedef struct idlib_utf8_decoder {
  char const* start;
  char const* end;
  char const* current;
  uint8_t state;
  uint32_t code_point;
} idlib_utf8_decoder;

int
idlib_utf8_decoder_initialize
  (
    idlib_utf8_decoder* decoder,
    void const* bytes,
    size_t number_of_bytes
  );

int
idlib_utf8_decoder_uninitialize
  (
    idlib_utf8_decoder* decoder
  );

int
idlib_utf8_decoder_next
  (
    idlib_utf8_decoder* decoder
  );

int
idlib_utf8_decoder_get
  (
    idlib_utf8_decoder* decoder,
    idlib_utf8_decoder_result* result
  );

int
idlib_utf8_decoder_set_input
  (
    idlib_utf8_decoder* decoder,
    void const* bytes,
    size_t number_of_bytes
  );

#endif // IDLIB_TEXT_UTF8_DECODER_H_INCLUDED
