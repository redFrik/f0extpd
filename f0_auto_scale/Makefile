# Makefile to build class 'f0_auto_scale' for Pure Data.
# Needs Makefile.pdlibbuilder as helper makefile for platform-dependent build
# settings and rules.

# library name
lib.name = f0_auto_scale

# input source file (class name == source file basename)
class.sources = f0_auto_scale.c

# all extra files to be included in binary distribution of the library
datafiles = f0_auto_scale-help.pd f0_auto_scale-meta.pd

# include Makefile.pdlibbuilder from submodule directory 'pd-lib-builder'
PDLIBBUILDER_DIR=../pd-lib-builder/
include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder
