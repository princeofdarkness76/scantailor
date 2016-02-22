FILE(
	WRITE "${TARGET_FILE}"
	# Without .gitignore Qt 5 assumes configure.exe is present.
	"if not exist configure.exe type nul >>.gitignore"
	"\n"
	# cmd /c is used because it may be configure.bat, which otherwise wouldn't return control.
	"cmd /c configure -platform ${PLATFORM} -debug-and-release -shared -force-debug-info"
	" -no-gif -system-zlib -system-libpng -system-libjpeg -qt-imageformat-jpeg -no-openssl"
	" -opengl desktop -nomake examples -nomake demos -nomake docs"
	" -opensource -confirm-license -no-ltcg"
	" -I \"${JPEG_INCLUDE_DIR}\" -I \"${ZLIB_INCLUDE_DIR}\""
	" -I \"${PNG_INCLUDE_DIR}\" -L \"${JPEG_LINK_DIR}\" -L \"${ZLIB_LINK_DIR}\""
	" -L \"${PNG_LINK_DIR}\""
	" -D _BIND_TO_CURRENT_VCLIBS_VERSION=1"
	"\n"
	"if errorlevel 1 goto exit\n"
	"${MAKE_COMMAND}\n"
	"if errorlevel 1 goto exit\n"
	"${MAYBE_SKIP_BUILDING_TOOLS}\n"
	"cd ..\\qttools\n"
	"if errorlevel 1 goto exit\n"
	"..\\qtbase\\bin\\qmake.exe -makefile -after \"CONFIG += release force_debug_info\" qttools.pro\n"
	"if errorlevel 1 goto exit\n"
	"${MAKE_COMMAND}\n"
	":exit\n"
)