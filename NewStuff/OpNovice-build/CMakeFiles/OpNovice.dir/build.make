# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.1

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice-build

# Include any dependencies generated for this target.
include CMakeFiles/OpNovice.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/OpNovice.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OpNovice.dir/flags.make

CMakeFiles/OpNovice.dir/OpNovice.cc.o: CMakeFiles/OpNovice.dir/flags.make
CMakeFiles/OpNovice.dir/OpNovice.cc.o: /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/OpNovice.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice-build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/OpNovice.dir/OpNovice.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OpNovice.dir/OpNovice.cc.o -c /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/OpNovice.cc

CMakeFiles/OpNovice.dir/OpNovice.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpNovice.dir/OpNovice.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/OpNovice.cc > CMakeFiles/OpNovice.dir/OpNovice.cc.i

CMakeFiles/OpNovice.dir/OpNovice.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpNovice.dir/OpNovice.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/OpNovice.cc -o CMakeFiles/OpNovice.dir/OpNovice.cc.s

CMakeFiles/OpNovice.dir/OpNovice.cc.o.requires:
.PHONY : CMakeFiles/OpNovice.dir/OpNovice.cc.o.requires

CMakeFiles/OpNovice.dir/OpNovice.cc.o.provides: CMakeFiles/OpNovice.dir/OpNovice.cc.o.requires
	$(MAKE) -f CMakeFiles/OpNovice.dir/build.make CMakeFiles/OpNovice.dir/OpNovice.cc.o.provides.build
.PHONY : CMakeFiles/OpNovice.dir/OpNovice.cc.o.provides

CMakeFiles/OpNovice.dir/OpNovice.cc.o.provides.build: CMakeFiles/OpNovice.dir/OpNovice.cc.o

CMakeFiles/OpNovice.dir/src/OpNoviceActionInitialization.cc.o: CMakeFiles/OpNovice.dir/flags.make
CMakeFiles/OpNovice.dir/src/OpNoviceActionInitialization.cc.o: /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNoviceActionInitialization.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice-build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/OpNovice.dir/src/OpNoviceActionInitialization.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OpNovice.dir/src/OpNoviceActionInitialization.cc.o -c /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNoviceActionInitialization.cc

CMakeFiles/OpNovice.dir/src/OpNoviceActionInitialization.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpNovice.dir/src/OpNoviceActionInitialization.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNoviceActionInitialization.cc > CMakeFiles/OpNovice.dir/src/OpNoviceActionInitialization.cc.i

CMakeFiles/OpNovice.dir/src/OpNoviceActionInitialization.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpNovice.dir/src/OpNoviceActionInitialization.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNoviceActionInitialization.cc -o CMakeFiles/OpNovice.dir/src/OpNoviceActionInitialization.cc.s

CMakeFiles/OpNovice.dir/src/OpNoviceActionInitialization.cc.o.requires:
.PHONY : CMakeFiles/OpNovice.dir/src/OpNoviceActionInitialization.cc.o.requires

CMakeFiles/OpNovice.dir/src/OpNoviceActionInitialization.cc.o.provides: CMakeFiles/OpNovice.dir/src/OpNoviceActionInitialization.cc.o.requires
	$(MAKE) -f CMakeFiles/OpNovice.dir/build.make CMakeFiles/OpNovice.dir/src/OpNoviceActionInitialization.cc.o.provides.build
.PHONY : CMakeFiles/OpNovice.dir/src/OpNoviceActionInitialization.cc.o.provides

CMakeFiles/OpNovice.dir/src/OpNoviceActionInitialization.cc.o.provides.build: CMakeFiles/OpNovice.dir/src/OpNoviceActionInitialization.cc.o

CMakeFiles/OpNovice.dir/src/OpNoviceDetectorConstruction.cc.o: CMakeFiles/OpNovice.dir/flags.make
CMakeFiles/OpNovice.dir/src/OpNoviceDetectorConstruction.cc.o: /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNoviceDetectorConstruction.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice-build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/OpNovice.dir/src/OpNoviceDetectorConstruction.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OpNovice.dir/src/OpNoviceDetectorConstruction.cc.o -c /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNoviceDetectorConstruction.cc

CMakeFiles/OpNovice.dir/src/OpNoviceDetectorConstruction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpNovice.dir/src/OpNoviceDetectorConstruction.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNoviceDetectorConstruction.cc > CMakeFiles/OpNovice.dir/src/OpNoviceDetectorConstruction.cc.i

CMakeFiles/OpNovice.dir/src/OpNoviceDetectorConstruction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpNovice.dir/src/OpNoviceDetectorConstruction.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNoviceDetectorConstruction.cc -o CMakeFiles/OpNovice.dir/src/OpNoviceDetectorConstruction.cc.s

CMakeFiles/OpNovice.dir/src/OpNoviceDetectorConstruction.cc.o.requires:
.PHONY : CMakeFiles/OpNovice.dir/src/OpNoviceDetectorConstruction.cc.o.requires

CMakeFiles/OpNovice.dir/src/OpNoviceDetectorConstruction.cc.o.provides: CMakeFiles/OpNovice.dir/src/OpNoviceDetectorConstruction.cc.o.requires
	$(MAKE) -f CMakeFiles/OpNovice.dir/build.make CMakeFiles/OpNovice.dir/src/OpNoviceDetectorConstruction.cc.o.provides.build
.PHONY : CMakeFiles/OpNovice.dir/src/OpNoviceDetectorConstruction.cc.o.provides

CMakeFiles/OpNovice.dir/src/OpNoviceDetectorConstruction.cc.o.provides.build: CMakeFiles/OpNovice.dir/src/OpNoviceDetectorConstruction.cc.o

CMakeFiles/OpNovice.dir/src/OpNovicePhysicsList.cc.o: CMakeFiles/OpNovice.dir/flags.make
CMakeFiles/OpNovice.dir/src/OpNovicePhysicsList.cc.o: /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNovicePhysicsList.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice-build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/OpNovice.dir/src/OpNovicePhysicsList.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OpNovice.dir/src/OpNovicePhysicsList.cc.o -c /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNovicePhysicsList.cc

CMakeFiles/OpNovice.dir/src/OpNovicePhysicsList.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpNovice.dir/src/OpNovicePhysicsList.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNovicePhysicsList.cc > CMakeFiles/OpNovice.dir/src/OpNovicePhysicsList.cc.i

CMakeFiles/OpNovice.dir/src/OpNovicePhysicsList.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpNovice.dir/src/OpNovicePhysicsList.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNovicePhysicsList.cc -o CMakeFiles/OpNovice.dir/src/OpNovicePhysicsList.cc.s

CMakeFiles/OpNovice.dir/src/OpNovicePhysicsList.cc.o.requires:
.PHONY : CMakeFiles/OpNovice.dir/src/OpNovicePhysicsList.cc.o.requires

CMakeFiles/OpNovice.dir/src/OpNovicePhysicsList.cc.o.provides: CMakeFiles/OpNovice.dir/src/OpNovicePhysicsList.cc.o.requires
	$(MAKE) -f CMakeFiles/OpNovice.dir/build.make CMakeFiles/OpNovice.dir/src/OpNovicePhysicsList.cc.o.provides.build
.PHONY : CMakeFiles/OpNovice.dir/src/OpNovicePhysicsList.cc.o.provides

CMakeFiles/OpNovice.dir/src/OpNovicePhysicsList.cc.o.provides.build: CMakeFiles/OpNovice.dir/src/OpNovicePhysicsList.cc.o

CMakeFiles/OpNovice.dir/src/OpNovicePhysicsListMessenger.cc.o: CMakeFiles/OpNovice.dir/flags.make
CMakeFiles/OpNovice.dir/src/OpNovicePhysicsListMessenger.cc.o: /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNovicePhysicsListMessenger.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice-build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/OpNovice.dir/src/OpNovicePhysicsListMessenger.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OpNovice.dir/src/OpNovicePhysicsListMessenger.cc.o -c /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNovicePhysicsListMessenger.cc

CMakeFiles/OpNovice.dir/src/OpNovicePhysicsListMessenger.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpNovice.dir/src/OpNovicePhysicsListMessenger.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNovicePhysicsListMessenger.cc > CMakeFiles/OpNovice.dir/src/OpNovicePhysicsListMessenger.cc.i

CMakeFiles/OpNovice.dir/src/OpNovicePhysicsListMessenger.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpNovice.dir/src/OpNovicePhysicsListMessenger.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNovicePhysicsListMessenger.cc -o CMakeFiles/OpNovice.dir/src/OpNovicePhysicsListMessenger.cc.s

CMakeFiles/OpNovice.dir/src/OpNovicePhysicsListMessenger.cc.o.requires:
.PHONY : CMakeFiles/OpNovice.dir/src/OpNovicePhysicsListMessenger.cc.o.requires

CMakeFiles/OpNovice.dir/src/OpNovicePhysicsListMessenger.cc.o.provides: CMakeFiles/OpNovice.dir/src/OpNovicePhysicsListMessenger.cc.o.requires
	$(MAKE) -f CMakeFiles/OpNovice.dir/build.make CMakeFiles/OpNovice.dir/src/OpNovicePhysicsListMessenger.cc.o.provides.build
.PHONY : CMakeFiles/OpNovice.dir/src/OpNovicePhysicsListMessenger.cc.o.provides

CMakeFiles/OpNovice.dir/src/OpNovicePhysicsListMessenger.cc.o.provides.build: CMakeFiles/OpNovice.dir/src/OpNovicePhysicsListMessenger.cc.o

CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorAction.cc.o: CMakeFiles/OpNovice.dir/flags.make
CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorAction.cc.o: /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNovicePrimaryGeneratorAction.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice-build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorAction.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorAction.cc.o -c /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNovicePrimaryGeneratorAction.cc

CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorAction.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNovicePrimaryGeneratorAction.cc > CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorAction.cc.i

CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorAction.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNovicePrimaryGeneratorAction.cc -o CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorAction.cc.s

CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorAction.cc.o.requires:
.PHONY : CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorAction.cc.o.requires

CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorAction.cc.o.provides: CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorAction.cc.o.requires
	$(MAKE) -f CMakeFiles/OpNovice.dir/build.make CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorAction.cc.o.provides.build
.PHONY : CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorAction.cc.o.provides

CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorAction.cc.o.provides.build: CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorAction.cc.o

CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorMessenger.cc.o: CMakeFiles/OpNovice.dir/flags.make
CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorMessenger.cc.o: /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNovicePrimaryGeneratorMessenger.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice-build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorMessenger.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorMessenger.cc.o -c /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNovicePrimaryGeneratorMessenger.cc

CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorMessenger.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorMessenger.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNovicePrimaryGeneratorMessenger.cc > CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorMessenger.cc.i

CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorMessenger.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorMessenger.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNovicePrimaryGeneratorMessenger.cc -o CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorMessenger.cc.s

CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorMessenger.cc.o.requires:
.PHONY : CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorMessenger.cc.o.requires

CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorMessenger.cc.o.provides: CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorMessenger.cc.o.requires
	$(MAKE) -f CMakeFiles/OpNovice.dir/build.make CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorMessenger.cc.o.provides.build
.PHONY : CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorMessenger.cc.o.provides

CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorMessenger.cc.o.provides.build: CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorMessenger.cc.o

CMakeFiles/OpNovice.dir/src/OpNoviceRunAction.cc.o: CMakeFiles/OpNovice.dir/flags.make
CMakeFiles/OpNovice.dir/src/OpNoviceRunAction.cc.o: /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNoviceRunAction.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice-build/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/OpNovice.dir/src/OpNoviceRunAction.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OpNovice.dir/src/OpNoviceRunAction.cc.o -c /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNoviceRunAction.cc

CMakeFiles/OpNovice.dir/src/OpNoviceRunAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpNovice.dir/src/OpNoviceRunAction.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNoviceRunAction.cc > CMakeFiles/OpNovice.dir/src/OpNoviceRunAction.cc.i

CMakeFiles/OpNovice.dir/src/OpNoviceRunAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpNovice.dir/src/OpNoviceRunAction.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNoviceRunAction.cc -o CMakeFiles/OpNovice.dir/src/OpNoviceRunAction.cc.s

CMakeFiles/OpNovice.dir/src/OpNoviceRunAction.cc.o.requires:
.PHONY : CMakeFiles/OpNovice.dir/src/OpNoviceRunAction.cc.o.requires

CMakeFiles/OpNovice.dir/src/OpNoviceRunAction.cc.o.provides: CMakeFiles/OpNovice.dir/src/OpNoviceRunAction.cc.o.requires
	$(MAKE) -f CMakeFiles/OpNovice.dir/build.make CMakeFiles/OpNovice.dir/src/OpNoviceRunAction.cc.o.provides.build
.PHONY : CMakeFiles/OpNovice.dir/src/OpNoviceRunAction.cc.o.provides

CMakeFiles/OpNovice.dir/src/OpNoviceRunAction.cc.o.provides.build: CMakeFiles/OpNovice.dir/src/OpNoviceRunAction.cc.o

CMakeFiles/OpNovice.dir/src/OpNoviceStackingAction.cc.o: CMakeFiles/OpNovice.dir/flags.make
CMakeFiles/OpNovice.dir/src/OpNoviceStackingAction.cc.o: /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNoviceStackingAction.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice-build/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/OpNovice.dir/src/OpNoviceStackingAction.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OpNovice.dir/src/OpNoviceStackingAction.cc.o -c /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNoviceStackingAction.cc

CMakeFiles/OpNovice.dir/src/OpNoviceStackingAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpNovice.dir/src/OpNoviceStackingAction.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNoviceStackingAction.cc > CMakeFiles/OpNovice.dir/src/OpNoviceStackingAction.cc.i

CMakeFiles/OpNovice.dir/src/OpNoviceStackingAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpNovice.dir/src/OpNoviceStackingAction.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNoviceStackingAction.cc -o CMakeFiles/OpNovice.dir/src/OpNoviceStackingAction.cc.s

CMakeFiles/OpNovice.dir/src/OpNoviceStackingAction.cc.o.requires:
.PHONY : CMakeFiles/OpNovice.dir/src/OpNoviceStackingAction.cc.o.requires

CMakeFiles/OpNovice.dir/src/OpNoviceStackingAction.cc.o.provides: CMakeFiles/OpNovice.dir/src/OpNoviceStackingAction.cc.o.requires
	$(MAKE) -f CMakeFiles/OpNovice.dir/build.make CMakeFiles/OpNovice.dir/src/OpNoviceStackingAction.cc.o.provides.build
.PHONY : CMakeFiles/OpNovice.dir/src/OpNoviceStackingAction.cc.o.provides

CMakeFiles/OpNovice.dir/src/OpNoviceStackingAction.cc.o.provides.build: CMakeFiles/OpNovice.dir/src/OpNoviceStackingAction.cc.o

CMakeFiles/OpNovice.dir/src/OpNoviceSteppingAction.cc.o: CMakeFiles/OpNovice.dir/flags.make
CMakeFiles/OpNovice.dir/src/OpNoviceSteppingAction.cc.o: /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNoviceSteppingAction.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice-build/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/OpNovice.dir/src/OpNoviceSteppingAction.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OpNovice.dir/src/OpNoviceSteppingAction.cc.o -c /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNoviceSteppingAction.cc

CMakeFiles/OpNovice.dir/src/OpNoviceSteppingAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpNovice.dir/src/OpNoviceSteppingAction.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNoviceSteppingAction.cc > CMakeFiles/OpNovice.dir/src/OpNoviceSteppingAction.cc.i

CMakeFiles/OpNovice.dir/src/OpNoviceSteppingAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpNovice.dir/src/OpNoviceSteppingAction.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNoviceSteppingAction.cc -o CMakeFiles/OpNovice.dir/src/OpNoviceSteppingAction.cc.s

CMakeFiles/OpNovice.dir/src/OpNoviceSteppingAction.cc.o.requires:
.PHONY : CMakeFiles/OpNovice.dir/src/OpNoviceSteppingAction.cc.o.requires

CMakeFiles/OpNovice.dir/src/OpNoviceSteppingAction.cc.o.provides: CMakeFiles/OpNovice.dir/src/OpNoviceSteppingAction.cc.o.requires
	$(MAKE) -f CMakeFiles/OpNovice.dir/build.make CMakeFiles/OpNovice.dir/src/OpNoviceSteppingAction.cc.o.provides.build
.PHONY : CMakeFiles/OpNovice.dir/src/OpNoviceSteppingAction.cc.o.provides

CMakeFiles/OpNovice.dir/src/OpNoviceSteppingAction.cc.o.provides.build: CMakeFiles/OpNovice.dir/src/OpNoviceSteppingAction.cc.o

CMakeFiles/OpNovice.dir/src/OpNoviceSteppingVerbose.cc.o: CMakeFiles/OpNovice.dir/flags.make
CMakeFiles/OpNovice.dir/src/OpNoviceSteppingVerbose.cc.o: /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNoviceSteppingVerbose.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice-build/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/OpNovice.dir/src/OpNoviceSteppingVerbose.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OpNovice.dir/src/OpNoviceSteppingVerbose.cc.o -c /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNoviceSteppingVerbose.cc

CMakeFiles/OpNovice.dir/src/OpNoviceSteppingVerbose.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpNovice.dir/src/OpNoviceSteppingVerbose.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNoviceSteppingVerbose.cc > CMakeFiles/OpNovice.dir/src/OpNoviceSteppingVerbose.cc.i

CMakeFiles/OpNovice.dir/src/OpNoviceSteppingVerbose.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpNovice.dir/src/OpNoviceSteppingVerbose.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice/src/OpNoviceSteppingVerbose.cc -o CMakeFiles/OpNovice.dir/src/OpNoviceSteppingVerbose.cc.s

CMakeFiles/OpNovice.dir/src/OpNoviceSteppingVerbose.cc.o.requires:
.PHONY : CMakeFiles/OpNovice.dir/src/OpNoviceSteppingVerbose.cc.o.requires

CMakeFiles/OpNovice.dir/src/OpNoviceSteppingVerbose.cc.o.provides: CMakeFiles/OpNovice.dir/src/OpNoviceSteppingVerbose.cc.o.requires
	$(MAKE) -f CMakeFiles/OpNovice.dir/build.make CMakeFiles/OpNovice.dir/src/OpNoviceSteppingVerbose.cc.o.provides.build
.PHONY : CMakeFiles/OpNovice.dir/src/OpNoviceSteppingVerbose.cc.o.provides

CMakeFiles/OpNovice.dir/src/OpNoviceSteppingVerbose.cc.o.provides.build: CMakeFiles/OpNovice.dir/src/OpNoviceSteppingVerbose.cc.o

# Object files for target OpNovice
OpNovice_OBJECTS = \
"CMakeFiles/OpNovice.dir/OpNovice.cc.o" \
"CMakeFiles/OpNovice.dir/src/OpNoviceActionInitialization.cc.o" \
"CMakeFiles/OpNovice.dir/src/OpNoviceDetectorConstruction.cc.o" \
"CMakeFiles/OpNovice.dir/src/OpNovicePhysicsList.cc.o" \
"CMakeFiles/OpNovice.dir/src/OpNovicePhysicsListMessenger.cc.o" \
"CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorAction.cc.o" \
"CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorMessenger.cc.o" \
"CMakeFiles/OpNovice.dir/src/OpNoviceRunAction.cc.o" \
"CMakeFiles/OpNovice.dir/src/OpNoviceStackingAction.cc.o" \
"CMakeFiles/OpNovice.dir/src/OpNoviceSteppingAction.cc.o" \
"CMakeFiles/OpNovice.dir/src/OpNoviceSteppingVerbose.cc.o"

# External object files for target OpNovice
OpNovice_EXTERNAL_OBJECTS =

OpNovice: CMakeFiles/OpNovice.dir/OpNovice.cc.o
OpNovice: CMakeFiles/OpNovice.dir/src/OpNoviceActionInitialization.cc.o
OpNovice: CMakeFiles/OpNovice.dir/src/OpNoviceDetectorConstruction.cc.o
OpNovice: CMakeFiles/OpNovice.dir/src/OpNovicePhysicsList.cc.o
OpNovice: CMakeFiles/OpNovice.dir/src/OpNovicePhysicsListMessenger.cc.o
OpNovice: CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorAction.cc.o
OpNovice: CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorMessenger.cc.o
OpNovice: CMakeFiles/OpNovice.dir/src/OpNoviceRunAction.cc.o
OpNovice: CMakeFiles/OpNovice.dir/src/OpNoviceStackingAction.cc.o
OpNovice: CMakeFiles/OpNovice.dir/src/OpNoviceSteppingAction.cc.o
OpNovice: CMakeFiles/OpNovice.dir/src/OpNoviceSteppingVerbose.cc.o
OpNovice: CMakeFiles/OpNovice.dir/build.make
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4Tree.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4GMocren.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4visHepRep.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4RayTracer.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4VRML.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4OpenGL.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4gl2ps.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4interfaces.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4persistency.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4analysis.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4error_propagation.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4readout.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4physicslists.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4parmodels.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4FR.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4vis_management.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4modeling.dylib
OpNovice: /usr/X11R6/lib/libGL.dylib
OpNovice: /usr/X11R6/lib/libGLU.dylib
OpNovice: /usr/X11R6/lib/libSM.dylib
OpNovice: /usr/X11R6/lib/libICE.dylib
OpNovice: /usr/X11R6/lib/libX11.dylib
OpNovice: /usr/X11R6/lib/libXext.dylib
OpNovice: /usr/X11R6/lib/libXmu.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4run.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4event.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4tracking.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4processes.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4zlib.dylib
OpNovice: /usr/lib/libexpat.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4digits_hits.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4track.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4particles.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4geometry.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4geomUSolids.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4materials.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4graphics_reps.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4intercoms.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4global.dylib
OpNovice: /Users/djaffe/work/GEANT4work/geant4.10.1-install/lib/libG4clhep.dylib
OpNovice: CMakeFiles/OpNovice.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable OpNovice"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OpNovice.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OpNovice.dir/build: OpNovice
.PHONY : CMakeFiles/OpNovice.dir/build

CMakeFiles/OpNovice.dir/requires: CMakeFiles/OpNovice.dir/OpNovice.cc.o.requires
CMakeFiles/OpNovice.dir/requires: CMakeFiles/OpNovice.dir/src/OpNoviceActionInitialization.cc.o.requires
CMakeFiles/OpNovice.dir/requires: CMakeFiles/OpNovice.dir/src/OpNoviceDetectorConstruction.cc.o.requires
CMakeFiles/OpNovice.dir/requires: CMakeFiles/OpNovice.dir/src/OpNovicePhysicsList.cc.o.requires
CMakeFiles/OpNovice.dir/requires: CMakeFiles/OpNovice.dir/src/OpNovicePhysicsListMessenger.cc.o.requires
CMakeFiles/OpNovice.dir/requires: CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorAction.cc.o.requires
CMakeFiles/OpNovice.dir/requires: CMakeFiles/OpNovice.dir/src/OpNovicePrimaryGeneratorMessenger.cc.o.requires
CMakeFiles/OpNovice.dir/requires: CMakeFiles/OpNovice.dir/src/OpNoviceRunAction.cc.o.requires
CMakeFiles/OpNovice.dir/requires: CMakeFiles/OpNovice.dir/src/OpNoviceStackingAction.cc.o.requires
CMakeFiles/OpNovice.dir/requires: CMakeFiles/OpNovice.dir/src/OpNoviceSteppingAction.cc.o.requires
CMakeFiles/OpNovice.dir/requires: CMakeFiles/OpNovice.dir/src/OpNoviceSteppingVerbose.cc.o.requires
.PHONY : CMakeFiles/OpNovice.dir/requires

CMakeFiles/OpNovice.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OpNovice.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OpNovice.dir/clean

CMakeFiles/OpNovice.dir/depend:
	cd /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice-build /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice-build /Users/djaffe/work/GIT/G4ONETON/NewStuff/OpNovice-build/CMakeFiles/OpNovice.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OpNovice.dir/depend

