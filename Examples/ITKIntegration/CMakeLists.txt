if(NOT CMAKE_PROJECT_NAME STREQUAL "SimpleITK")
  find_package ( ITK )
  include( ${ITK_USE_FILE} )
  find_package ( Elastix )
  include ( ${ELASTIX_USE_FILE} )
endif()

# set( NV_OPENCL_LIB /usr/local/cuda/lib64/libOpenCL.so )


add_executable ( ITKIntegration ITKIntegration.cxx )
target_link_libraries ( ITKIntegration ${ELASTIX_LIBRARIES} ${SimpleITK_LIBRARIES} ${ITK_LIBRARIES} ${OPENCL_LIBRARIES} )

add_executable ( ElastixFilter ElastixFilter.cxx )
target_link_libraries( ElastixFilter ${ELASTIX_LIBRARIES} ${SimpleITK_LIBRARIES} ${ITK_LIBRARIES} ${OPENCL_LIBRARIES} )

add_executable ( TransformixFilter TransformixFilter.cxx )
target_link_libraries( TransformixFilter ${ELASTIX_LIBRARIES} ${SimpleITK_LIBRARIES} ${ITK_LIBRARIES} ${OPENCL_LIBRARIES} )
