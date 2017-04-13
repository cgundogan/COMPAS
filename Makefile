# name of the library
LIBNAME         :=  libcompas.a

# absolute path of current directory
LIBROOT         :=  $(CURDIR)

# path to the unit tests
UNITTESTS_PATH  :=  $(LIBROOT)/tests/unit-tests

# path to the unit testing library Unity
UNITY_PATH      := $(UNITTESTS_PATH)/unity

# specify the modules to build
modules         :=  src/routing

# sources will be filled by included Makefiles
sources         := $(wildcard $(modules:%=%/*.c))

# transformations for object and dependency files
objects         =   $(sources:%.c=%.o)
dependencies    =   $(objects:%.o=%.d)

# for clean-up
rm_binaries     =   $(sources:%.c=%.o)

# set correct include path for .h files
include_dirs    :=  include

ifneq (, $(filter clean unit-test unit-test-run, $(MAKECMDGOALS)))
# set correct include path for unity when unit-testing
include_dirs    +=  $(UNITY_PATH)
unittests_src   :=  $(shell find $(UNITTESTS_PATH) -name 'unit-tests.c')
unittests_bin   :=  $(unittests_src:%.c=%)
unity_obj       :=  $(UNITY_PATH)/unity.o
dependencies    +=  $(unittests_src:%.c=%.d) $(unity_obj:%.o=%.d)
rm_binaries     +=  $(unittests_src:%.c=%.o) $(unittests_bin) $(unity_obj)
endif

CFLAGS          +=  $(addprefix -I, $(include_dirs))
vpath %.h $(include_dirs)

# set automatic dependency generation
CFLAGS          +=  -MD -MP

all:

# create dependency files
$(dependencies): $(objects)

# create $(LIBNAME).a from modules
$(LIBNAME): $(objects)
	$(AR) rcs $@ $^

# build library by default
.PHONY: all
all: $(LIBNAME)

# build all unit-tests and link $(LIBTOOL).a
.PHONY: unit-test
unit-test: LDLIBS += $(LIBNAME)
unit-test: $(LIBNAME) $(unittests_bin)

# static pattern to build all unit-tests with unity
$(unittests_bin) : % : $(unity_obj) %.o

# run all unit tests
.PHONY: unit-test-run
unit-test-run: unit-test
	@ for u in $(unittests_bin); do $$u; done

# clean slate
.PHONY: clean
clean:
	$(RM) $(rm_binaries) $(LIBNAME) $(dependencies)

ifneq "$(MAKECMDGOALS)" "clean"
    include $(dependencies)
endif
