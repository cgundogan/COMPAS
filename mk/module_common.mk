local_dir       :=  $(dir $(lastword $(filter-out $(lastword $(MAKEFILE_LIST)), $(MAKEFILE_LIST))))
local_src       :=  $(wildcard $(local_dir)*c)
sources         +=  $(local_src)
