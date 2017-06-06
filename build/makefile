# *************************************************************
# Makefile for RapidJasonWrapperLibrary
# *************************************************************

SRCDIR = ../src
BLDDIR = .
INCDIR = ../src/lib/rapidjson/include/rapidjson/
EXE = JSONformatter

#################### Options ###################################
CFLAGS = -O2 -g -Wall -Wextra -c -std=c++11

#################### Objects ###################################

OBJS = $(BLDDIR)/rapidJSON_api.o \
	$(BLDDIR)/formatJSON.o \
    $(BLDDIR)/main.o
################### Target #####################################
all:
	g++ $(CFLAGS) -I$(INCDIR) $(SRCDIR)/*.cpp
	g++ -o $(EXE) $(OBJS)

clean: 
	rm -rf $(BLDDIR)/*.o
	rm -rf $(EXE)
