DIST_DIR := ./dist
SRC_DIRS := ./src
DATA_DIRS := $(SRC_DIRS)/data

SRCS := $(shell find $(SRC_DIRS)  -name '*.c')

$(DIST_DIR)/executable:
	mkdir -p $(dir $@)
	cp -r $(DATA_DIRS) $(DIST_DIR)
	gcc -o $@ $(SRCS)

clean:
	rm -r $(DIST_DIR)
