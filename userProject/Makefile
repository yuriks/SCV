# BUILD SETTINGS ###########################################

TARGET := userProject

# FLAGS ####################################################

ifneq ($(MAKECMDGOALS), release)
    CONFIG := debug
    EXTRA_CXXFLAGS += -g3 -O0
else
    CONFIG := release
    EXTRA_CXXFLAGS += -g0 -O2 -DNDEBUG
endif
EXTRA_CXXFLAGS += -pedantic -Werror -Wall -Wextra -Wno-unused

ALL_CXXFLAGS += -std=c++0x -MMD -I./src -I../include $(EXTRA_CXXFLAGS) $(CXXFLAGS)
ALL_LDFLAGS += -L../bin $(LDFLAGS)
LDLIBS += -lglut -lGLEW -lGL -lGLU -lscv

ifeq ($(UNAME), Darwin)
	CXX := clang++
	ALL_CXXFLAGS += -stdlib=libc++
	ALL_LDFLAGS += -stdlib=libc++
endif

############################################################

TARGET := bin/$(TARGET)
JUNK_DIR := bin/obj-$(CONFIG)

STRIP := strip

OBJS := $(shell find src -name *.cpp | sed "s/^src\///")
OBJS := $(foreach obj, $(OBJS:.cpp=.o), $(JUNK_DIR)$(obj))

# RULES ####################################################

.PHONY : all release clean

all : $(TARGET)

release : all
	$(STRIP) $(TARGET)

clean :
	rm -rf bin/*

ifneq ($(MAKECMDGOALS), clean)
    -include $(OBJS:.o=.d)
endif

$(TARGET) : $(OBJS)
	$(CXX) -o $@ $(ALL_LDFLAGS) $^ $(LDLIBS)

$(JUNK_DIR)%.o : src/%.cpp
	@mkdir -p "$(dir $@)"
	$(CXX) -c -o $@ $(ALL_CXXFLAGS) $<
