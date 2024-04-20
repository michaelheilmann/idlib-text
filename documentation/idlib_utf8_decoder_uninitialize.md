# idlib_utf8_decoder_uninitialize

## C Signature
```
int
idlib_utf8_decoder_uninitialize
  (
    idlib_utf8_decoder* decoder
  );
```

## Description
Uninitialize an `idlib_utf8_decoder` object.

## Parameters
- `decoder` A pointer to an `idlib_utf8_decoder` object.

## Return value
`IDLIB_SUCCESS` on success. `IDLIB_ARGUMENT_INVALID` if `decoder` or `bytes` is a null pointer.
