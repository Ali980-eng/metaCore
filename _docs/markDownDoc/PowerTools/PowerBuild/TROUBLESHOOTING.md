# Troubleshooting Guide

Common issues and solutions.

## Build Errors

### "Compiler not found"

**Error Message:**

```none
Compiler not found: g++
```

**Causes:**

- Compiler not installed
- Compiler not in PATH
- Wrong compiler name

**Solutions:**

1. **Install compiler:**

   ```powershell
   # Windows - MinGW
   choco install mingw
   
   # Linux - GCC
   sudo apt-get install build-essential
   ```

2. **Check if installed:**

   ```powershell
   g++ --version
   gcc --version
   csc.exe /?
   ```

3. **Add to PATH manually:**

   ```powershell
   $build.SetCompilerPath("g++", "C:\MinGW\bin\g++.exe")
   ```

4. **Find compiler location:**

   ```bash
   # Linux/macOS
   which g++
   which gcc
   
   # Windows
   where g++
   where gcc
   ```

---

### "Target already exists"

**Error Message:**

```none
An item with the same key has already been added
```

**Causes:**

- Adding target config twice
- Target not removed before re-adding

**Solutions:**

```powershell
# Remove before re-adding
$build.removeTargetConfig("Debug")
$build.addTargetConfig("Debug", $newConfig)

# Or clear all first
$build.clearAllConfigs()
$build.addTargetConfig("Debug", $debugConfig)
$build.addTargetConfig("Release", $releaseConfig)
```

---

### "No source paths added"

**Warning:**

```none
No source paths have been added
```

**Causes:**

- Forgot to add source paths
- Wrong source path

**Solutions:**

```powershell
# Add source path
$build.AddSourcePath("./src")

# Verify it was added
$paths = $build.GetSourcePaths()
Write-Host "Source paths: $paths"

# Check if directory exists
if (-not (Test-Path "./src")) {
    Write-Host "Source directory missing!"
}
```

---

### "Compilation failed"

**Error Message:**

```none
Failed to compile file: main.cpp
```

**Causes:**

- Syntax errors in source code
- Missing headers
- Compiler flags wrong
- Missing library dependencies

**Solutions:**

1. **Enable verbose mode:**

   ```powershell
   $build.SetVerbose($true)
   $build.Build("./build")
   ```

2. **Check syntax:**

   ```bash
   # Compile single file
   g++ -c src/main.cpp -I./include
   ```

3. **Verify headers exist:**

   ```powershell
   Get-ChildItem ./include -Include "*.h" -Recurse
   ```

4. **Check include paths:**

   ```powershell
   $paths = $build.GetIncludePaths()
   $paths | ForEach-Object { 
       Write-Host "Include: $_"
       if (-not (Test-Path $_)) {
           Write-Host "  ⚠ Path not found!"
       }
   }
   ```

---

### "Linking failed"

**Error Message:**

```none
Linking failed
```

**Causes:**

- Undefined references
- Missing library files
- Incompatible object files
- Library not linked

**Solutions:**

```powershell
# Check object files created
Get-ChildItem ./build -Filter "*.o" | ForEach-Object {
    Write-Host "Object: $($_.Name)"
}

# Verify all source files compiled
$build.SetVerbose($true)
$build.Build("./build")
```

---

## Configuration Issues

### "Project name not set"

**Error Message:**

```none
Project name not set
```

**Solutions:**

```powershell
$build.SetProjectName("MyApp")
$build.GetProjectName()  # Verify it's set
```

---

### "Programming language not specified"

**Error Message:**

```none
Programming language not specified
```

**Solutions:**

```powershell
$build.SetLanguage("C++")  # or "C", "CSharp", "Python"

# Verify
$lang = $build.GetLanguage()
Write-Host "Language: $lang"
```

---

### "Compiler not set"

**Error Message:**

```none
Compiler not set
```

**Solutions:**

```powershell
$build.SetCompiler("g++")  # Match language

# Verify
$compiler = $build.GetCompiler()
Write-Host "Compiler: $compiler"
```

---

## Path Issues

### "Path not found"

**Error Message:**

```none
Cannot find path './src' because it does not exist
```

**Solutions:**

```powershell
# Verify directory exists
if (-not (Test-Path "./src")) {
    Write-Host "Creating source directory..."
    New-Item -ItemType Directory -Path "./src" | Out-Null
}

# Add files
New-Item -ItemType File -Path "./src/main.cpp"
```

---

### "Permission denied"

**Error Message:**

```none
Access to the path is denied
```

**Causes:**

- Insufficient permissions
- File locked by another process
- Read-only file

**Solutions:**

```powershell
# Check permissions
Get-Item "./src" | Select-Object -ExpandProperty "*Attributes"

# Give read/write permissions
icacls.exe "./src" /grant "%USERNAME%:F"

# Or run PowerShell as administrator
Start-Process powershell -Verb RunAs
```

---

## Platform Issues

### "Not running on correct OS"

**Problem:** Script works on Windows but not Linux/macOS

**Solutions:**

```powershell
$osType = $build.GetOS()
Write-Host "OS Type: $osType"

# Use OS-specific compiler
if ($osType -eq "Windows") {
    $build.SetCompiler("cl.exe")
} else {
    $build.SetCompiler("g++")
}
```

---

### "Wrong file line endings"

**Problem:** Script works locally but fails on different OS

**Solutions:**

```powershell
# Convert line endings
# On Windows
dos2unix build.ps1

# Or use PowerShell
(Get-Content build.ps1) -replace "`r`n", "`n" | Set-Content build.ps1
```

---

## PowerShell Issues

### "Module not found"

**Error Message:**

```none
Cannot find module PowerBuild.psm1
```

**Solutions:**

```powershell
# Check current directory
Get-ChildItem PowerBuild.psm1

# Import with full path
Import-Module "C:\full\path\PowerBuild.psm1"

# Or from script directory
$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
Import-Module "$scriptDir\PowerBuild.psm1"
```

---

### "Execution policy prevents script"

**Error Message:**

```none
cannot be loaded because running scripts is disabled
```

**Solutions:**

```powershell
# Check current policy
Get-ExecutionPolicy

# Set to allow scripts
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser

# Or run single script
powershell -ExecutionPolicy Bypass -File build.ps1
```

---

### "PowerShell version too old"

**Symptom:** Strange syntax errors, features not working

**Solutions:**

```powershell
# Check version
$PSVersionTable.PSVersion

# Update PowerShell
# Windows
choco install powershell-core

# Or download from
# https://github.com/PowerShell/PowerShell/releases
```

---

## Output Issues

### "Executable not created"

**Problem:** Build completes but no .exe file

**Solutions:**

```powershell
# Verify output directory
$outDir = "./build"
Get-ChildItem $outDir -Recurse

# Check if build really succeeded
try {
    $build.Build($outDir)
    Write-Host "Build returned successfully"
} catch {
    Write-Host "Build failed: $_"
}

# Look for partial files
Get-ChildItem $outDir -Filter "*.o"
```

---

### "File locked error"

**Error Message:**

```none
The file is in use
```

**Causes:**

- Output file still running
- Antivirus scanning file
- Another process using file

**Solutions:**

```powershell
# Kill process using executable
Stop-Process -Name "MyApp" -ErrorAction SilentlyContinue

# Clean before rebuild
Remove-Item "./build/*" -Force -ErrorAction SilentlyContinue

# Retry build
$build.Build("./build")
```

---

## Validation Issues

### "Validation reports errors"

**Problem:** ValidateSetup() reports errors before building

**Solutions:**

```powershell
$validation = $build.ValidateSetup()

Write-Host "Validation Results:"
Write-Host "  Valid: $($validation.Valid)"

# Show all errors
if ($validation.Errors.Count -gt 0) {
    Write-Host "  Errors:"
    $validation.Errors | ForEach-Object { 
        Write-Host "    ✗ $_" -ForegroundColor Red
        
        # Specific fixes
        if ($_ -like "*Project name*") {
            $build.SetProjectName("MyApp")
        }
        elseif ($_ -like "*language*") {
            $build.SetLanguage("C++")
        }
        elseif ($_ -like "*Compiler*") {
            $build.SetCompiler("g++")
        }
    }
}

# Show all warnings
if ($validation.Warnings.Count -gt 0) {
    Write-Host "  Warnings:"
    $validation.Warnings | ForEach-Object { 
        Write-Host "    ⚠ $_" -ForegroundColor Yellow
    }
}
```

---

## Debugging Steps

### Step-by-Step Debug

```powershell
Import-Module ./PowerBuild.psm1

$build = [PowerBuild]::new()
Write-Host "1. Created instance"

$build.SetProjectName("DebugApp")
Write-Host "2. Set project name: $($build.GetProjectName())"

$build.SetLanguage("C++")
Write-Host "3. Set language: $($build.GetLanguage())"

$build.SetCompiler("g++")
Write-Host "4. Set compiler: $($build.GetCompiler())"

$build.SetVerbose($true)
Write-Host "5. Enabled verbose"

$build.AddSourcePath("./src")
Write-Host "6. Added source path"

$sources = $build.GetSourcePaths()
Write-Host "7. Source paths: $sources"

$validation = $build.ValidateSetup()
Write-Host "8. Validation: $(if ($validation.Valid) { 'VALID' } else { 'INVALID' })"

if ($validation.Valid) {
    $build.Build("./build")
    Write-Host "9. Build complete"
} else {
    Write-Host "9. Validation failed:"
    $validation.Errors | ForEach-Object { Write-Host "   - $_" }
}
```

---

## Getting Help

1. **Enable verbose mode** - Shows all details
2. **Check validation** - Catches most issues early
3. **Review examples** - See EXAMPLES.md for working code
4. **Test individually** - Compile single file with compiler directly
5. **Check compiler directly** - Run `g++ --help` to verify compiler works

---

## Still Having Issues?

1. **Collect information:**

   ```powershell
   Write-Host "PowerShell Version: $($PSVersionTable.PSVersion)"
   Write-Host "OS: $(if ($IsWindows) { 'Windows' } elseif ($IsLinux) { 'Linux' } else { 'macOS' })"
   $build.GetCompiler()
   $build.GetOS()
   ```

2. **Run with verbose:**

   ```powershell
   $build.SetVerbose($true)
   $build.Build("./build")
   ```

3. **Validate configuration:**

   ```powershell
   $v = $build.ValidateSetup()
   $v | select * | Format-Table
   ```

4. **Test compiler directly:**

   ```bash
   g++ -v -c test.cpp
   ```
