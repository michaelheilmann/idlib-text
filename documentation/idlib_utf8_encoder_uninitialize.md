# idlib_utf8_encoder_uninitialize

## C Signature
```
int
idlib_utf8_encoder_uninitialize
  (
    idlib_utf8_encoder* encoder
  );
```

## Description
Uninitialize an `idlib_utf8_encoder` object.

## Parameters
- `reader` A pointer to an `idlib_utf8_encoder` object.

## Return value
`IDLIB_SUCCESS` on success. `IDLIB_ARGUMENT_INVALID` if `reader` or `bytes` is a null pointer.
