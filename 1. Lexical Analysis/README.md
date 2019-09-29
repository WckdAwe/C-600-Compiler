## Stage 1 - Lexical Analysis
### Executing the source
After confirming that you have successfully installed flex (you can try command **flex -V**), execute the following commands:

    flex compiler.l    # This command generates lex.yy.c
    gcc lex.yy.c -lfl  # This command builds lex.yy.c to an executable
    ./a.exe Tests/test.cpp # WINDOWS: Execute Lexical analyzer on Tests/test.cpp
    ./a Tests/test.cpp     # LINUX: Execute Lexical analyzer on Tests/test.cpp



### Files
 - **compiler.l**: Lexical Analysis Rules
 - **compiler.h**: Includes all the Tokens for the language
 - **ConversionFunctions.c**: Basic functions for converting between bin-oct-hex to decimal. **This file is removed on next stages**.



### Troubleshooting
 - **Illegal Characters** on Windows: Make sure your test.cpp file is on **LF MODE** and **not CRLF**. This happens because when files are uploaded on Github, they are automatically converted into Linux File Endings (\r\n) instead of (\n) which is detected by windows.
   - This can be considered a bug to be fixed by our lexer. Any pull request would be welcome!