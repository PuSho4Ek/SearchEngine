if(EXISTS "D:/forWork/MoonUif Inc/Search Engine/Search Engine/cmake-build-debug/src/SearchEngine[1]_tests.cmake")
  include("D:/forWork/MoonUif Inc/Search Engine/Search Engine/cmake-build-debug/src/SearchEngine[1]_tests.cmake")
else()
  add_test(SearchEngine_NOT_BUILT SearchEngine_NOT_BUILT)
endif()