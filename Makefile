ifneq ($(MAKECMDGOALS), release)
    CONFIG := debug
    CXXFLAGS += -g3 -O0 -D_DEBUG
else
    CONFIG := release
    CXXFLAGS += -g0 -O2 -DNDEBUG
endif

JUNK_DIR := bin/$(CONFIG)
CXXFLAGS += -std=c++03 -MMD -Iinclude


MODULES := scv examples

scv_PATH := SCV
examples_PATH := scv_examples
designer_PATH := InterfaceDesigner
freeform_designer_PATH := FreeFormInterfaceDesigner

include $(foreach i,$(MODULES),$($(i)_PATH)/rules.mk)

.DEFAULT_GOAL :=
.PHONY : all
all : $(foreach i,$(MODULES),$($(i)_TARGET))

.PHONY : release
release : all

.PHONY : clean
clean :
	rm -rf bin
