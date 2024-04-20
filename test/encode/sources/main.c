/*
  IdLib Text
  Copyright (C) 2023-2024 Michael Heilmann. All rights reserved.

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

#include "idlib/text.h"

// EXIT_SUCCESS, EXIT_FAILURE
#include <stdlib.h>

// memcmp
#include <string.h>

static int
do_encode_test
  (
    idlib_utf8_encoder_result const* output,
    size_t number_of_outputs,
    uint32_t const* inputs,
    size_t number_of_inputs
  )
{
  idlib_utf8_encoder encoder;
  int result;
  result = idlib_utf8_encoder_initialize(&encoder, inputs, number_of_inputs);
  if (result) {
    return result;
  }
  for (size_t i = 0; i < number_of_outputs; ++i) {
    idlib_utf8_encoder_result temporary;
    result = idlib_utf8_encoder_get(&encoder, &temporary);
    if (result) {
      idlib_utf8_encoder_uninitialize(&encoder);
      return result;
    }
    if (temporary.state != output[i].state || memcmp(temporary.bytes, output[i].bytes, 4)) {
      idlib_utf8_encoder_uninitialize(&encoder);
      return IDLIB_ENVIRONMENT_FAILED;
    }
    result = idlib_utf8_encoder_next(&encoder);
    if (result) {
      idlib_utf8_encoder_uninitialize(&encoder);
      return result;
    }
  }
  result = idlib_utf8_encoder_uninitialize(&encoder);
  if (result) {
    return result;
  }
  return IDLIB_SUCCESS;
}

static int
encode_test_1
  (
  )
{
  int result;
  static const idlib_utf8_encoder_result output[] = 
                                   { { .bytes = { 0 },            .state = IDLIB_UTF8_ENCODER_STATE_START_OF_INPUT },
                                     { .bytes = { 'H', 0, 0, 0 }, .state = IDLIB_UTF8_ENCODER_STATE_ONE_BYTE }, 
                                     { .bytes = { 'e', 0, 0, 0 }, .state = IDLIB_UTF8_ENCODER_STATE_ONE_BYTE },
                                     { .bytes = { 'l', 0, 0, 0 }, .state = IDLIB_UTF8_ENCODER_STATE_ONE_BYTE },
                                     { .bytes = { 'l', 0, 0, 0 }, .state = IDLIB_UTF8_ENCODER_STATE_ONE_BYTE },
                                     { .bytes = { 'o', 0, 0, 0 }, .state = IDLIB_UTF8_ENCODER_STATE_ONE_BYTE },
                                     { .bytes = { ',', 0, 0, 0 }, .state = IDLIB_UTF8_ENCODER_STATE_ONE_BYTE },
                                     { .bytes = { ' ', 0, 0, 0 }, .state = IDLIB_UTF8_ENCODER_STATE_ONE_BYTE },
                                     { .bytes = { 'W', 0, 0, 0 }, .state = IDLIB_UTF8_ENCODER_STATE_ONE_BYTE },
                                     { .bytes = { 'o', 0, 0, 0 }, .state = IDLIB_UTF8_ENCODER_STATE_ONE_BYTE },
                                     { .bytes = { 'r', 0, 0, 0 }, .state = IDLIB_UTF8_ENCODER_STATE_ONE_BYTE },
                                     { .bytes = { 'l', 0, 0, 0 }, .state = IDLIB_UTF8_ENCODER_STATE_ONE_BYTE },
                                     { .bytes = { 'd', 0, 0, 0 }, .state = IDLIB_UTF8_ENCODER_STATE_ONE_BYTE },
                                     { .bytes = { '!', 0, 0, 0 }, .state = IDLIB_UTF8_ENCODER_STATE_ONE_BYTE },
                                     { .bytes = { 0 },            .state = IDLIB_UTF8_ENCODER_STATE_END_OF_INPUT  },
                                   };
  static const uint32_t input[] = { 'H', 'e', 'l', 'l', 'o', ',',
                                    ' ',
                                    'W', 'o', 'r', 'l', 'd', '!', };
  result = do_encode_test(output, sizeof(output) / sizeof(idlib_utf8_encoder_result), input, sizeof(input) / sizeof(uint32_t));
  return result;
}

static int
encode_test_2
  (
  )
{
  int result;
  static const idlib_utf8_encoder_result output[] =
                                  { 
                                    { .bytes = { 0 }, .state = IDLIB_UTF8_ENCODER_STATE_START_OF_INPUT, },
                                    { .bytes = { 0xCF, 0x80, 0, 0,}, .state = IDLIB_UTF8_ENCODER_STATE_TWO_BYTE },     // pi (two byte) https://www.compart.com/en/unicode/U+03C0
                                    { .bytes = { 0xE2, 0x82, 0xAC, 0 }, .state = IDLIB_UTF8_ENCODER_STATE_THREE_BYTE },  // euro (three byte) https://www.compart.com/en/unicode/U+20AC
                                    { .bytes = { 0xF0, 0x9F, 0x8C, 0x9D }, .state = IDLIB_UTF8_ENCODER_STATE_FOUR_BYTE },  // smiley (four byte) https://www.compart.com/en/unicode/U+1F31D
                                    { .bytes = { 0 }, .state = IDLIB_UTF8_ENCODER_STATE_END_OF_INPUT }
                                  };
  static const uint32_t input[] = { 0x3C0,
                                    0x20AC,
                                    0x1F31D,
                                  };
  result = do_encode_test(output, sizeof(output) / sizeof(idlib_utf8_encoder_result), input, sizeof(input) / sizeof(uint32_t));
  return result;
}

int
main
  (
    int argc,
    char** argv
  )
{ 
  if (encode_test_1()) {
    return EXIT_FAILURE;
  }
  if (encode_test_2()) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
