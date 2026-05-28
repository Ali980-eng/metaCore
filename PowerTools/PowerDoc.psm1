# ============================================================
# MODULE: PowerDoc.psm1
# Description: Generate documentation (TXT, MD, Doxygen) for code files using Ollama.
# Usage:
#   Import-Module .\PowerDoc.psm1
#   Set-OllamaModel -Name "phi3:mini"
#   Invoke-AutoDoc -Path ".\src" -OutputFormat "All" -Recurse
# ============================================================

# ===================== GLOBAL CONFIGURATION =====================
$script:OllamaModel = "phi3:mini"   # Default model, can be changed with Set-OllamaModel
# =================================================================

<#
.SYNOPSIS
    Set the Ollama model to use for documentation generation.
.DESCRIPTION
    Changes the global model name used by Invoke-AutoDoc.
.PARAMETER Name
    Name of the Ollama model (e.g., "phi3:mini", "llama3.2:3b").
.EXAMPLE
    Set-OllamaModel -Name "codellama:7b"
#>
function Set-OllamaModel {
    param(
        [Parameter(Mandatory=$true)]
        [string]$Name
    )
    $script:OllamaModel = $Name
    Write-Host "Ollama model set to: $script:OllamaModel" -ForegroundColor Green
}

<#
.SYNOPSIS
    Generate documentation for code files using Ollama.
.DESCRIPTION
    Supports TXT, MD, Doxygen, or All formats. Works on a single file or a folder.
.PARAMETER Path
    Path to a file or folder.
.PARAMETER OutputFormat
    Format of the output: 'txt', 'md', 'doxygen', or 'All' (generates all three).
.PARAMETER OutputDir
    Directory where generated documentation will be saved.
.PARAMETER Recurse
    If Path is a folder, process all matching files recursively.
.PARAMETER Extensions
    File extensions to include (e.g., @('.cpp','.h','.ps1')). Default includes common languages.
.PARAMETER Force
    Overwrite existing output files.
.EXAMPLE
    Invoke-AutoDoc -Path ".\main.cpp" -OutputFormat "doxygen"
.EXAMPLE
    Invoke-AutoDoc -Path ".\src" -OutputFormat "All" -Recurse -Extensions @('.cpp','.h')
#>
function Invoke-AutoDoc {
    param(
        [Parameter(Mandatory=$true)]
        [string]$Path,
        
        [ValidateSet('txt', 'md', 'doxygen', 'All')]
        [string]$OutputFormat = "doxygen",
        
        [string]$OutputDir = ".\Documentation",
        
        [switch]$Recurse,
        
        [string[]]$Extensions = @('.cpp', '.c', '.h', '.hpp', '.java', '.ps1', '.psm1', '.py', '.cs', '.js', '.ts'),
        
        [switch]$Force
    )

    # ---------- Helper: Determine language from extension ----------
    function Get-LanguageFromExtension {
        param([string]$Extension)
        switch -Regex ($Extension) {
            '\.(cpp|c|h|hpp|cc)$' { return "C++" }
            '\.c$' { return "C" }
            '\.java$' { return "Java" }
            '\.ps1|\.psm1$' { return "PowerShell" }
            '\.py$' { return "Python" }
            '\.cs$' { return "C#" }
            '\.js|\.ts$' { return "JavaScript/TypeScript" }
            default { return "General" }
        }
    }

    # ---------- Helper: Document a single file ----------
    function Document-File {
        param(
            [string]$FilePath,
            [string]$OutputFormat,
            [string]$OutputDir,
            [bool]$Force
        )
        
        $code = Get-Content $FilePath -Raw -ErrorAction Stop
        $fileName = [System.IO.Path]::GetFileNameWithoutExtension($FilePath)
        $extension = [System.IO.Path]::GetExtension($FilePath)
        $language = Get-LanguageFromExtension -Extension $extension
        
        Write-Host "Processing: $([System.IO.Path]::GetFileName($FilePath))" -ForegroundColor Cyan
        
        # Prepare output subfolder for this file (optional, but keeps things tidy)
        $fileOutputDir = Join-Path -Path $OutputDir -ChildPath $fileName
        if ($OutputFormat -ne "All") {
            $fileOutputDir = $OutputDir
        } else {
            # When All, create subfolder per file to avoid mixing
            New-Item -ItemType Directory -Force -Path $fileOutputDir | Out-Null
        }
        
        # ---- Doxygen output (inside the code) ----
        if ($OutputFormat -in @('doxygen', 'All')) {
            $doxygenPrompt = @"
Add Doxygen-style comments to the following $language code.
Rules:
- Use /** ... */ for C/C++/Java/C# or <# ... #> for PowerShell.
- Every function must have a brief, @param for each parameter, @return if applicable.
- Write the full code with the added documentation.

Code:
$code
"@
            $doxygenOutput = $doxygenPrompt | ollama run $script:OllamaModel
            $doxygenFile = Join-Path -Path $fileOutputDir -ChildPath "$fileName$extension"
            if ($Force -or -not (Test-Path $doxygenFile)) {
                $doxygenOutput | Out-File -FilePath $doxygenFile -Encoding UTF8
                Write-Host "  -> Doxygen: $doxygenFile" -ForegroundColor Green
            } else {
                Write-Host "  -> Doxygen: file exists (use -Force to overwrite)" -ForegroundColor Yellow
            }
        }
        
        # ---- Markdown output ----
        if ($OutputFormat -in @('md', 'All')) {
            $mdPrompt = @"
Write a clear Markdown summary for the following $language code.
Include:
- A short description of what this code does.
- List all functions and their purposes.
- A simple usage example.

Code:
$code
"@
            $mdOutput = $mdPrompt | ollama run $script:OllamaModel
            $mdFile = Join-Path -Path $fileOutputDir -ChildPath "$fileName.md"
            if ($Force -or -not (Test-Path $mdFile)) {
                $mdOutput | Out-File -FilePath $mdFile -Encoding UTF8
                Write-Host "  -> Markdown: $mdFile" -ForegroundColor Green
            } else {
                Write-Host "  -> Markdown: file exists (use -Force to overwrite)" -ForegroundColor Yellow
            }
        }
        
        # ---- Plain Text output ----
        if ($OutputFormat -in @('txt', 'All')) {
            $txtPrompt = @"
Write a plain text documentation for the following $language code.
Include:
- A short description.
- List of functions with brief explanations.
- No markdown or special formatting, just plain text.

Code:
$code
"@
            $txtOutput = $txtPrompt | ollama run $script:OllamaModel
            $txtFile = Join-Path -Path $fileOutputDir -ChildPath "$fileName.txt"
            if ($Force -or -not (Test-Path $txtFile)) {
                $txtOutput | Out-File -FilePath $txtFile -Encoding UTF8
                Write-Host "  -> Text: $txtFile" -ForegroundColor Green
            } else {
                Write-Host "  -> Text: file exists (use -Force to overwrite)" -ForegroundColor Yellow
            }
        }
    }

    # ---------- Main script logic ----------
    # Check Ollama availability
    try {
        $null = ollama --version
    } catch {
        Write-Error "Ollama is not installed or not in PATH. Please install Ollama first."
        return
    }
    
    # Check if model exists, pull if needed
    $models = ollama list | Select-String $script:OllamaModel
    if (-not $models) {
        Write-Host "Model '$($script:OllamaModel)' not found locally. Pulling now..." -ForegroundColor Yellow
        ollama pull $script:OllamaModel
    }
    
    # Create base output directory
    New-Item -ItemType Directory -Force -Path $OutputDir | Out-Null
    
    # Resolve path
    if (-not (Test-Path $Path)) {
        Write-Error "Path not found: $Path"
        return
    }
    
    $item = Get-Item $Path
    if (-not $item.PSIsContainer) {
        # Single file
        Document-File -FilePath $item.FullName -OutputFormat $OutputFormat -OutputDir $OutputDir -Force $Force
    } else {
        # Folder
        $getParams = @{
            Path = $item.FullName
            File = $true
        }
        if ($Recurse) { $getParams.Recurse = $true }
        $files = Get-ChildItem @getParams | Where-Object { $Extensions -contains $_.Extension }
        
        if ($files.Count -eq 0) {
            Write-Warning "No files with extensions ($($Extensions -join ', ')) found in $Path"
            return
        }
        
        foreach ($file in $files) {
            Document-File -FilePath $file.FullName -OutputFormat $OutputFormat -OutputDir $OutputDir -Force $Force
        }
    }
    
    Write-Host "`n✅ Documentation completed. Output saved to: $OutputDir" -ForegroundColor Green
}

# Export the public functions
Export-ModuleMember -Function Set-OllamaModel, Invoke-AutoDoc