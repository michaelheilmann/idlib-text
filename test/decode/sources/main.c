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

#include <stdlib.h>

static int
do_decode_test
  (
    idlib_utf8_decoder_result const* output,
    size_t number_of_outputs,
    uint8_t const* inputs,
    size_t number_of_inputs
  )
{
  idlib_utf8_decoder decoder;
  int result;
  result = idlib_utf8_decoder_initialize(&decoder, inputs, number_of_inputs);
  if (result) {
    return result;
  }
  for (size_t i = 0; i < number_of_outputs; ++i) {
    idlib_utf8_decoder_result temporary;
    result = idlib_utf8_decoder_get(&decoder, &temporary);
    if (result) {
      idlib_utf8_decoder_uninitialize(&decoder);
      return result;
    }
    if (temporary.state != output[i].state || temporary.code_point != output[i].code_point) {
      idlib_utf8_decoder_uninitialize(&decoder);
      return IDLIB_ENVIRONMENT_FAILED;
    }
    result = idlib_utf8_decoder_next(&decoder);
    if (result) {
      idlib_utf8_decoder_uninitialize(&decoder);
      return result;
    }
  }
  result = idlib_utf8_decoder_uninitialize(&decoder);
  if (result) {
    return result;
  }
  return IDLIB_SUCCESS;
}

static int
decode_test_1
  (
  )
{
  int result;
  static const idlib_utf8_decoder_result output[] = 
                                   { { .code_point = '\0', .state = IDLIB_UTF8_DECODER_STATE_START_OF_INPUT },
                                     { .code_point = 'H',  .state = IDLIB_UTF8_DECODER_STATE_NORMAL }, 
                                     { .code_point = 'e',  .state = IDLIB_UTF8_DECODER_STATE_NORMAL },
                                     { .code_point = 'l',  .state = IDLIB_UTF8_DECODER_STATE_NORMAL },
                                     { .code_point = 'l',  .state = IDLIB_UTF8_DECODER_STATE_NORMAL },
                                     { .code_point = 'o',  .state = IDLIB_UTF8_DECODER_STATE_NORMAL },
                                     { .code_point = ',',  .state = IDLIB_UTF8_DECODER_STATE_NORMAL },
                                     { .code_point = ' ',  .state = IDLIB_UTF8_DECODER_STATE_NORMAL },
                                     { .code_point = 'W',  .state = IDLIB_UTF8_DECODER_STATE_NORMAL },
                                     { .code_point = 'o',  .state = IDLIB_UTF8_DECODER_STATE_NORMAL },
                                     { .code_point = 'r',  .state = IDLIB_UTF8_DECODER_STATE_NORMAL }, 
                                     { .code_point = 'l',  .state = IDLIB_UTF8_DECODER_STATE_NORMAL },
                                     { .code_point = 'd',  .state = IDLIB_UTF8_DECODER_STATE_NORMAL },
                                     { .code_point = '!',  .state = IDLIB_UTF8_DECODER_STATE_NORMAL },
                                     { .code_point = '\0', .state = IDLIB_UTF8_DECODER_STATE_END_OF_INPUT  },
                                   };
  static const uint8_t input[] = { 'H', 'e', 'l', 'l', 'o', ',',
                                   ' ',
                                   'W', 'o', 'r', 'l', 'd', '!', };
  result = do_decode_test(output, sizeof(output) / sizeof(idlib_utf8_decoder_result), input, sizeof(input) / sizeof(uint8_t));
  return result;
}

static int
decode_test_2
  (
  )
{
  int result;
  static const idlib_utf8_decoder_result output[] =
                                  { 
                                    { .code_point = '\0', .state = IDLIB_UTF8_DECODER_STATE_START_OF_INPUT, },
                                    { .code_point = 0x3C0, .state = IDLIB_UTF8_DECODER_STATE_NORMAL },   // pi (two byte) https://www.compart.com/en/unicode/U+03C0
                                    { .code_point = 0x20AC, .state = IDLIB_UTF8_DECODER_STATE_NORMAL },  // euro (three byte) https://www.compart.com/en/unicode/U+20AC
                                    { .code_point = 0x1F31D, .state = IDLIB_UTF8_DECODER_STATE_NORMAL }, // smiley (four byte) https://www.compart.com/en/unicode/U+1F31D
                                    { .code_point = '\0', .state = IDLIB_UTF8_DECODER_STATE_END_OF_INPUT }
                                  };
  static const uint8_t input[] = { 0xCF, 0x80,
                                   0xE2, 0x82, 0xAC,
                                   0xF0, 0x9F, 0x8C, 0x9D };
  result = do_decode_test(output, sizeof(output) / sizeof(idlib_utf8_decoder_result), input, sizeof(input) / sizeof(uint8_t));
  return result;
}

int
main
  (
    int argc,
    char** argv
  )
{ 
  if (decode_test_1()) {
    return EXIT_FAILURE;
  }
  if (decode_test_2()) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
