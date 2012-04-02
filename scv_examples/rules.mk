MODULE := examples

examples_TARGET := scv_examples
examples_CXXFLAGS :=
examples_LIBS := -lfreeglut -lFreeImage -lglew

include common-rules.mk
