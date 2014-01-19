all: init robot robot-test dev-test

.PHONY: all-clean doc

build/%:
	@(mkdir -p $@)

dist:
	@(mkdir dist)
	
init: build/common dist

robot: build/robot
	@(cd src/robot && make)

robot-test: build/robot-test
	@(cd src/robot-test && make)

dev-test: build/dev-test
	@(cd src/dev-test && make)

doc:
	rm -rf doc/*
	@doxygen doxy.cfg

format:
	@(cd src/common && make $@)
	@(cd src/robot && make $@)
	@(cd src/robot-test && make $@)
	@(cd src/dev-test && make $@)
	
clean:
	@(cd src/robot && make $@)
	@(cd src/robot-test && make $@)
	@(cd src/dev-test && make $@)

all-clean:
	@(cd src/robot && make $@)
	@(cd src/robot-test && make $@)
	@(cd src/dev-test && make $@)
