# idlib_utf8_decoder_next

## C Signature
```
int
idlib_utf8_decoder_next
  (
    idlib_utf8_decoder* decoder
  );
```

## Description
Advance the decoder to the next symbol.

If this function is invoked successfully, then it has two possible outcomes:
- If the state of the decoder is `IDLIB_UTF8_DECODER_STATE_END_OF_INPUT` or `IDLIB_UTF8_DECODER_STATE_ERROR` when this function is invoked successfully, then the state of the decoder is retained.
bol of the decoder is `IDLIB_UTF8_SYMBOL_ERROR` or `IDLIB_UTF8_SYMBOL_END` when this function is invoked succcessfully, then the state of the decoder remains unchanged.
- If decoding the next symbol fails then the position is not changed and the symbol is set to `IDLIB_UTF8_SYMBOL_ERROR`.
- The next symbol is successfully decoded.


## Parameters
- `decoder` A pointer to an `idlib_utf8_decoder` object.

## Return value
`IDLIB_SUCCESS` on success. `IDLIB_ARGUMENT_INVALID` if `decoder` is a null pointer.
