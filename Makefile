LIBNAME         :=  libcompas.a
LIBROOT         :=  $(dir $(lastword $(MAKEFILE_LIST)))
modules         :=  src/topology src/metatable
sources         :=
module_libs     :=

objects         =   $(sources:%.c=%.o)
dependencies    =   $(objects:%.o=%.d)

include_dirs    :=  include
CFLAGS          +=  $(addprefix -I, $(include_dirs))
vpath %.h $(include_dirs)

all:

include $(addsuffix /module.mk, $(modules))

$(LIBNAME): $(module_libs)
	$(AR) rcs $@ $^

.PHONY: all
all: $(LIBNAME)

.PHONY: clean
clean:
	$(RM) $(objects) $(module_libs) $(LIBNAME) $(dependencies)
