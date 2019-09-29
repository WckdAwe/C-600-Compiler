## Stage 2 - Lexical Analysis
### Executing the source
After confirming that you have successfully installed both **flex** and **bison**, execute the following commands:

    make                             # Automatically build all necessary files
    ./bison <Directory/TestFile.cpp> # Execute Lexical Analysis on the testfile.



### Files
 - **Transition Diagram**: The Transition Diagram for our C++600's Language subset.
 - **bison.tab.c/h**: Automatically generated files.
 - **hashtbl.c/h**: Library for creating and printing HashTables in C.
 - **settings.h**: Settings for this stage (such as max errors to print).
 - **Makefile**: Rules to automatically create all necessary files, read more bellow.



### MakeFile
To see what are and how to use Makefiles see the following visit https://makefiletutorial.com/ .



### Troubleshooting
 - **Illegal Characters** on Windows: Make sure your test.cpp file is on **LF MODE** and **not CRLF**. This happens because when files are uploaded on Github, they are automatically converted into Linux File Endings (\r\n) instead of (\n) which is detected by windows.
   - This can be considered a bug to be fixed by our lexer. Any pull request would be welcome!

