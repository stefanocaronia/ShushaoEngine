# Universal MakeFile v1.5
# Compatible with Code::blocks
include .makefiles/settings.mk

# Defauilt
ifeq ($(PRECOMPILED_HEADERS),true)
all: prebuild directories resources precomp | $(TARGET)
	@echo -e $(CEND)$(CGREEN)$(BULLET)$(BUILD) Linking done! $(CEND)
else
all: prebuild directories resources | $(TARGET)
	@echo -e $(CEND)$(CGREEN)$(BULLET)$(BUILD) Linking done! $(CEND)
endif

prebuild:
	@echo -e $(CYELLOW)Building $(THIS_DIR) "["$(BUILD)"]" - $(N_SOURCES) sources$(CEND) "\n"

# Rebuild
rebuild: prebuild clean | directories resources precomp $(TARGET)
	@echo -e $(CEND)$(CGREEN)$(BULLET)$(BUILD) Clean, Compilation and linking done! $(CEND)

# Copy Resources from Resources Directory to Target Directory
resources:
	@echo -e $(CLBLUE)$(BULLET)Syncing resources $(CEND)
#@rescopy $(BUILD)
	@rsync $(RESDIR)/ $(TARGETDIR) -az --delete --prune-empty-dirs

# Make the directories
directories:
	@echo -e $(CLBLUE)$(BULLET)Checking build directories $(CEND)
	@$(MD) -p $(TARGETDIR)
	@$(MD) -p $(BUILDDIR)
	@if $(COPY_INCLUDE_HEADERS); then $(MD) -p $(HEADERSDIR); fi
	@if $(COMPILE_STATIC_LIB); then $(MD) -p $(TARGETLIBDIR); fi
	@$(RM) -f obj/$(BUILD)/$(ENGINE_RESFILE)
	@$(RM) -f obj/$(BUILD)/$(GAME_RESFILE)
	@if $(COPY_INCLUDE_HEADERS); then echo -e $(CLBLUE)$(BULLET)Copying headers $(CEND) && \
	rsync $(SRCDIR)/$(ENGINE)/ $(HEADERSDIR) -az --delete --filter='+ **/*.h' --filter='- **/*.*' --prune-empty-dirs; fi

#Clean only Objecst
clean:
	@echo -e $(CLBLUE)$(BULLET)Cleaning build $(CEND)
	@$(RM) -rf obj/*
	@$(RM) -rf bin/*
	@$(RM) -rf $(HEADERSDIR)/*
	@$(RM) -rf $(TARGETLIBDIR)/*
	@$(RM) -f $(PRECOMPILEDDIR)/*.gch
	@$(RM) -f $(PRECOMPILEDDIR)/*.d

test:
	@echo "SOURCES: " $(SOURCES)
	@echo "RCSOURCES: " $(RCSOURCES)
	@echo "OBJECTS: " $(OBJECTS)
	@echo "RCFILES: " $(RCFILES)
	@echo "TOPRECOMP: " $(TOPRECOMP)
	@echo "DEPENDS: " $(DEPENDS)

single:
# -H
	@$(MD) -p $(dir $(SINGLEOBJ))
	@echo -e $(CLCYAN)$(BULLET)Compiling: $(subst ./,'',$(SINGLEFILE)) -\> $(SINGLEOBJ) $(CEND)$(CLCYAN)
	@$(CC) $(COMFLAGS) $(INCDIRS) -c $(SINGLEFILE) -o $(SINGLEOBJ)
	@echo -e $(CLCYAN)$(BULLET)Compiling assembly: $(subst ./,'',$(SINGLEFILE)) -\> $(SINGLEASSEMBLY) $(CEND)$(CLCYAN)
	@$(CC) $(COMFLAGS) -S $(INCDIRS) -c $(SINGLEFILE) -o $(SINGLEASSEMBLY)
	@echo -e $(CGREEN)$(BULLET)Compilation done $(CEND)$(CLCYAN)

precompstart:
	@echo -e $(CLBLUE)$(BULLET)Precompiling headers $(CEND)$(CLCYAN)

compileresources:
	@echo -e $(CLBLUE)$(BULLET)Compiling resources $(CEND)$(CLCYAN)
	@$(MD) -p obj/$(BUILD)/engine/resources
	@echo -e $(TAB)$(BULLET2)$(ENGINE_RCFILE) -\> obj/$(BUILD)/$(ENGINE_RESFILE)
	@$(RC) $(ENGINE_RCFILE) -o obj/$(BUILD)/$(ENGINE_RESFILE) --output-format=coff

precomp: precompstart $(PRECOMP)
#@echo -e $(CLPURPLE)$(BULLET)Precompiling headers done $(CEND)

# Pre-compiled headers
$(PRECOMPILEDDIR)/%.$(GCHEXT): $(SRCDIR)/$(ENGINE)/$(GCHDIR)/%.h
	@echo -e $(TAB)$(BULLET2)$< -\> $@
	@$(MD) -p $(dir $@)
	@$(CC) $(GCHFLAGS) $(INCDIRS) -c $< -o $@

compilation:
	@echo -e $(CLBLUE)$(BULLET)Compiling sources$(CEND)$(CLCYAN)
	@$(MAKE) -f .makefiles/compile.mk --silent -j $(CORES) -Oline -l 80.0
#@echo -e $(CLPURPLE)$(BULLET)Compiling done$(CEND)

run: all
	@echo -e $(CYELLOW)$(BULLET)Running $(TARGET) $(CEND)
	@cd $(TARGETDIR) && ./$(TARGET)

debug: all
	@echo -e $(CYELLOW)$(BULLET)Running Debug of $(TARGET) $(CEND)
	@cd $(TARGETDIR) && $(DB) $(TARGET)


#Compile rc files
$(BUILDDIR)/%.$(RESEXT): $(SRCDIR)/%.$(RCEXT)
	@echo -e $(TAB)$(BULLET2)$< -\> $@
	@$(MD) -p $(dir $@)
	@$(RC) $< -o $@ --output-format=coff

# Link
$(TARGET): compilation compileresources $(RCFILES)
	@echo -e $(CEND)$(CLBLUE)$(BULLET)Creating resources library $(LIBTARGET) $(CEND)
	@$(CC) $(SHAREDFLAGS) -o $(TARGETDIR)/$(LIBTARGET) obj/$(BUILD)/$(ENGINE_RESFILE)
	@if $(COMPILE_STATIC_LIB); then $(CP) $(TARGETDIR)/$(LIBTARGET) $(TARGETLIBDIR)/; fi
	@if $(COMPILE_STATIC_LIB); then echo -e $(CEND)$(CLBLUE)$(BULLET)Creating static lib $(STATICLIB) $(CEND) && \
	$(AR) $(ARFLAGS) $(TARGETLIBDIR)/$(STATICLIB) $(ENGINEOBJECTS); fi
	@echo -e $(CEND)$(CLBLUE)$(BULLET)Linking executable $(TARGET) $(CEND)
	@$(CC) $(LNKFLAGS) -o $(TARGETDIR)/$(TARGET) $(OBJECTS) $(RCFILES) $(LIBDIRS) $(LIB)

# Non-File Targets
.PHONY: all prebuild release rebuild clean resources directories run debug test single precomp precompstart compileresources

.NOTPARALLEL: all
