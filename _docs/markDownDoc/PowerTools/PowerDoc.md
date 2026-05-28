**PowerShell Code Summary**

This PowerShell script generates documentation for code files using Ollama,[7D[K
Ollama, a tool for automatic documentation generation. The script allows us[2D[K
users to set a custom model and generate documentation in various formats ([1D[K
(TXT, MD, Doxygen, or All) for a specified file or folder.

**Functions Used:**

* `Set-OllamaModel`: Sets the default model name used by the Ollama functio[7D[K
function.
* `Invoke-AutoDoc`: Generates documentation for code files using Ollama. It[2D[K
It supports TXT, MD, Doxygen, and All formats.

**Usage Example:**

```powershell
# Set the Ollama model to "phi3:mini"
Set-OllamaModel -Name "phi3:mini"

# Generate documentation for a file in the current directory
Invoke-AutoDoc -Path ".\src" -OutputFormat "All" -Recurse

# Generate documentation for all files in the current directory and its sub[3D[K
subdirectories
Invoke-AutoDoc -Path ".\" *" -OutputFormat "All" -Recurse -Extensions @(".c[5D[K
@(".cpp", "*.h")

# Generate documentation in Markdown format for a file or folder
Invoke-AutoDoc -Path ".\src" -OutputFormat "md"
```

**Global Configuration:**

* `$script:OllamaModel`: The default model name used by the Ollama function[8D[K
function.
* `Set-OllamaModel`: Sets the default model name.

**Output Format:**

The script supports TXT, MD, Doxygen, and All formats. When generating docu[4D[K
documentation for a file or folder, you can specify the desired output form[4D[K
format using one of the following options:

* `-OutputFormat "txt"`: Generates plain text documentation.
* `-OutputFormat "md"`: Generates Markdown documentation.
* `-OutputFormat "doxygen"`: Generates Doxygen documentation.
* `-OutputFormat "All"`: Generates all formats (TXT, MD, Doxygen) for a sin[3D[K
single file or folder.

