SHELL = /bin/sh
# I just thought it was time to write a new makefile (=    -Chris

# Version 1.3 of Awake 2062 Makefile. Well, now the Makefile is a lot
# nicer. Auto-generating dependancies,  manual dependancy updates, and
# other such nice additions. Doing a fully recompile should no longer
# EVER be required. -- Khepri

# 1.31, Added CVS capability to Makefile for convenience.

.SUFFIXES :
.SUFFIXES : .cpp .o
.DELETE_ON_ERROR :
.PHONY : unittest
#CXX = g++
CXX = clang
#CXX = /opt/homebrew/Cellar/gcc/11.2.0_3/bin/aarch64-apple-darwin21-g++-11 -Wno-format-truncation -Wno-deprecated-copy
CC = g++
#CC = /opt/homebrew/Cellar/gcc/11.2.0_3/bin/aarch64-apple-darwin21-g++-11 -Wno-format-truncation -Wno-deprecated-copy

PROFILE = -ggdb
CVS = cvs

# I added the DEBUG flag to make extensive checks on lists and such
# in order to find any problems such as not freeing up pointers properly.
# The obvious drawback is that it's time consuming, so once things go
# smooth, the define can be removed.

COMMON_FLAGS = -lmysqlclient -lz -lm -lstdc++ -std=c++11
BOOST_FLAGS = -lboost_filesystem

# You probably want to comment this out: This is the makefile specification for the GitHub runner.
LIBS = -lcrypt -L/usr/local/lib $(COMMON_FLAGS) $(BOOST_FLAGS) -lnsl -lcurl
MYFLAGS = -DNOCRYPT -Dlinux -I /usr/local/include/ -Wall -Wextra -Wno-unused-parameter -Wno-vla -std=c++11

# OSX? Uncomment these:
#LIBS = -L/usr/local/lib $(COMMON_FLAGS) $(BOOST_FLAGS) -lsodium -lcurl
#MYFLAGS = -DUSE_MEMORY_CANARIES -DDEBUG -DSELFADVANCE -Dosx -I /usr/local/include/ -Wall -Wextra -Wno-unused-parameter -std=c++11 -DSUPPRESS_MOB_SKILL_ERRORS -DACCELERATE_FOR_TESTING -D_GLIBCXX_DEBUG

# Linux / others? Uncomment these:
#LIBS = -lcrypt -L/usr/local/lib $(COMMON_FLAGS) -lnsl -lsodium -lcurl
#MYFLAGS = -DDEBUG_CRYPTO -DDEBUG -DSELFADVANCE -DIDLEDELETE_DRYRUN -Dlinux -I /usr/local/include/ -Wall -Wextra -Wno-unused-parameter -DSUPPRESS_MOB_SKILL_ERRORS -std=c++11
# If you want GitHub integration, add -DGITHUB_INTEGRATION to the above and fill out your basic auth credentials in github_config.cpp.

# Cygwin:
#LIBS = -L/usr/local/lib $(COMMON_FLAGS) -lsodium -lcrypt
#MYFLAGS = -DDEBUG -DSELFADVANCE -DIDLEDELETE_DRYRUN -DWIN32 -I /usr/local/include/ -Wall -Wextra -Wno-unused-parameter -DSUPPRESS_MOB_SKILL_ERRORS -std=c++11

CPPFLAGS = $(MYFLAGS) $(PROFILE)

sourcefiles = $(wildcard *.cpp)
objfiles = $(sourcefiles:.cpp=.o)
dependfiles = $(wildcard *.d)

../bin/awake.new : $(objfiles)

utils:
	$(MAKE) ../bin/autowiz
	$(MAKE) ../bin/delobjs
	$(MAKE) ../bin/listrent
	$(MAKE) ../bin/mudpasswd
	$(MAKE) ../bin/purgeplay
	$(MAKE) ../bin/showplay
	$(MAKE) ../bin/sign
	$(MAKE) ../bin/split
	$(MAKE) ../bin/plrtoascii
	$(MAKE) ../bin/convmob
	$(MAKE) ../bin/convobj
	$(MAKE) ../bin/convwld

autowiz:
	$(MAKE) ../bin/autowiz
delobjs:
	$(MAKE) ../bin/delobjs
listrent:
	$(MAKE) ../bin/listrent
mudpasswd:
	$(MAKE) ../bin/mudpasswd
purgeplay:
	$(MAKE) ../bin/purgeplay
showplay:
	$(MAKE) ../bin/showplay
sign:
	$(MAKE) ../bin/sign
split:
	$(MAKE) ../bin/split
plrtoascii:
	$(MAKE) ../bin/plrtoascii
convmob:
	$(MAKE) ../bin/convmob
convobj:
	$(MAKE) ../bin/convobj
convwld:
	$(MAKE) ../bin/convwld

../bin/autowiz : util/autowiz.cc structs.hpp db.hpp utils.hpp
	$(CXX) $(CPPFLAGS) -o ../bin/autowiz util/autowiz.cc
../bin/delobjs : util/delobjs.cc structs.hpp
	$(CXX) $(CPPFLAGS) -o ../bin/delobjs util/delobjs.cc
../bin/listrent : util/listrent.cc structs.hpp

	$(CXX) $(CPPFLAGS) -o ../bin/listrent util/listrent.cc
../bin/mudpasswd   : util/mudpasswd.cc structs.hpp
	$(CXX) $(CPPFLAGS) -o ../bin/mudpasswd util/mudpasswd.cc
../bin/purgeplay : util/purgeplay.cc structs.hpp
	$(CXX) $(CPPFLAGS) -o ../bin/purgeplay util/purgeplay.cc
../bin/showplay : util/showplay.cc structs.hpp
	$(CXX) $(CPPFLAGS) -o ../bin/showplay util/showplay.cc
../bin/sign: util/sign.cc
	$(CXX) $(CPPFLAGS) -o ../bin/sign $(COMMFLAGS) util/sign.cc
../bin/split: util/split.cc
	$(CXX) $(CPPFLAGS) -o ../bin/split util/split.cc
../bin/plrtoascii: util/plrtoascii.cc db.hpp utils.hpp structs.hpp
	$(CXX) $(CPPFLAGS) -o ../bin/plrtoascii util/plrtoascii.cc

../bin/convmob: util/convmob.cpp constants.cpp bitfield.cpp
	$(CXX) $(CPPFLAGS) -o ../bin/convmob util/convmob.cpp constants.cpp bitfield.cpp assert.cpp
../bin/convobj: util/convobj.cpp constants.cpp bitfield.cpp
	$(CXX) $(CPPFLAGS) -o ../bin/convobj util/convobj.cpp constants.cpp bitfield.cpp assert.cpp
../bin/convwld: util/convwld.cpp constants.cpp bitfield.cpp
	$(CXX) $(CPPFLAGS) -o ../bin/convwld util/convwld.cpp constants.cpp bitfield.cpp assert.cpp

clean:
	rm -f *.o ../test/*.o *.d ../bin/awake.new

%.d: %.cpp
	set -e; $(CC) -MM $(CPPFLAGS) $< \
		| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
		[ -s $@ ] || rm -f $@


../bin/awake.new :
	touch ../bin/awake
	rm ../bin/awake
	$(CXX) -o ../bin/awake $(PROFILE) $(objfiles) $(LIBS)

recompile:
	$(MAKE) clean
	$(MAKE) depend
	$(MAKE) ../bin/awake.new

depend : $(wildcard *.d)

update:
	$(CVS) update

all:
	$(MAKE) ../bin/awake.new

unittest_srcs = $(wildcard ../test/*.cpp)
unittest_objs = $(unittest_srcs:.cpp=.o) $(objfiles)

unittest: ../bin/unittest
	../bin/unittest

../bin/unittest: CPPFLAGS+=-DUNITTEST
../bin/unittest: $(unittest_objs)
	$(CXX) -o $@ $(PROFILE) $(unittest_objs) $(LIBS)

../test/%.o: ../test/%.cpp
	$(CXX) -c $(CPPFLAGS) -I../3rdparty/catch2 -o $@ $<


include $(sourcefiles:.cpp=.d)
