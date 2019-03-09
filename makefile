# Universal MakeFile v1.4
# Compatible with Code::blocks
include .makefiles/settings.mk

#Defauilt
all: prebuild directories resources | $(TARGET)
	@echo -e $(CEND)$(BULLET)$(CGREEN)$(BUILD) Compilation and linking done! $(CEND)

prebuild:
	@echo -e $(CYELLOW)Building $(THIS_DIR) "("$(BUILD)")"$(CEND) "\n"

#Rebuild
rebuild: prebuild clean | directories resources $(TARGET)
	@echo -e $(CEND)$(BULLET)$(CGREEN)$(BUILD) Clean, Compilation and linking done! $(CEND)

#Copy Resources from Resources Directory to Target Directory
resources:
	@echo -e $(BULLET)$(CBLUE)Copying resources $(CEND)
	@rescopy $(BUILD)

#Make the directories
directories:
	@echo -e $(BULLET)$(CBLUE)Checking build directories $(CEND)
	@$(MD) -p $(TARGETDIR)
	@$(MD) -p $(BUILDDIR)

#Clean only Objecst
clean:
	@echo -e $(BULLET)$(CBLUE)Cleaning build $(CEND)
	@$(RM) -rf obj/*
	@$(RM) -rf bin/*

compilation:
	@echo -e $(BULLET)$(CBLUE)Compilation $(CEND)$(CGREY)
	@$(MAKE) -f .makefiles/compile.mk --silent -j 8 -Oline

run: all
	@echo -e $(BULLET)$(CYELLOW)Running $(TARGET) $(CEND)
	@cd $(TARGETDIR) && ./$(TARGET)

debug: all
	@echo -e $(BULLET)$(CYELLOW)Running Debug of $(TARGET) $(CEND)
	@cd $(TARGETDIR) && $(DB) $(TARGET)

#Link
$(TARGET): compilation
	@echo -e $(CEND)$(BULLET)$(CBLUE)Linking $(TARGET) $(CEND)
	@$(CC) $(LNKFLAGS) -o $(TARGETDIR)/$(TARGET) $(OBJECTS) $(LIBDIRS) $(LIB)

#Non-File Targets
.PHONY: all prebuild release rebuild clean resources directories run debug

.NOTPARALLEL: all

# include dependency files (*.d) if available
-include $(DEPENDS)
