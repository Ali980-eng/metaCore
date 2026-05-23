# Installation and Setup

## Prerequisites

- PowerShell 5.0 or higher
- A C++ compiler (g++, clang, MSVC) OR
- A C compiler (gcc, clang) OR
- C# compiler (csc) OR
- Python 3+

## Step 1: Copy the Module

Copy `PowerBuild.psm1` to your project directory:

```powershell
# Copy from source to your project
Copy-Item PowerBuild.psm1 -Destination ./your-project/
```

## Step 2: Import the Module

```powershell
# Import the module
Import-Module ./PowerBuild.psm1 -Force

# Create new builder instance
$build = [PowerBuild]::new()
```

## Step 3: Set Basic Configuration

```powershell
$build.SetProjectName("MyApp")
$build.SetLanguage("C++")
$build.SetCompiler("g++")
```

## Step 4: Add Source Paths

```powershell
# Add where your source code is
$build.AddSourcePath("./src")

# Add where headers are located
$build.AddIncludePath("./include")
```

## Step 5: Create Build Directory

```powershell
$outputDir = "./build"
if (-not (Test-Path $outputDir)) {
    New-Item -ItemType Directory -Path $outputDir -Force | Out-Null
}
```

## Step 6: Start Building

```powershell
try {
    $build.Build($outputDir)
    Write-Host "Build successful!" -ForegroundColor Green
} catch {
    Write-Host "Build failed: $_" -ForegroundColor Red
}
```

## Compiler Installation

### Windows - MinGW (G++)

```powershell
# Using Chocolatey
choco install mingw

# Or download from https://www.mingw-w64.org/
```

### Windows - Visual Studio (MSVC)

Install Visual Studio Community Edition with C++ workload.

### Linux - GCC

```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install build-essential

# Fedora/RHEL
sudo yum groupinstall "Development Tools"

# Arch
sudo pacman -S base-devel
```

### Linux - Clang

```bash
# Ubuntu/Debian
sudo apt-get install clang

# Fedora
sudo yum install clang

# Arch
sudo pacman -S clang
```

### Linux - Python

```bash
# Usually pre-installed, but check
python3 --version

# If not installed
sudo apt-get install python3
```

### Windows - C# (CSC)

Included with Visual Studio or use:

```powershell
choco install dotnet
```

## Verify Installation

### Check Compiler

```powershell
# For G++
g++ --version

# For GCC
gcc --version

# For CSC
csc.exe /?

# For Python
python --version
```

### Test PowerBuild

```powershell
Import-Module ./PowerBuild.psm1

$build = [PowerBuild]::new()
$build.SetProjectName("Test")
$build.SetLanguage("C++")
$build.SetCompiler("g++")

$validation = $build.ValidateSetup()
if ($validation.Valid) {
    Write-Host "✓ Setup is valid"
} else {
    Write-Host "✗ Setup has errors:"
    $validation.Errors | ForEach-Object { Write-Host "  - $_" }
}
```

## Project Structure

Organize your project like this:

```none
MyProject/
├── PowerBuild.psm1          ← Copy here
├── src/                      ← Source files (.cpp, .c, .cs, .py)
│   ├── main.cpp
│   ├── utils.cpp
│   └── ...
├── include/                  ← Header files (.h)
│   ├── utils.h
│   └── ...
├── build/                    ← Output directory (created automatically)
│   ├── main.o
│   ├── utils.o
│   └── MyProject.exe
└── build.ps1                 ← Your build script
```

## Create Build Script

Create `build.ps1` in project root:

```powershell
#!/usr/bin/env pwsh
Import-Module ./PowerBuild.psm1 -Force

$build = [PowerBuild]::new()
$build.SetVerbose($true)
$build.SetProjectName("MyProject")
$build.SetLanguage("C++")
$build.SetCompiler("g++")

$build.AddSourcePath("./src")
$build.AddIncludePath("./include")

$outputDir = "./build"
if (-not (Test-Path $outputDir)) {
    New-Item -ItemType Directory -Path $outputDir -Force | Out-Null
}

try {
    $build.Build($outputDir)
    Write-Host "✓ Build succeeded" -ForegroundColor Green
} catch {
    Write-Host "✗ Build failed: $_" -ForegroundColor Red
    exit 1
}
```

## Run Build Script

```powershell
# On Windows
.\build.ps1

# On Linux/macOS
pwsh ./build.ps1
```

## Troubleshooting Installation

### "Compiler not found"

Check if compiler is in PATH:

```powershell
# Find compiler manually
Get-Command g++
Get-Command gcc
Get-Command csc

# Or use which on Linux
which g++
which gcc
```

If not found, install compiler or add to PATH.

### "Module import failed"

Ensure PowerBuild.psm1 is in current directory and readable.

### "Access denied"

Set execution policy:

```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```

### "PowerShell version too old"

Update PowerShell:

```powershell
# Check version
$PSVersionTable

# Update (PowerShell 7+)
choco install powershell-core
```
