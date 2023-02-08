function(export_headers TARGET HEADER_SRC_DIR HEADER_DEST_DIR)
	# extract header files
	file(GLOB_RECURSE HEADERS
		CONFIGURE_DEPENDS 
		RELATIVE "${HEADER_SRC_DIR}" "${HEADER_SRC_DIR}/*.h")

	foreach(HEADER ${HEADERS})
		# extract header's directory
		get_filename_component(HEADER_DIRECTORY "${HEADER}" DIRECTORY)

		# create dest's subdirectory
		add_custom_command(TARGET "${TARGET}"
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E make_directory ${HEADER_DEST_DIR}/${HEADER_DIRECTORY})

		# create symbol link
		add_custom_command(TARGET "${TARGET}"
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E 
			create_symlink ${HEADER_SRC_DIR}/${HEADER} ${HEADER_DEST_DIR}/${HEADER})
	endforeach()
endfunction()
