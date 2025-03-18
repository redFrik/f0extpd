# Makefile to build class 'f0_slub' for Pure Data.
# Needs Makefile.pdlibbuilder as helper makefile for platform-dependent build
# settings and rules.

# library name
lib.name = f0_slub

# input source file (class name == source file basename)
class.sources = f0_slub.c

# all extra files to be included in binary distribution of the library
datafiles = f0_slub-help.pd f0_slub-meta.pd

# include Makefile.pdlibbuilder from submodule directory 'pd-lib-builder'
PDLIBBUILDER_DIR=../pd-lib-builder/
include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder
