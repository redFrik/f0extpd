# Makefile to build class 'f0_distance' for Pure Data.
# Needs Makefile.pdlibbuilder as helper makefile for platform-dependent build
# settings and rules.

# library name
lib.name = f0_distance

# input source file (class name == source file basename)
class.sources = f0_distance.c

# all extra files to be included in binary distribution of the library
datafiles = f0_distance-help.pd f0_distance-meta.pd

# include Makefile.pdlibbuilder from submodule directory 'pd-lib-builder'
PDLIBBUILDER_DIR=../pd-lib-builder/
include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder
