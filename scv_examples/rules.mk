MODULE := examples

examples_TARGET := scv_examples
examples_CXXFLAGS :=
examples_LIBS := -lglut -lfreeimage -lGLEW -lGL -lGLU
examples_LOCALLIBS := $(scv_TARGET)

include common-rules.mk
