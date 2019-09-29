## Stage 3 - Semantics Analysis
### Executing the source
After confirming that you have successfully installed both **flex** and **bison**, execute the following commands:

    make                             # Automatically build all necessary files
    ./bison <Directory/TestFile.cpp> # Execute Lexical Analysis on the testfile.



### Files
 - **outputs**: Abstract Syntax Tree Output as txt.
 - **ast.c/h**: Abstract Syntax Tree (AST) source.
 - **bison.y**: Parser fitted with AST nodes.
 - **c600.h/general.c/geaneral.h**: Header containing generic libraries.
 - **error.c/h**: Error handling library.
 - **lexer.l**: Lexical Analysis file.
 - **main.c**: Main execution for our compiler.
 - **pretty.c/h**: Handles printing AST to a beautiful format on **ouputs folder**.
 - **semantics.c/h**: Handles semantic analysis using the AST.
 - **symbol.c/h**: Used **instead of hashtable** since it is an easier form to access and create scopes.
 - **types.c/h**: Handles basic & complex type initialization such as int, float, unions e.t.c



### MakeFile
To see what are and how to use Makefiles see the following visit https://makefiletutorial.com/ .



### Troubleshooting
 - **Illegal Characters** on Windows: Make sure your test.cpp file is on **LF MODE** and **not CRLF**. This happens because when files are uploaded on Github, they are automatically converted into Linux File Endings (\r\n) instead of (\n) which is detected by windows.
   - This can be considered a bug to be fixed by our lexer. Any pull request would be welcome!
