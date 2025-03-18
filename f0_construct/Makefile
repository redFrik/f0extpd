# Makefile to build class 'f0_construct' for Pure Data.
# Needs Makefile.pdlibbuilder as helper makefile for platform-dependent build
# settings and rules.

# library name
lib.name = f0_construct

# input source file (class name == source file basename)
class.sources = f0_construct.c

# all extra files to be included in binary distribution of the library
datafiles = f0_construct-help.pd f0_construct-meta.pd

# include Makefile.pdlibbuilder from submodule directory 'pd-lib-builder'
PDLIBBUILDER_DIR=../pd-lib-builder/
include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder
