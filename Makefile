#
# Makefile for CSE 30 -- PA3
# You should not need to change anything in this file.
#
# XXX DO NOT EDIT
#

HEADERS		= pa3.h pa3Strings.h
TEST_HEADERS	= $(HEADERS) test.h
C_SRCS		= pa3.c pa3Globals.c addWordCount.c buildWordTable.c \
		  buildPlot.c findCommand.c printPlot.c printData.c \
		  printTable.c interactiveLoop.c shouldPrompt.c
ASM_SRCS	= computeHash.s myURem.s findSlotIndex.s compareWordData.s \
		  createWordData.s intervalContains.s

# REG = only used in regular program; EC = only used in EC program.
REG_C_SRCS	= # N/A
EC_C_SRCS	= # N/A
REG_ASM_SRCS	= # N/A
EC_ASM_SRCS	= # N/A

C_OBJS		= $(C_SRCS:.c=.o)
ASM_OBJS	= $(ASM_SRCS:.s=.o)
REG_C_OBJS	= $(REG_C_SRCS:.c=.o)
EC_C_OBJS	= $(EC_C_SRCS:.c=.o)
REG_ASM_OBJS	= $(REG_ASM_SRCS:.s=.o)
EC_ASM_OBJS	= $(EC_ASM_SRCS:.s=.o)
OBJS		= $(C_OBJS) $(ASM_OBJS) $(REG_C_OBJS) $(REG_ASM_OBJS)
EC_OBJS		= $(C_OBJS) $(ASM_OBJS) $(EC_C_OBJS) $(EC_ASM_OBJS)

EXE		= pa3
EC_EXE		= # N/A
TEST_EXES	= testcomputeHash testmyURem testfindSlotIndex \
		  testcompareWordData testprintData testcreateWordData \
		  testbuildPlot testprintPlot testbuildWordTable \
		  testaddWordCount

GCC		= gcc
ASM		= $(GCC)
RM		= rm

DEBUG_FLAGS	= -g
GCC_FLAGS	= -c $(DEBUG_FLAGS) -std=c99 -pedantic -Wall -D__EXTENSIONS__
ASM_FLAGS	= -c $(DEBUG_FLAGS)
LD_FLAGS	= $(DEBUG_FLAGS) -Wall

OPT_FLAGS	= -O3 -fstack-protector-all
OPT_GCC_FLAGS	= $(subst $(DEBUG_FLAGS),$(OPT_FLAGS),$(GCC_FLAGS))
OPT_ASM_FLAGS	= $(subst $(DEBUG_FLAGS),$(OPT_FLAGS),$(ASM_FLAGS))
OPT_LD_FLAGS	= $(subst $(DEBUG_FLAGS),$(OPT_FLAGS),$(LD_FLAGS))


#
# Standard rules
#

.s.o:
	@echo "Assembling each assembly source file separately ..."
	$(ASM) $(ASM_FLAGS) $<
	@echo ""

.c.o:
	@echo "Compiling each C source file separately ..."
	$(GCC) $(GCC_FLAGS) $<
	@echo ""

#
# Simply have our project target be a single default $(EXE) executable.
#

$(EXE):	$(OBJS)
	@echo "Linking all object modules ..."
	$(GCC) $(LD_FLAGS) -o $(EXE) $(OBJS)
	@echo ""
	@echo "Compilation Successful!"

$(EC_EXE): $(EC_OBJS)
	@echo "Linking all object modules ..."
	$(GCC) $(LD_FLAGS) -o $(EC_EXE) $(EC_OBJS)
	@echo ""
	@echo "Compilation Successful!"

$(C_OBJS) $(REG_C_OBJS) $(EC_C_OBJS): $(HEADERS)


clean:
	@echo "Cleaning up project directory ..."
	$(RM) -f *.o $(EXE) $(EC_EXE) core a.out $(TEST_EXES) *$(OPT_EXT)
	@echo ""
	@echo "Clean."

#
# Unit test targets
#

# Dependencies that are common across all files
commonDeps = printTable.o

# List dependencies for tester executable in variable suffixed with "Deps"
testcomputeHashDeps = testcomputeHash.o computeHash.o pa3Globals.o
testmyURemDeps = testmyURem.o myURem.o
testfindSlotIndexDeps = testfindSlotIndex.o findSlotIndex.o computeHash.o \
			myURem.o pa3Globals.o
testcompareWordDataDeps = testcompareWordData.o compareWordData.o pa3Globals.o
testprintDataDeps = testprintData.o printData.o
testcreateWordDataDeps = testcreateWordData.o createWordData.o computeHash.o \
			 pa3Globals.o
testbuildPlotDeps = testbuildPlot.o buildPlot.o
testprintPlotDeps = testprintPlot.o printPlot.o buildPlot.o
testbuildWordTableDeps = testbuildWordTable.o buildWordTable.o \
			 createWordData.o compareWordData.o findSlotIndex.o \
			 myURem.o computeHash.o addWordCount.o pa3Globals.o
testaddWordCountDeps = testaddWordCount.o addWordCount.o createWordData.o \
		       compareWordData.o computeHash.o pa3Globals.o

OPT_EXT = -opt

# Optimized object file rules.
%$(OPT_EXT).o: %.s
	@echo "Assembling each assembly source file separately ..."
	$(ASM) $(OPT_ASM_FLAGS) -o $(<:.s=$(OPT_EXT).o) $<
	@echo ""

%$(OPT_EXT).o: %.c
	@echo "Compiling each C source file separately ..."
	$(GCC) $(OPT_GCC_FLAGS) -o $(<:.c=$(OPT_EXT).o) $<
	@echo ""

# Rules for compiling tester toplevels.
$(TEST_EXES): $(TEST_HEADERS)
	@echo "Compiling $@ ..."
	$(GCC) $(LD_FLAGS) -o $@ $(filter %.o, $^)
	@echo "Compilation Successful!"

TEST_OPT_EXES = $(TEST_EXES:=$(OPT_EXT))
$(TEST_OPT_EXES): $(TEST_HEADERS)
	@echo "Compiling $@ ..."
	$(GCC) $(OPT_LD_FLAGS) -o $@ $(filter %.o, $^)
	@echo "Compilation Successful!"

# Lay out dependencies for each test file (regular and optimized).
define testRule
# Regular dependencies.
$(1): $$($(1)Deps) $$(commonDeps)
# Optimized dependencies.
$(1)$$(OPT_EXT): $$($(1)Deps:.o=$$(OPT_EXT).o) $$(commonDeps:.o=$$(OPT_EXT).o)
endef

# This calls the above function on each test file target, generating rules
# for each tester file's regular and optimized executables.
$(foreach test,$(TEST_EXES),$(eval $(call testRule,$(test))))

new:
	make clean
	make
