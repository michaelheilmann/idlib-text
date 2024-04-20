# idlib_utf8_decoder_get

## C Signature
```
int
idlib_utf8_decoder_get
  (
    idlib_utf8_decoder* decoder,
    uint32_t* code_point
  );
```

## Description
Get the current code point.

If this function is invoked successfully, then the current Unicode Code Point of the decoder or an in-band information value is assigned to `*code_point`.
There are three in-band information values neither of which is a valid Unicode Code Point:
- `IDLIB_UTF8_SYMBOL_START` if the decoder is before the start of the input,
- `IDLIB_UTF8_SYMBOL_END` if the decoder is after the end of the input, and
`- IDLIB_UTF8_SYMBOL_ERROR` if the decoder was unable to decode a symbol.

## Parameters
- `decoder` A pointer to am `idlib_utf8_reader` object.
- `code_point` A pointer to `uint32_t` variable.

## Return value
`IDLIB_SUCCESS` on success. `IDLIB_ARGUMENT_INVALID` if `decoder` or `code_point` is a null pointer.
