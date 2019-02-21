.PHONY: clean All

All:
	@echo "----------Building project:[ aorServerTest - Release ]----------"
	@cd "aorServerTest" && "$(MAKE)" -f  "aorServerTest.mk"
clean:
	@echo "----------Cleaning project:[ aorServerTest - Release ]----------"
	@cd "aorServerTest" && "$(MAKE)" -f  "aorServerTest.mk" clean
