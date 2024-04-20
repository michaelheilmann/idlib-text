#
# IdLib Text
# Copyright (C) 2018-2024 Michael Heilmann. All rights reserved.
#
# This software is provided 'as-is', without any express or implied
# warranty.  In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.
#

cmake_minimum_required(VERSION 3.20)

project(idlib-text LANGUAGES C)

set(idlib-text.idlib-process-directory "${CMAKE_CURRENT_SOURCE_DIR}/external/idlib-process-1.1")

set(idlib-text-cmake-files-dir "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_subdirectory(library)
add_subdirectory(${idlib-text.idlib-process-directory})

enable_testing()
add_subdirectory(test/decode)
add_subdirectory(test/encode)
