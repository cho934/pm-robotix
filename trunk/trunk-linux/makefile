# Define the default target that build everything
all: init dev-test unit-test robot-test pmx 

# Define the targets that should not have dependency check
.PHONY: all-clean clean doc

build/%:
	@(mkdir -p $@)

PMXArmadeusBinaries:
	@(mkdir PMXArmadeusBinaries)

init: build/common PMXArmadeusBinaries

# Build the main application
pmx: build/pmx-match-main
	@(cd src/pmx-match-main && make)

# Build the functional tests package
robot-test: build/robot-test
	@(cd src/robot-test && make)
	
# Build the unit tests package
unit-test: build/unit-test
	@(cd src/unit-test && make)

# Build the unit tests package
dev-test: build/dev-test
	@(cd src/dev-test && make)

# Generate the documentation
doc:
	rm -rf doc/*
	@doxygen doxy.cfg

# Format the code
format:
	@(cd src/common && make $@)
	@(cd src/pmx-match-main && make $@)
	@(cd src/robot-test && make $@)
	@(cd src/unit-test && make $@)
	@(cd src/dev-test && make $@)

# Clean all the intermediate files of the sub-projects
clean:
	@(cd src/pmx-match-main && make $@)
	@(cd src/robot-test && make $@)
	@(cd src/unit-test && make $@)
	@(cd src/dev-test && make $@)

# Clean all the sub-projects even last successful build results
all-clean:
	@(cd src/pmx-match-main && make $@)
	@(cd src/robot-test && make $@)
	@(cd src/unit-test && make $@)
	@(cd src/dev-test && make $@)
