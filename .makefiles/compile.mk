# Universal MakeFile v1.4
# Compatible with Code::blocks
include .makefiles/settings.mk

#Defauilt
all: $(OBJECTS) $(RCFILES)
	@$(MD) -p obj/$(BUILD)/engine/resources
	@$(RC) $(ENGINE_RCFILE) -o obj/$(BUILD)/$(ENGINE_RESFILE)

#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@echo -e $(TAB)$(BULLET2)$<
	@$(MD) -p $(dir $@)
	@$(CC) $(COMFLAGS) $(INCDIRS) -c $< -o $@

#Compile rc files
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(RCEXT)
	@echo -e $(TAB)$(BULLET2)$<
	@$(MD) -p $(dir $@)
	@$(RC) $< -o $@

#Non-File Targets
.PHONY: all

# include dependency files (*.d) if available
-include $(DEPENDS)