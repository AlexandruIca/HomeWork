function( set_cxx_standard CXX_TARGET STANDARD )
    set_target_properties( ${CXX_TARGET} PROPERTIES
        CXX_STANDARD ${STANDARD}
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
    )
endfunction()

