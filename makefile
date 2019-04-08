# Universal MakeFile v1.4
# Compatible with Code::blocks
include .makefiles/settings.mk

#Defauilt
all: prebuild directories resources | $(TARGET)
	@echo -e $(CEND)$(CGREEN)$(BULLET)$(BUILD) Compilation and linking done! $(CEND)

prebuild:
	@echo -e $(CYELLOW)Building $(THIS_DIR) "("$(BUILD)")"$(CEND) "\n"

#Rebuild
rebuild: prebuild clean | directories resources $(TARGET)
	@echo -e $(CEND)$(CGREEN)$(BULLET)$(BUILD) Clean, Compilation and linking done! $(CEND)

#Copy Resources from Resources Directory to Target Directory
resources:
	@echo -e $(CLBLUE)$(BULLET)Syncing resources $(CEND)
#@rescopy $(BUILD)
	@rsync $(RESDIR)/ $(TARGETDIR) -az --delete --prune-empty-dirs

#Make the directories
directories:
	@echo -e $(CLBLUE)$(BULLET)Checking build directories $(CEND)
	@$(MD) -p $(TARGETDIR)
	@$(MD) -p $(BUILDDIR)
	@$(RM) -f obj/$(BUILD)/$(ENGINE_RESFILE)
	@$(RM) -f obj/$(BUILD)/$(GAME_RESFILE)

#Clean only Objecst
clean:
	@echo -e $(CLBLUE)$(BULLET)Cleaning build $(CEND)
	@$(RM) -rf obj/*
	@$(RM) -rf bin/*

test:
	@echo "SOURCES: " $(SOURCES)
	@echo "RCSOURCES: " $(RCSOURCES)
	@echo "OBJECTS: " $(OBJECTS)
	@echo "RCFILES: " $(RCFILES)

compilation:
	@echo -e $(CLBLUE)$(BULLET)Compilation $(CEND)$(CLCYAN)
	@$(MAKE) -f .makefiles/compile.mk --silent -j $(CORES) -Oline -l 80.0

run: all
	@echo -e $(CYELLOW)$(BULLET)Running $(TARGET) $(CEND)
	@cd $(TARGETDIR) && ./$(TARGET)

debug: all
	@echo -e $(CYELLOW)$(BULLET)Running Debug of $(TARGET) $(CEND)
	@cd $(TARGETDIR) && $(DB) $(TARGET)

#Link
$(TARGET): compilation
	@echo -e $(CEND)$(CLBLUE)$(BULLET)Creating library $(LIBTARGET) $(CEND)
	@$(CC) $(SHAREDFLAGS) -o $(TARGETDIR)/$(LIBTARGET) obj/$(BUILD)/$(ENGINE_RESFILE)
	@echo -e $(CEND)$(CLBLUE)$(BULLET)Linking executable $(TARGET) $(CEND)
	@$(CC) $(LNKFLAGS) -o $(TARGETDIR)/$(TARGET) $(OBJECTS) $(RCFILES) $(LIBDIRS) $(LIB)

#Non-File Targets
.PHONY: all prebuild release rebuild clean resources directories run debug test

.NOTPARALLEL: all

# include dependency files (*.d) if available
-include $(DEPENDS)
