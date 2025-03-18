# Makefile to build class 'f0_fold' for Pure Data.
# Needs Makefile.pdlibbuilder as helper makefile for platform-dependent build
# settings and rules.

# library name
lib.name = f0_fold

# input source file (class name == source file basename)
class.sources = f0_fold.c

# all extra files to be included in binary distribution of the library
datafiles = f0_fold-help.pd f0_fold-meta.pd

# include Makefile.pdlibbuilder from submodule directory 'pd-lib-builder'
PDLIBBUILDER_DIR=../pd-lib-builder/
include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder
