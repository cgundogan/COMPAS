local_dir       :=  $(dir $(lastword $(filter-out $(lastword $(MAKEFILE_LIST)), $(MAKEFILE_LIST))))
local_lib       :=  $(local_dir)$(notdir $(local_dir:%/=%)).a
local_src       :=  $(wildcard $(addsuffix *.c, $(local_dir)))
local_objs      :=  $(local_src:%.c=%.o)

sources         +=  $(local_src)
module_libs     +=  $(local_lib)

$(local_lib): $(local_objs)
	$(AR) rcs $@ $^
