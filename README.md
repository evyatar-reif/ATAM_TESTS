## Instructions

1. **Open the terminal** in the `part1` folder and run:

   ```bash
   git clone https://github.com/evyatar-reif/ATAM_TESTS.git
   ```

2. **Folder structure** after cloning will look like this:

   ```
   /part1
       ├── students_code.S
       ├── _aux.o
       └── ATAM_TESTS/
           ├── tests/
           └── test_all.c
   ```

3. In the `part1` folder, **run the following command** to compile and test your code:

   ```bash
   gcc -g -o part1 students_code.S ./ATAM_TESTS/test_all.c _aux.o && ./part1
   ```

   This will compile your assembly code and run the tests.
