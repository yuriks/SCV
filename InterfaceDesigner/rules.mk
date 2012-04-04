MODULE := designer

designer_TARGET := interface-designer
designer_CXXFLAGS :=
designer_LIBS := -lglut -lfreeimage -lGLEW -lGL -lGLU
designer_LOCALLIBS := $(scv_TARGET)

include common-rules.mk
