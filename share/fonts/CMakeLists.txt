file (GLOB FONT_FILES *.ttf)

install (
	FILES ${FONT_FILES}
	DESTINATION ${INSTALL_SHARE_DIR}/fonts
	COMPONENT Share
	)
