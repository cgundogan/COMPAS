# name of the library
LIBNAME         :=  libcompas.a

# absolute path of current directory
LIBROOT         :=  $(CURDIR)

UNITTESTS_PATH  :=  $(LIBROOT)/tests/unit-tests

# path to the unit testing library Unity
UNITY_PATH      := $(UNITTESTS_PATH)/unity

# specify the modules to build
modules         :=  src/routing/spanning_tree

# sources will be filled by included Makefiles
sources         :=

#generic variable to hold names of all binaries
binaries        :=

# transformations for object and dependency files
objects         =   $(sources:%.c=%.o)
dependencies    =   $(objects:%.o=%.d)

# set correct include path for .h files
include_dirs    :=  include

ifneq (, $(filter clean unit-test, $(MAKECMDGOALS)))
# set correct include path for unity when unit-testing
include_dirs    +=  $(UNITY_PATH)
unittests_src   :=  $(shell find $(UNITTESTS_PATH) -name 'unit-tests.c')
unittests_bin   :=  $(unittests_src:%.c=%)
binaries        +=  $(unittests_bin)
endif

CFLAGS          +=  $(addprefix -I, $(include_dirs))
vpath %.h $(include_dirs)

all:

# include Makefiles of modules
include $(addsuffix /module.mk, $(modules))

# create $(LIBNAME).a from modules
$(LIBNAME): $(objects)
	$(AR) rcs $@ $^

# build library by default
.PHONY: all
all: $(LIBNAME)

.PHONY: unit-test
unit-test: LDLIBS += $(LIBNAME)
unit-test: $(LIBNAME) $(unittests_bin)

$(unittests_bin) : % : $(UNITY_PATH)/unity.o %.o

# clean slate
.PHONY: clean
clean:
	$(RM) $(objects) $(LIBNAME) $(dependencies) $(binaries)

ifneq "$(MAKECMDGOALS)" "clean"
    -include $(dependencies)
endif
