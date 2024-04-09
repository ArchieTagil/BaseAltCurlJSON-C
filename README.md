# BaseALT test task

## Build and run

1. If you want to build the whole project use: "make build" command. You'll be able to find the executable file in "bin" directory

2. If you only want to build the library use: "make cr_lib" command. The library will be placed in "lib" directory.

3. "make" without arguments will build and run program.

### IMPORTANT!!!

    don't forget to add path of the new shared library to your LD_LIBRARY_PATH !!! Use follow commands for this:

        LD_LIBRARY_PATH=/home/greybaca/base_alt_work_directory/lib:$LD_LIBRARY_PATH
        export LD_LIBRARY_PATH

## How to use CLI

List of commands to use:

1. "set_branch1 sisyphus" - (avaliable arguments: sisyphus, p10, p9)

2. "set_branch2 sisyphus" - (avaliable arguments: sisyphus, p10, p9)

3. "show_branches" - show names of selected branches (if they set) or empty.

4. "get_data" - works only if both branches was set. It'll get lists of packages of both branches to compare.

5. "show branch1_data" - show uploded data for branch1

6. "show branch2_data" - show uploaded data for branch2

7. "compare left" - works only if data for both branches was received. Show packages that are present in the first branch and are missing in the second one.

8. "compare right" - works only if data for both branches was received. Show packages that are present in the second branch and are missing in the first one.

9. "show highest_version_release" - works only if data for both branches was received. It'll show packages whose version-release in the first branch more higher than the version-release in the second one.

10. "exit" - just quit out of the program.