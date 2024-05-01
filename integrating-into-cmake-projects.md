# Integrate with your CMake project
The proper way to integrate *IdLib Text* with your CMake project is by using `FetchContent`:

You need to fetch *IdLib Text* and its dependency *IdLib Process*:

You can do that as follows:

```
include(FetchContent)

#######################################################################################################################

set(idlib-process.repository CACHE STRING "IdLib Process: The Git repository to check out")
if (NOT idlib-process.repository)
  set(idlib-process.repository https://github.com/michaelheilmann/idlib-process.git)
endif()

set(idlib-process.tag CACHE STRING "IdLib Process: The Git tag to check out")
if (NOT idlib-process.tag)
  set(idlib-process.tag 1.2)
endif()

set(idlib-process.source-dir CACHE STRING "IdLib Process: Path to the source directory")
if (NOT idlib-process.source-dir)
  set(idlib-process.source-dir "${CMAKE_CURRENT_BINARY_DIR}/idlib-process-1.4-src")
endif()

set(idlib-process.binary-dir CACHE STRING "IdLib Process: Path to the build directory")
if (NOT idlib-process.binary-dir)
  set(idlib-process.binary-dir "${CMAKE_CURRENT_BINARY_DIR}/idlib-process-1.4-bld")
endif()
                    
#######################################################################################################################

set(idlib-text.repository CACHE STRING "IdLib Text: The Git repository to check out")
if (NOT idlib-text.repository)
  set(idlib-text.repository https://github.com/michaelheilmann/idlib-text.git)
endif()

set(idlib-text.tag CACHE STRING "IdLib Text: The Git tag to check out")
if (NOT idlib-text.tag)
  set(idlib-text.tag 1.0)
endif()

set(idlib-text.source-dir CACHE STRING "IdLib Text: Path to the source directory")
if (NOT idlib-text.source-dir)
  set(idlib-text.source-dir "${CMAKE_CURRENT_BINARY_DIR}/idlib-text-1.0-src")
endif()

set(idlib-text.binary-dir CACHE STRING "IdLib Text: Path to the build directory")
if (NOT idlib-text.binary-dir)
  set(idlib-text.binary-dir "${CMAKE_CURRENT_BINARY_DIR}/idlib-text-1.0-bld")
endif()

#######################################################################################################################

FetchContent_Declare(idlib-text
                     GIT_REPOSITORY ${idlib-text.repository}
                     GIT_TAG ${idlib-text.tag}
                     SOURCE_DIR ${idlib-text.source-dir}
                     BINARY_DIR ${idlib-text.binary-dir})

```

Now simply add
```
FetchContent_MakeAvailable(idlib-text)
```
And you can use *IdLib Text* by linking the library target `idlib-text` to a target `<target>`
```
target_link_libraries(my-target idlib-text)
```
and by adding the include-directive  
```
#include "idlib/text.h"
```
in your C files.
