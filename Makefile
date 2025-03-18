# recursively build all example projects in the subdirectories


makefiledirs := $(filter-out _% dev/, $(dir $(wildcard */Makefile)))

PDLIBBUILDER_DIR = pd-lib-builder
include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder

buildcheck installcheck: $(makefiledirs)

runcheck:
	PDBINDIR=$(PDBINDIR) ./test-patches.sh $(makefiledirs:%=%*.pd)

projects:
	@echo $(makefiledirs)
