# idlib_utf8_encoder_set_input

## C Signature
```
int
idlib_utf8_encoder_set_input
  (
    idlib_utf8_encoder* encoder,
    void const* code_points,
    size_t number_of_code_points
  );
```

## Description
Set the input of an `idlib_utf8_reader` object.

If this function is invoked successfully, then the reader is in its initial state wrt the specified array of Unicode Code Points.
The initial state is `state = IDLIB_UTF8_ENCODER_START_OF_INPUT`

## Parameters
- `reader` A pointer to an `idlib_utf8_reader` object.
- `code_points` A pointer to an array of `number_of_code_points` Unicode Code Points.
- `number_of_code_points` The number of Unicode Code Points in the array pointed to by `code_points`.

## Return value
`IDLIB_SUCCESS` on success. `IDLIB_ARGUMENT_INVALID` if `encoder` or `code_points` is a null pointer.
