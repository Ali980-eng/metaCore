# ============================================================
# AutoDoc.ps1 - Generate documentation using Ollama
# Usage:
#   .\AutoDoc.ps1 -Path <file-or-folder> -OutputFormat <txt|md|doxygen|All>
# Examples:
#   .\AutoDoc.ps1 -Path .\main.cpp -OutputFormat doxygen
#   .\AutoDoc.ps1 -Path .\src -OutputFormat All -Recurse -Extensions @('.cpp','.h')
# ============================================================

param(
    [Parameter(Mandatory=$true)]
    [string]$Path, # File or folder path

    [ValidateSet('txt', 'md', 'doxygen', 'All')]
    [string]$OutputFormat = "doxygen", # Output format

    [string]$OutputDir = ".\Documentation", # Output directory

    [switch]$Recurse, # Process subfolders

    [string[]]$Extensions = @('.cpp', '.c', '.h', '.hpp', '.java', '.ps1', '.psm1', '.py', '.cs', '.js', '.ts'),

    [switch]$Force, # Overwrite existing files

    [string]$Model = "llama3.2:1b"  # Ollama model name
)

# ===================== Helper Functions =====================

# Determine programming language from file extension
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

# Document a single file
function DocumentFile {
    param(
        [string]$FilePath,
        [string]$OutputFormat,
        [string]$OutputDir,
        [bool]$Force
    )

    $code = Get-Content $FilePath -Raw -ErrorAction Stop
    $baseName = [System.IO.Path]::GetFileNameWithoutExtension($FilePath)
    $extension = [System.IO.Path]::GetExtension($FilePath)
    $language = Get-LanguageFromExtension -Extension $extension

    Write-Host "Processing: $([System.IO.Path]::GetFileName($FilePath))" -ForegroundColor Cyan

    # Determine output subfolder (for 'All' format, create a folder per file)
    if ($OutputFormat -eq "All") {
        $targetDir = Join-Path -Path $OutputDir -ChildPath $baseName
        New-Item -ItemType Directory -Force -Path $targetDir | Out-Null
    } else {
        $targetDir = $OutputDir
    }

    # ----- Doxygen output -----
    if ($OutputFormat -in @('doxygen', 'All')) {
        $doxyPrompt = @"
Add Doxygen-style comments to the following $language code.
Rules:
- Use /** ... */ for C/C++/Java/C# or <# ... #> for PowerShell.
- Every function must have a brief description, @param for each parameter, and @return if applicable.
- Write the full code with the added documentation.

Code:
$code
"@
        $doxyResult = $doxyPrompt | ollama run $Model
        $doxyFile = Join-Path -Path $targetDir -ChildPath "$baseName$extension"
        if ($Force -or -not (Test-Path $doxyFile)) {
            $doxyResult | Out-File -FilePath $doxyFile -Encoding UTF8
            Write-Host "  -> Doxygen: $doxyFile" -ForegroundColor Green
        } else { Write-Host "  -> Doxygen: file exists (use -Force)" -ForegroundColor Yellow }
    }

    # ----- Markdown output -----
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
        $mdResult = $mdPrompt | ollama run $Model
        $mdFile = Join-Path -Path $targetDir -ChildPath "$baseName.md"
        if ($Force -or -not (Test-Path $mdFile)) {
            $mdResult | Out-File -FilePath $mdFile -Encoding UTF8
            Write-Host "  -> Markdown: $mdFile" -ForegroundColor Green
        } else { Write-Host "  -> Markdown: file exists (use -Force)" -ForegroundColor Yellow }
    }

    # ----- Plain text output -----
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
        $txtResult = $txtPrompt | ollama run $Model
        $txtFile = Join-Path -Path $targetDir -ChildPath "$baseName.txt"
        if ($Force -or -not (Test-Path $txtFile)) {
            $txtResult | Out-File -FilePath $txtFile -Encoding UTF8
            Write-Host "  -> Text: $txtFile" -ForegroundColor Green
        } else { Write-Host "  -> Text: file exists (use -Force)" -ForegroundColor Yellow }
    }
}

# ===================== Main Script =====================

# Check Ollama
try {
    $null = ollama --version
} catch {
    Write-Error "Ollama not found. Please install Ollama from https://ollama.com"
    exit 1
}

# Check/pull model
$models = ollama list | Select-String $Model
if (-not $models) {
    Write-Host "Model '$Model' not found locally. Pulling now..." -ForegroundColor Yellow
    ollama pull $Model
}

# Create output directory
New-Item -ItemType Directory -Force -Path $OutputDir | Out-Null

# Resolve input path
if (-not (Test-Path $Path)) {
    Write-Error "Path not found: $Path"
    exit 1
}

$item = Get-Item $Path
if (-not $item.PSIsContainer) {
    # Single file
    DocumentFile -FilePath $item.FullName -OutputFormat $OutputFormat -OutputDir $OutputDir -Force $Force
} else {
    # Folder
    $getParams = @{ Path = $item.FullName; File = $true }
    if ($Recurse) { $getParams.Recurse = $true }
    $files = Get-ChildItem @getParams | Where-Object { $Extensions -contains $_.Extension }

    if ($files.Count -eq 0) {
        Write-Warning "No files with extensions ($($Extensions -join ', ')) in $Path"
        exit 0
    }

    foreach ($file in $files) {
        Document-File -FilePath $file.FullName -OutputFormat $OutputFormat -OutputDir $OutputDir -Force $Force
    }
}

Write-Host "`n✅ Done! Output in: $OutputDir" -ForegroundColor Green