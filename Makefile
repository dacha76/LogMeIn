.PHONY: clean All

All:
	@echo "----------Building project:[ aorServerTest - Debug ]----------"
	@cd "aorServerTest" && "$(MAKE)" -f  "aorServerTest.mk"
clean:
	@echo "----------Cleaning project:[ aorServerTest - Debug ]----------"
	@cd "aorServerTest" && "$(MAKE)" -f  "aorServerTest.mk" clean
