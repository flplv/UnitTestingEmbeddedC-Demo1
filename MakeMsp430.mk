ifeq (1,${V})
	SILENT =
else
	SILENT = @  
endif

PLATFORM = msp430
PROJECT = turma-piloto
MCU = msp430g2231

OBJDIR = objs/$(PLATFORM)

LIBS = 

SRCFILES =

SRCDIRS = \
	src_msp430 \
	src
	
INCLUDES = \
	-I src_msp430 \
	-I src
	
CFLAGS = -mmcu=$(MCU) -g -Os -Wall -Wunused $(INCLUDES)
ASFLAGS = -mmcu=$(MCU) -x assembler-with-cpp -Wa,-gstabs
LDFLAGS = -mmcu=$(MCU) -Wl,-Map=$(OBJDIR)/$(PROJECT).map

CC      	= msp430-gcc
LD      	= msp430-ld
AR      	= msp430-ar
AS      	= msp430-gcc
GASP    	= msp430-gasp
NM      	= msp430-nm
OBJCOPY 	= msp430-objcopy
MAKETXT 	= srec_cat
UNIX2DOS	= unix2dos
RM      	= rm -f

get_src_from_dir  = $(wildcard $1/*.cpp) $(wildcard $1/*.c)
get_dirs_from_dirspec  = $(wildcard $1)
get_src_from_dir_list = $(foreach dir, $1, $(call get_src_from_dir,$(dir)))
SRCS += $(call get_src_from_dir_list, $(SRCDIRS)) $(SRCFILES)	

__src_to = $(subst .c,$1, $(subst .cpp,$1,$2))
src_to = $(addprefix $(OBJDIR)/,$(call __src_to,$1,$2))
src_to_o = $(call src_to,.o,$1)
OBJS = $(call src_to_o,$(SRCS))

HEX = $(PROJECT)_$(PLATFORM).hex
ELF = $(PROJECT)_$(PLATFORM).elf

all: buildrepo printversions $(HEX)

$(ELF): $(OBJS)
	@echo
	@echo Linking $(notdir $@)
	$(SILENT)$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $@

$(OBJDIR)/%.o: %.cpp
	@echo Compiling $(notdir $<)
	$(SILENT)$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJDIR)/%.o: %.c
	@echo Compiling $(notdir $<)
	$(SILENT)$(CC) $(CFLAGS) -c $< -o $@

$(HEX): $(ELF)
	@echo Copying $(notdir $@)
	$(SILENT)$(OBJCOPY) -O ihex $< $@
	
deploy: $(ELF)
	@echo Deploying $(notdir $<)
	$(SILENT)echo "prog $<" | mspdebug rf2500
	
clean:
	$(RM) -R $(HEX) $(ELF) $(OBJDIR)

printversions:
	@echo SRC DIRS:
	@echo $(SRCDIRS)
	@echo SOURCES:
	@echo $(SRCS)
	@echo OBJECTS:
	@echo $(OBJS)
	@echo

buildrepo:
	@$(call make-repo)

# Create obj directory structure
define make-repo
	mkdir -p $(OBJDIR)
	for dir in $(SRCDIRS); \
	do \
		mkdir -p $(OBJDIR)/$$dir; \
	done
endef