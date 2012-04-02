$(MODULE)_TARGET := bin/$($(MODULE)_TARGET)
$(MODULE)_SOURCES := $(shell find $($(MODULE)_PATH)/src -name *.cpp | sed "s/^$($(MODULE)_PATH)\/src\///")
$(MODULE)_JUNK_DIR := $(JUNK_DIR)/$(MODULE)
$(MODULE)_OBJS := $(foreach obj, $($(MODULE)_SOURCES:.cpp=.o), $($(MODULE)_JUNK_DIR)/$(obj))

$($(MODULE)_JUNK_DIR)/%.o : MODULE := $(MODULE)
$($(MODULE)_JUNK_DIR)/%.o : $($(MODULE)_PATH)/src/%.cpp
	@mkdir -p "$(dir $@)"
	$(CXX) -c -o $@ $(CXXFLAGS) $($(MODULE)_CXXFLAGS) $<

ifeq ($(suffix $($(MODULE)_TARGET)), .a)

$($(MODULE)_TARGET) : MODULE := $(MODULE)
$($(MODULE)_TARGET) : $($(MODULE)_OBJS)
	@mkdir -p "$(dir $@)"
	$(AR) rcs $@ $^

else

$($(MODULE)_TARGET) : MODULE := $(MODULE)
$($(MODULE)_TARGET) : $($(MODULE)_OBJS)
	@mkdir -p "$(dir $@)"
	$(CXX) -o $@ $(LDFLAGS) $($(MODULE)_LDFLAGS) $^ $($(MODULE)_LIBS)

endif
