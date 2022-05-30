

function(git_project)
    #    set(options QUIET)
    set(oneValueArgs
            PROJECT_NAME
            PREFIX
            DOWNLOAD_DIR
            SOURCE_DIR
            BINARY_DIR
            # Prevent the following from being passed through
            CONFIGURE_COMMAND
            BUILD_COMMAND
            INSTALL_COMMAND
            TEST_COMMAND
            )
    set(multiValueArgs "")

    cmake_parse_arguments(DL_ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if (NOT DL_ARGS_SOURCE_DIR)
        set(DL_ARGS_SOURCE_DIR "${CMAKE_BINARY_DIR}/${DL_ARGS_PROJECT_NAME}-src")
    endif ()
    if (NOT DL_ARGS_BINARY_DIR)
        set(DL_ARGS_BINARY_DIR "${CMAKE_BINARY_DIR}/${DL_ARGS_PROJECT_NAME}-build")
    endif ()

    set(${DL_ARGS_PROJECT_NAME}_SOURCE_DIR "${DL_ARGS_SOURCE_DIR}" PARENT_SCOPE)
    set(${DL_ARGS_PROJECT_NAME}_BINARY_DIR "${DL_ARGS_BINARY_DIR}" PARENT_SCOPE)

    include(ExternalProject)
    ExternalProject_Add(${DL_ARGS_PROJECT_NAME}
            ${DL_ARGS_UNPARSED_ARGUMENTS}
            SOURCE_DIR "${DL_ARGS_SOURCE_DIR}"
            BINARY_DIR "${DL_ARGS_BINARY_DIR}"
            UPDATE_COMMAND ""
            INSTALL_COMMAND ""
            )

endfunction()