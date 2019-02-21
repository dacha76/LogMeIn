.PHONY: clean All

All:
	@echo "----------Building project:[ aorServerTest - Debug ]----------"
	@cd "aorClient" && "$(MAKE)" -f  "aorServerTest.mk"
clean:
	@echo "----------Cleaning project:[ aorServerTest - Debug ]----------"
	@cd "aorClient" && "$(MAKE)" -f  "aorServerTest.mk" clean
