# PowerShell Code Summary

This PowerShell script generates documentation for code files using Ollama, a tool for automatic documentation generation. The script allows users to set a custom model and generate documentation in various formats (TXT, MD, Doxygen, or All) for a specified file or folder.

## Functions Used

* `Set-OllamaModel`: Sets the default model name used by the Ollama function.
* `Invoke-AutoDoc`: Generates documentation for code files using Ollama. It supports TXT, MD, Doxygen, and All formats.

## Usage Example

```powershell
# Set the Ollama model to "phi3:mini"
Set-OllamaModel -Name "phi3:mini"

# Generate documentation for a file in the current directory
Invoke-AutoDoc -Path ".\src" -OutputFormat "All" -Recurse

# Generate documentation for all files in the current directory and its subdirectories
Invoke-AutoDoc -Path ".\" *" -OutputFormat "All" -Recurse -Extensions @(".cpp", "*.h")

# Generate documentation in Markdown format for a file or folder
Invoke-AutoDoc -Path ".\src" -OutputFormat "md"
```

## Global Configuration

* `$script:OllamaModel`: The default model name used by the Ollama function.
* `Set-OllamaModel`: Sets the default model name.

## Output Format

The script supports TXT, MD, Doxygen, and All formats.
When generating documentation for a file or folder, you can specify the desired output format using one of the following options:

* `-OutputFormat "txt"`: Generates plain text documentation.
* `-OutputFormat "md"`: Generates Markdown documentation.
* `-OutputFormat "doxygen"`: Generates Doxygen documentation.
* `-OutputFormat "All"`: Generates all formats (TXT, MD, Doxygen) for a single file or folder.
