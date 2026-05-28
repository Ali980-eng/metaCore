# AutoDoc.ps1 Description

AutoDoc.ps1 is a PowerShell script used to generate documentation for C++, Python, and other programming languages. It takes the path to a file or folder, output format (txt, md, doxygen, All), and additional settings as input.

## Functions Used

* `Get-LanguageFromExtension`: Determines the programming language from a file extension.
* `Document-File`: Processes a single file by adding comments, descriptions, and explanations. It can be used to generate documentation for C++, Python, and other languages.
* `New-Item`: Creates a new directory with the specified name.
* `Get-Item`: Retrieves an item from the file system.
* `Test-Path`: Verifies if a path exists.
* `ollama run`: Runs Ollama on the generated code.

### Usage

* Add the script to your PowerShell profile or use it directly in the command line:

```powershell
    .\AutoDoc.ps1 -Path <file-or-folder> -OutputFormat <txt|md|doxygen|All> -OutputDir <folder>
```

### Examples

* Generate Doxygen documentation for a C++ file:

    ```powershell
        .\\AutoDoc.ps1 -Path .\\main.cpp -OutputFormat doxygen
    ```

* Generate Markdown documentation for a Python file:

    ```powershell
    .\\AutoDoc.ps1 -Path .\\src -OutputFormat All -Recurse -Extensions @('.py', '.md')
    ```

### Main Script

The main script checks if Ollama is installed and pulls the specified model. It then creates an output directory and resolves the input path.

* Check if Ollama is installed:

    ```powershell
        try {
            $null = ollama --version
        } catch {
            Write-Error "Ollama not found. Please install Ollama from https://ollama.com"
            exit 1
        }
    ```

* Pull the specified model:

    ```powershell
        $models = ollama list | Select-String $Model
        if (-not $models) {
            Write-Host "Model '$Model' not found locally. Pulling now..." -ForegroundColor Yellow
            ollama pull $Model
        }
    ```

* Create an output directory:

    ```powershell
        New-Item -ItemType Directory -Force -Path $OutputDir | Out-Null
    ```

### Output Formats

The script supports the following output formats:

* Doxygen: Generates HTML and Markdown files with comments and descriptions.
* All: Creates a new folder for each file in the specified format.
* txt: Writes plain text documentation to a file.
