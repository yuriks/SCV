MODULE := freeform_designer

freeform_designer_TARGET := freeform-interface-designer
freeform_designer_CXXFLAGS :=
freeform_designer_LIBS := -lglut -lGLEW -lGL -lGLU
freeform_designer_LOCALLIBS := $(scv_TARGET)

include common-rules.mk
