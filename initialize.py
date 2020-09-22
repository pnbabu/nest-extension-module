#!/usr/bin/env python

from fileinput import FileInput
from sys import argv, exit

if len(argv) != 2:
    print("Usage: initialize_module.py <module_name>")
    exit()

module_name = argv[1]

print(f"Initializing extension module using name '{module_name}'")
if input("Continue? [Y/n] ").lower() not in ("", "y"):
    print("Aborting.")
    exit()

fnames = [
    "CMakeLists.txt",
    "README.md",
    "src/mymodule.cpp",
    "src/mymodule.h"
]

module_namespace = "nest_" + module_name.lower()
module_symbol = module_name.lower()

for fname in fnames:
    print(f"Processing file '{fname}'... ")
    with FileInput(fname, inplace=True, backup=".bak") as file:
        for line in file:
            line = line.replace("<<MODULE_NAME>>", module_name)
            line = line.replace("<<MODULE_NAMESPACE>>", module_namespace)
            line = line.replace("<<MODULE_SYMBOL>>", module_symbol)
            print(line, end="")

print(f"""
Done initializing the extension module.

You can now add your custom source code files to the 'src' directory
and instantiate or register the contained components from within
'src/mymodule.h' and 'src/mymodule.cpp'.

Once you're done, you can configure the module by running
  mkdir build && cd build
  cmake -Dwith-nest=<nest_install_dir>/bin/nest-config ..

To compile and install the module, run
  make && make install

If all goes well, you can then load your module into NEST by
  nest.Install({module_symbol})

More detailed instructions for writing custom extension modules
can be found at https://github.com/nest/nest-extension-module.
""")
