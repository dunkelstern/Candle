TEMPLATE = subdirs
SUBDIRS = qtscript_core \
          qtscript_gui \
          qtscript_widgets \
          qtscript_printsupport \
          qtscript_multimedia \
          qtscript_network \
          qtscript_opengl \
          qtscript_sql \
          qtscript_xml \
          qtscript_uitools \
          qtscript_custom

# there are thousands of deprecation warnings in the generated code, disable them
QMAKE_CXXFLAGS_RELEASE=-Wno-deprecated-declarations
