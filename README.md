# IdLib Text
*IdLib Text* provides Unicode Code Point and UTF 8 related functionality in C.
*IdLib Text* is licensed under the [zlib License](LICENSE).

## Integration into your CMake project
Integrating *IdLib Text* into the sources of your CMake-based project is the intended use of *IdLib Text*.

Follow these steps to integrate this library into your CMake-based project:

- Create a directory for external dependencies within your project directory. For example `3rdparty`.
- Create a folder `idlib-text` in that directory.
- Download/checkout *IdLib Text* into that folder such that the contents of the directory in which this `README.md` file is located in directly resides under `3rdparty/idlib-text`.
- Add to your project the `3rdparty/idlib-text/CMakeLists.txt` using `add_subdirectory`.
- Link your target `YourTarget` to *IdLib Text* using `target_link_libraries(YourTarget idlib-text)`.
- In your C/C++ code, you now can include now the functionality of *IdLib Text* by adding the preprocessor include directive `#include "idlib/text.h"`.

## Building
For development (or if you really want to use prebuilt binaries), you can do standalone builds of *IdLib Text*.

*IdLib Text* has been tested to build and run both under *Windows 11* and *Linux*.
Find the build instrutions for the respective systems below:
- [Building *IdLib Text*: Windows 11/Visual Studio Community](building-under-windows-11-visual-studio-community-20222)
- [Building *IdLib Text*: Linux](building-under-linux)

## Documentation
The documentation is provided as a set of MarkDown files directly in this repository.

Start reading the documentation here [documentation/idlib-text.md](documentation/idlib-text.md).
