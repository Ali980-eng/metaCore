# Usage Guide

How to use PowerBuild in your projects.

## Basic Usage Flow

### 1. Create Instance

```powershell
Import-Module ./PowerBuild.psm1

$build = [PowerBuild]::new()
```

### 2. Configure Project

```powershell
$build.SetProjectName("HelloWorld")
$build.SetLanguage("C++")
$build.SetCompiler("g++")
```

### 3. Add Paths

```powershell
$build.AddSourcePath("./src")
$build.AddIncludePath("./include")
```

### 4. Validate (Optional but Recommended)

```powershell
$validation = $build.ValidateSetup()
if (-not $validation.Valid) {
    Write-Host "Configuration errors:"
    $validation.Errors | ForEach-Object { Write-Host "  - $_" }
    exit 1
}
```

### 5. Build

```powershell
$build.Build("./build")
```

### 6. Check Results

```powershell
if (Test-Path "./build/HelloWorld.exe") {
    Write-Host "Build successful!"
} else {
    Write-Host "Build failed!"
}
```

---

## Complete Example Scripts

### Example 1: Simple C++ Build

```powershell
#!/usr/bin/env pwsh

Import-Module ./PowerBuild.psm1 -Force

# Create builder
$build = [PowerBuild]::new()

# Configure
$build.SetProjectName("MyApp")
$build.SetLanguage("C++")
$build.SetCompiler("g++")

# Add paths
$build.AddSourcePath("./src")
$build.AddIncludePath("./include")

# Create output directory
$outDir = "./build"
if (-not (Test-Path $outDir)) {
    New-Item -ItemType Directory -Path $outDir | Out-Null
}

# Build
try {
    $build.Build($outDir)
    Write-Host "✓ Build successful: $outDir/MyApp.exe" -ForegroundColor Green
} catch {
    Write-Host "✗ Build failed: $_" -ForegroundColor Red
    exit 1
}
```

### Example 2: Verbose Building

```powershell
$build = [PowerBuild]::new()
$build.SetVerbose($true)  # Show all details

$build.SetProjectName("DebugApp")
$build.SetLanguage("C++")
$build.SetCompiler("g++")

$build.AddSourcePath("./src")
$build.Build("./build")
```

### Example 3: With Error Handling

```powershell
$build = [PowerBuild]::new()
$build.SetVerbose($true)

try {
    $build.SetProjectName("TestApp")
    $build.SetLanguage("C++")
    $build.SetCompiler("g++")
    $build.AddSourcePath("./src")
    
    # Validate before building
    $validation = $build.ValidateSetup()
    if (-not $validation.Valid) {
        throw "Setup validation failed:`n$($validation.Errors -join "`n")"
    }
    
    # Create build directory
    $buildDir = "./build"
    if (-not (Test-Path $buildDir)) {
        New-Item -ItemType Directory -Path $buildDir -Force | Out-Null
    }
    
    # Build
    $build.Build($buildDir)
    Write-Host "✓ Build completed" -ForegroundColor Green
    
} catch {
    Write-Host "✗ Error: $_" -ForegroundColor Red
    Write-Host "Details: $($_.InvocationInfo.Line)" -ForegroundColor Yellow
    exit 1
}
```

### Example 4: C and C# Projects

```powershell
# Building C project
$c_build = [PowerBuild]::new()
$c_build.SetProjectName("C_Program")
$c_build.SetLanguage("C")
$c_build.SetCompiler("gcc")
$c_build.AddSourcePath("./c_src")
$c_build.Build("./build")

# Building C# project
$cs_build = [PowerBuild]::new()
$cs_build.SetProjectName("DotNetApp")
$cs_build.SetLanguage("CSharp")
$cs_build.SetCompiler("csc")
$cs_build.AddSourcePath("./cs_src")
$cs_build.Build("./build")
```

### Example 5: Python Project

```powershell
$py_build = [PowerBuild]::new()
$py_build.SetVerbose($true)

$py_build.SetProjectName("PythonApp")
$py_build.SetLanguage("Python")
$py_build.SetCompiler("python")
$py_build.AddSourcePath("./src")

$py_build.Build("./build")
# Output: Found X Python files, ready to run with: python main.py
```

---

## Multiple Language Projects

If you have multiple languages in one project:

```powershell
# Build C++ part
$cpp_build = [PowerBuild]::new()
$cpp_build.SetProjectName("LibCore")
$cpp_build.SetLanguage("C++")
$cpp_build.SetCompiler("g++")
$cpp_build.AddSourcePath("./core")
$cpp_build.Build("./build")

# Build C# wrapper
$cs_build = [PowerBuild]::new()
$cs_build.SetProjectName("Wrapper")
$cs_build.SetLanguage("CSharp")
$cs_build.SetCompiler("csc")
$cs_build.AddSourcePath("./wrapper")
$cs_build.Build("./build")
```

---

## Target-Specific Builds

### Debug vs Release

```powershell
$build = [PowerBuild]::new()
$build.SetProjectName("MyApp")
$build.SetLanguage("C++")
$build.SetCompiler("g++")

# Configure Debug target
$debugConfig = @{
    flags = "-g -O0 -DDEBUG"
    output = "./build/debug"
}
$build.addTargetConfig("Debug", $debugConfig)

# Configure Release target
$releaseConfig = @{
    flags = "-O3 -DRELEASE -Wall"
    output = "./build/release"
}
$build.addTargetConfig("Release", $releaseConfig)

$build.AddSourcePath("./src")

# Build Debug
$build.Build("./build/debug")
Write-Host "Debug build complete"

# Build Release
$build.Build("./build/release")
Write-Host "Release build complete"
```

---

## Handling Different Paths

### Multiple Source Directories

```powershell
$build = [PowerBuild]::new()
$build.SetProjectName("LargeProject")
$build.SetLanguage("C++")
$build.SetCompiler("g++")

# Multiple source locations
$build.AddSourcePath("./src/core")
$build.AddSourcePath("./src/utils")
$build.AddSourcePath("./src/lib")

# Multiple include locations
$build.AddIncludePath("./include")
$build.AddIncludePath("./include/core")
$build.AddIncludePath("./third_party/include")

$build.Build("./build")
```

---

## Working with Different Compilers

### Auto-Detect Compiler

System automatically finds compiler in PATH:

```powershell
$build = [PowerBuild]::new()
$build.SetCompiler("g++")  # System finds it automatically

# Get the path it found
$compilerPath = $build.GetCompilerPath("g++")
Write-Host "Using compiler: $compilerPath"
```

### Manual Compiler Path

```powershell
$build = [PowerBuild]::new()
$build.SetCompilerPath("g++", "C:\MinGW\bin\g++.exe")
$build.SetProjectName("App")
$build.SetLanguage("C++")
$build.SetCompiler("g++")
$build.Build("./build")
```

### Switch Between Compilers

```powershell
$osType = (Get-Item -Path ".").Name

if ($osType -like "*Linux*" -or $osType -like "*WSL*") {
    $compiler = "g++"
} else {
    # Try MSVC first, fall back to MinGW
    try {
        $build = [PowerBuild]::new()
        $build.GetCompilerPath("cl.exe") | Out-Null
        $compiler = "cl.exe"
    } catch {
        $compiler = "g++"
    }
}

$build = [PowerBuild]::new()
$build.SetCompiler($compiler)
# ... rest of configuration
```

---

## Logging and Diagnostics

### Enable Verbose Output

```powershell
$build = [PowerBuild]::new()
$build.SetVerbose($true)

$build.SetProjectName("App")
$build.SetLanguage("C++")
$build.SetCompiler("g++")
$build.AddSourcePath("./src")

# Now all commands will be shown
$build.Build("./build")
```

### Custom Logging

```powershell
$build = [PowerBuild]::new()
$build.SetVerbose($true)

# Manually log information
$build.WriteLog("Starting build process")
$build.WriteLog("Compiler: $(build.GetCompiler())")

# Build operation logs will show with timestamps
$build.Build("./build")
```

### Validate Before Building

```powershell
$build = [PowerBuild]::new()
# ... configuration ...

$validation = $build.ValidateSetup()

Write-Host "Validation Status:"
Write-Host "  Valid: $($validation.Valid)"

if ($validation.Errors.Count -gt 0) {
    Write-Host "  Errors:"
    $validation.Errors | ForEach-Object { Write-Host "    - $_" }
}

if ($validation.Warnings.Count -gt 0) {
    Write-Host "  Warnings:"
    $validation.Warnings | ForEach-Object { Write-Host "    - $_" }
}
```

---

## Output Files

### Find Generated Executable

```powershell
$build = [PowerBuild]::new()
$build.SetProjectName("MyApp")
$build.SetLanguage("C++")
$build.SetCompiler("g++")
$build.AddSourcePath("./src")

$outDir = "./build"
New-Item -ItemType Directory -Path $outDir -Force | Out-Null

$build.Build($outDir)

# Find the executable
$exePath = "$outDir/MyApp.exe"
if (Test-Path $exePath) {
    Write-Host "Executable: $exePath"
    Write-Host "Size: $(Get-Item $exePath).Length bytes"
}
```

### Check Build Success

```powershell
try {
    $build.Build("./build")
    Write-Host "✓ Build succeeded" -ForegroundColor Green
    
    # Verify output exists
    $projectName = $build.GetProjectName()
    $outPath = "./build/$projectName.exe"
    
    if (Test-Path $outPath) {
        $size = (Get-Item $outPath).Length
        Write-Host "Output: $outPath ($size bytes)"
    }
} catch {
    Write-Host "✗ Build failed: $_" -ForegroundColor Red
}
```

---

## Cleaning Up

### Remove Build Artifacts

```powershell
$build = [PowerBuild]::new()

# Clean internal cache
$build.Clean()

# Or manually remove directory
if (Test-Path "./build") {
    Remove-Item "./build" -Recurse -Force
    Write-Host "Build directory cleaned"
}
```

---

## Tips and Tricks

### Reusable Build Function

```powershell
function Build-Project {
    param(
        [string]$name,
        [string]$language = "C++",
        [string]$compiler = "g++"
    )
    
    $build = [PowerBuild]::new()
    $build.SetVerbose($true)
    $build.SetProjectName($name)
    $build.SetLanguage($language)
    $build.SetCompiler($compiler)
    
    $build.AddSourcePath("./src")
    $build.AddIncludePath("./include")
    
    if (-not (Test-Path "./build")) {
        New-Item -ItemType Directory -Path "./build" | Out-Null
    }
    
    return $build.Build("./build")
}

# Usage
Build-Project -name "MyApp" -language "C++" -compiler "g++"
```

### Batch Building

```powershell
$projects = @("ProjectA", "ProjectB", "ProjectC")

foreach ($proj in $projects) {
    Write-Host "Building $proj..." -ForegroundColor Cyan
    
    $build = [PowerBuild]::new()
    $build.SetProjectName($proj)
    $build.SetLanguage("C++")
    $build.SetCompiler("g++")
    $build.AddSourcePath("./$proj/src")
    $build.AddIncludePath("./$proj/include")
    
    try {
        $build.Build("./$proj/build")
        Write-Host "✓ $proj completed" -ForegroundColor Green
    } catch {
        Write-Host "✗ $proj failed: $_" -ForegroundColor Red
    }
}
```
