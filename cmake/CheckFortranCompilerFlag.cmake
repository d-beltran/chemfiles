# - Check whether the Fortan compiler supports a given flag.
# CHECK_FORTRAN_COMPILER_FLAG(<flag> <var>)
#  <flag> - the compiler flag
#  <var>  - variable to store the result
# This internally calls the check_fortran_source_compiles macro.  See help
# for CheckFortranSourceCompiles for a listing of variables that can
# modify the build.

INCLUDE(CheckFortranSourceCompiles)

MACRO (CHECK_FORTRAN_COMPILER_FLAG _FLAG _RESULT)
   SET(SAFE_CMAKE_REQUIRED_DEFINITIONS "${CMAKE_REQUIRED_DEFINITIONS}")
   SET(CMAKE_REQUIRED_DEFINITIONS "${_FLAG}")
   CHECK_FORTRAN_SOURCE_COMPILES("end" ${_RESULT}
     # Some compilers do not fail with a bad flag
     FAIL_REGEX "unrecognized .*option"                     # GNU
     FAIL_REGEX "ignoring unknown option"                   # MSVC
     FAIL_REGEX "[Uu]nknown option"                         # HP
     FAIL_REGEX "[Ww]arning: [Oo]ption"                     # SunPro
     FAIL_REGEX "command option .* is not recognized"       # XL
     )
   SET (CMAKE_REQUIRED_DEFINITIONS "${SAFE_CMAKE_REQUIRED_DEFINITIONS}")
ENDMACRO (CHECK_FORTRAN_COMPILER_FLAG)
