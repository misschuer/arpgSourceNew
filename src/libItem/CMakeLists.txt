   
 
file(GLOB sources_localdir *.cpp *.h *.c *.cc)


add_library(item STATIC ${sources_localdir})
#add_executable(http_client ${http_STAT_SRCS})
target_link_libraries(item libmongoclient comm)

if (MSVC)	
  set_target_properties(item PROPERTIES FOLDER "lib")
endif()
