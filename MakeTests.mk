## Silence switch ##
# run `make V=1` to make it verbose.
ifeq (1,${V})
    SILENCE =
else
    SILENCE = @  
endif

## CppUTest configurations ##
# Read header comment on file `$(CPPUTEST_HOME)/build/MakefileWorker.mk` to understand these definitions.

COMPONENT_NAME = turma-piloto
CPPUTEST_HOME = cpputest

CPPUTEST_ENABLE_DEBUG = Y
CPPUTEST_USE_EXTENSIONS = Y
CPP_PLATFORM = Gcc
CPPUTEST_USE_GCOV = Y
CPPUTEST_OBJS_DIR = objs/tests
CPPUTEST_LIB_DIR = lib/tests

SRC_DIRS = \
    src

TEST_SRC_DIRS = \
    src_tests

INCLUDE_DIRS =\
    src \
    $(CPPUTEST_HOME)/include\

CPPUTEST_CPPFLAGS = -DDISABLE_LOG -DTEST_BUILD
CPPUTEST_CXXFLAGS = -std=c++14 -O0
CPPUTEST_LDFLAGS = -pthread
CPPUTEST_WARNINGFLAGS = -Wall -Wextra -Wshadow -Wswitch-default -Wswitch-enum -Wconversion -Wno-long-long

## The real work ##
# including this file that will use configuration and have the make rules.
include $(CPPUTEST_HOME)/build/MakefileWorker.mk

# Coverage Report rules #
coverage: all
	$(SILENCE)lcov --capture --directory objs/tests/src --output-file coverage.info
	$(SILANCE)genhtml coverage.info --output-directory coverage
	@echo
	@echo "Written coverage report to coverage/index.html"
	@echo
	
coverage_clean:
	rm -rf coverage coverage.info
