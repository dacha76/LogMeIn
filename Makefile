.PHONY: clean All

All:
	@echo "----------Building project:[ aorServer - Debug ]----------"
	@cd "aorServer" && "$(MAKE)" -f  "aorServer.mk"
clean:
	@echo "----------Cleaning project:[ aorServer - Debug ]----------"
	@cd "aorServer" && "$(MAKE)" -f  "aorServer.mk" clean
