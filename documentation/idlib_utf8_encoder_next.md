# idlib_utf8_reader_next

## C Signature
```
int
idlib_utf8_reader_next
  (
    idlib_utf8_reader* reader
  );
```

## Description
Advance the UTF8 reader to the next symbol.

If this function is invoked successfully, then it has two possible outcomes:
- If the state of the encoder is `IDLIB_UTF8_ENCODER_STATE_END_OF_INPUT` or `IDLIB_UTF8_ENCODER_STATE_ERROR` when this function is invoked succcessfully, then the state of the decoder is retained.
- If encoding the next Unicode Code Point fails then the position is not changed and the state is set to `IDLIB_UTF8_ENCODER_STATE_ERROR`.
- The next Unicode Code Point was successfully encoded.


## Parameters
- `reader` A pointer to an `idlib_utf8_reader` object.

## Return value
`IDLIB_SUCCESS` on success. `IDLIB_ARGUMENT_INVALID` if `reader` is a null pointer.
