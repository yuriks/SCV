MODULE := designer

designer_TARGET := interface-designer
designer_CXXFLAGS :=
designer_LIBS := -lglut -lfreeimage -lGLEW -lGL -lGLU $(scv_TARGET)

include common-rules.mk
