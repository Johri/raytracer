# -*- Makefile -*-

# $Id: Makefile,v 1.1 2008-04-10 09:49:21 guni4317 Exp $

default: targets

UNAME := $(shell uname -s)

prefix =.

include $(prefix)/defines.mk

CXXINCLUDE	+=-I$(prefix)/include -I/opt/local/include
ifeq ($(UNAME), Darwin)
LIBS		+=-framework OpenGL -framework GLUT -lboost_thread-mt -lUnitTest++

else
LIBS		+=-lglut -lGL -lboost_thread -lUnitTest++
endif

EXTRA_LIBS	+=-L$(prefix)/ -Wl,-rpath,. -L/opt/local/lib
MOVE		=mv

HEADER =\
	include/glutwindow.hpp \
	include/pixel.hpp \
	include/ppmwriter.hpp \
	include/color.hpp \
	include/vector.hpp \
	include/point.hpp \
	include/matrix.hpp \
	include/material.hpp \
	include/material_map.hpp \
	include/triangle.hpp \
	include/box.hpp \
	include/point3d.hpp \
	include/ray.hpp \
	include/shape.hpp \
	include/sphere.hpp \
	include/tube.hpp \
	include/cone.hpp \
	include/scene.hpp \
	include/camera.hpp \
	include/light.hpp \
        $(NULL)

SOURCE =\
	src/glutwindow.cpp \
	src/pixel.cpp \
	src/ppmwriter.cpp \
	src/color.cpp \
	src/point.cpp \
	src/vector.cpp \
	src/matrix.cpp \
	src/material.cpp \
	src/material_map.cpp \
	src/main.cpp \
	src/triangle.cpp \
	src/box.cpp \
	src/point3d.cpp \
	src/ray.cpp \
	src/shape.cpp \
	src/sphere.cpp \
	src/tube.cpp \
	src/cone.cpp \
	src/scene.cpp \
	src/camera.cpp \
	src/light.cpp \
	$(NULL)

PROGRAMSOURCE =\
	src/main.cpp \
	$(NULL)

OBJECTS =$(SOURCE:.cpp=.o) 

PROGRAMOBJECT =$(PROGRAMSOURCE:.cpp=.o)

PROGRAMS = 	$(PROGRAMOBJECT:.o=)

targets:	$(PROGRAMS)

$(PROGRAMS):	$(OBJECTS)
	-$(RM) $@
	$(CXX) -o $(prefix)/$@ $(LIBS) $(EXTRA_LIBS) $(LDXXFLAGS) $(OBJECTS)
	$(MOVE) $(prefix)/$@ .

realclean:: clean
	-$(RM) $(prefix)/$(OBJECTS)
	-$(RM) $(prefix)/$(PROGRAMOBJECTS)
	-$(RM) $(prefix)/$(PROGRAMS)

include $(prefix)/rules.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),realclean)
#-include $(OBJECTS:.o=.d)
endif
endif

# $Id: Makefile,v 1.1 2008-04-10 09:49:21 guni4317 Exp $
