MAKEFLAGS:=--silent

BUILD_DIR:=$(CURDIR)/bld
SOURCE_DIR:=$(CURDIR)/src

all: clean build test

.PHONY: clean
.PHONY: build
.PHONY: test

clean:
	rm -rf $(BUILD_DIR)

$(BUILD_DIR)/Makefile:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake \
       -G "Unix Makefiles" \
       $(SOURCE_DIR)

build: $(BUILD_DIR)/Makefile
	$(MAKE) -C $(BUILD_DIR)

test: build
	$(MAKE) -C $(BUILD_DIR) test