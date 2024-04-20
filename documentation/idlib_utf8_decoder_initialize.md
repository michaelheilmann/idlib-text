# idlib_utf8_decoder_initialize

## C Signature
```
int
idlib_utf8_decoder_initialize
  (
    idlib_utf8_decoder* decoder,
    void const* bytes,
    size_t number_of_bytes
  );
```

## Description
Initialize an `idlib_utf8_decoder` object.

If this function is invoked successfully, then the decoder is in its initial state wrt the specified array of Bytes.
That is, its current symbol is `IDLIB_UTF8_SYMBOL_START` and its position is before the first Byte of the input.

## Parameters
- `decoder` A pointer to an `idlib_utf8_decoder` object.
- `bytes` A pointer to an array of `number_of_bytes` Bytes.
- `number_of_bytes` The number of Bytes in the array pointed to by `bytes`.

## Return value
`IDLIB_SUCCESS` on success. `IDLIB_ARGUMENT_INVALID` if `decoder` or `bytes` is a null pointer.
