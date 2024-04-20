# idlib_utf8_decoder_set_input

## C Signature
```
int
idlib_utf8_decoder_set_input
  (
    idlib_utf8_decoder* decoder,
    void const* bytes,
    size_t number_of_bytes
  );
```

## Description
Set the input of a decoder.

If this function is invoked successfully, then the decoder is in its initial state wrt the specified array of Bytes.
The initial state is `state = IDLIB_UTF8_DECODER_STATE_START_OF_INPUT` and `code_point = 0'.

## Parameters
- `decoder` A pointer to an `idlib_utf8_decoder` object.
- `bytes` A pointer to an array of `number_of_bytes` Bytes.
- `number_of_bytes` The number of Bytes in the array pointed to by `bytes`.

## Return value
`IDLIB_SUCCESS` on success. `IDLIB_ARGUMENT_INVALID` if `decoder` or `bytes` is a null pointer.
