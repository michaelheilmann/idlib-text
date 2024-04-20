# idlib_delete_file

## C Signature
```
int
idlib_utf8_reader_get
  (
    idlib_utf8_reader* reader,
    uint32_t* symbol
  );
```

## Description
Get the current symbol.

If this function is invoked successfully, then the current UTF8 symbol of the reader
is assigned to `*symbol`. There are three in-band return values that can also be
assigned to `*symbol`: `IDLIB_UTF8_SYMBOL_START` if the reader is before the start
of the input, `IDLIB_UTF8_SYMBOL_END` if the reader is after the end of the input,
and `IDLIB_UTF8_SYMBOL_ERROR` if the reader was unable to decode a symbol.

## Parameters
- `RETURN` A pointer to a C string. The path name of the file.
- `reader` A pointer to am `idlib_utf8_reader` object.

## Return value
`IDLIB_SUCCESS` on success. `IDLIB_ARGUMENT_INVALID` if `symbol` or `reader` is a null pointer.