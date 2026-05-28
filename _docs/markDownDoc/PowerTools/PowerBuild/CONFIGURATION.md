# Configuration Guide

Advanced configuration options and techniques.

## Basic Configuration

### Minimal Configuration

```powershell
$build = [PowerBuild]::new()
$build.SetProjectName("App")
$build.SetLanguage("C++")
$build.SetCompiler("g++")
$build.AddSourcePath("./src")
$build.Build("./build")
```

### Complete Configuration

```powershell
$build = [PowerBuild]::new()

# Project info
$build.SetProjectName("MyApp")
$build.mini_version(1)

# Build configuration
$build.SetLanguage("C++")
$build.SetCompiler("g++")
$build.SetVerbose($true)

# Paths
$build.AddSourcePath("./src")
$build.AddSourcePath("./lib")
$build.AddIncludePath("./include")
$build.AddIncludePath("./third_party")

# Validate
$validation = $build.ValidateSetup()
if ($validation.Valid) {
    $build.Build("./build")
}
```

---

## Compiler Configuration

### Setting Compiler Paths

**Auto-detect (recommended):**

```powershell
$build.SetCompiler("g++")
# System automatically finds it in PATH
```

**Manual path:**

```powershell
$build.SetCompilerPath("g++", "C:\MinGW\bin\g++.exe")
$build.SetCompiler("g++")
```

**Get detected path:**

```powershell
$path = $build.GetCompilerPath("g++")
Write-Host "Using: $path"
```

### Compiler Selection by OS

```powershell
$osType = $build.GetOS()

if ($osType -eq "Windows") {
    # Try MSVC first
    try {
        $build.SetCompiler("cl.exe")
        $build.GetCompilerPath("cl.exe") | Out-Null
    } catch {
        # Fall back to MinGW
        $build.SetCompiler("g++")
    }
} else {
    # Linux/macOS
    $build.SetCompiler("g++")
}
```

### Multiple Compiler Support

```powershell
$compilers = @{
    "g++" = "gcc/g++ compiler"
    "clang++" = "Clang compiler"
    "cl.exe" = "MSVC compiler"
}

foreach ($compiler in $compilers.Keys) {
    try {
        $path = $build.GetCompilerPath($compiler)
        Write-Host "✓ $compiler found at $path"
    } catch {
        Write-Host "✗ $compiler not found"
    }
}
```

---

## Path Configuration

### Source Paths

```powershell
# Single directory
$build.AddSourcePath("./src")

# Multiple directories
$build.AddSourcePath("./src")
$build.AddSourcePath("./lib")
$build.AddSourcePath("./modules")

# Get all paths
$paths = $build.GetSourcePaths()
$paths | ForEach-Object { Write-Host "Source: $_" }
```

### Include Paths

```powershell
# Local includes
$build.AddIncludePath("./include")

# Third-party libraries
$build.AddIncludePath("./third_party/include")
$build.AddIncludePath("./third_party/boost")

# System paths (usually automatic)
# But can be added explicitly for special cases
$build.AddIncludePath("/usr/local/include")
```

### Relative vs Absolute Paths

```powershell
# Relative (recommended)
$build.AddSourcePath("./src")
$build.AddIncludePath("./include")

# Absolute (use when needed)
$build.AddSourcePath("C:\Projects\MyApp\src")
$build.AddIncludePath("C:\SDK\include")

# UNC paths (network)
$build.AddSourcePath("\\server\share\code\src")
```

---

## Target Configuration

### Single Target

```powershell
$config = @{
    flags = "-Wall -g -O0"
    output = "./build"
    standard = "c++17"
}

$build.addTargetConfig("Default", $config)
```

### Multiple Targets

```powershell
# Debug configuration
$build.addTargetConfig("Debug", @{
    flags = "-g -O0 -DDEBUG"
    output = "./build/debug"
    opt = "none"
    warnings = "all"
})

# Release configuration
$build.addTargetConfig("Release", @{
    flags = "-O3 -DNDEBUG"
    output = "./build/release"
    opt = "full"
    warnings = "pedantic"
})

# Development configuration
$build.addTargetConfig("Dev", @{
    flags = "-g -O1 -Wall"
    output = "./build/dev"
    opt = "partial"
    warnings = "all"
})
```

### Accessing Target Configurations

```powershell
# Get specific target
$debugConfig = $build.GetTargetConfig("Debug")
Write-Host "Debug flags: $($debugConfig.flags)"

# Update single value
$build.replaceConfig("Debug", "flags", "-g -O2")

# Get all values
$config = $build.GetTargetConfig("Debug")
$config.Keys | ForEach-Object { 
    Write-Host "$($_): $($config[$_])" 
}
```

### Remove and Clear

```powershell
# Remove specific target
$build.removeTargetConfig("Dev")

# Clear all targets
$build.clearAllConfigs()
```

---

## Language-Specific Configuration

### C++ Configuration

```powershell
$build.SetLanguage("C++")
$build.SetCompiler("g++")

# Add include paths for headers
$build.AddIncludePath("./include")

# Build
$build.Build("./build")
```

### C Configuration

```powershell
$build.SetLanguage("C")
$build.SetCompiler("gcc")

# Similar to C++
$build.AddSourcePath("./src")
$build.AddIncludePath("./include")

$build.Build("./build")
```

### C# Configuration

```powershell
$build.SetLanguage("CSharp")
$build.SetCompiler("csc")

# Source paths are required
$build.AddSourcePath("./src")

$build.Build("./build")
```

### Python Configuration

```powershell
$build.SetLanguage("Python")
$build.SetCompiler("python")

# Just verify files exist
$build.AddSourcePath("./src")

$validation = $build.ValidateSetup()
if ($validation.Valid) {
    Write-Host "Python environment ready"
}
```

---

## Output Configuration

### Output Directory

```powershell
# Simple output
$build.Build("./build")

# Version-specific
$build.Build("./build/v1.0")

# Debug/Release specific
$build.Build("./build/debug")
$build.Build("./build/release")

# Timestamped
$timestamp = Get-Date -Format "yyyyMMdd_HHmmss"
$build.Build("./build/$timestamp")
```

### Output File Names

Output format depends on OS and language:

**Windows:**

- C++: `ProjectName.exe`
- C: `ProjectName.exe`
- C#: `ProjectName.exe`

**Linux/macOS:**

- C++: `ProjectName` (no extension)
- C: `ProjectName` (no extension)
- C#: `ProjectName.exe`

---

## Logging Configuration

### Verbose Mode

```powershell
# Enable verbose logging
$build.SetVerbose($true)

# Now all operations show details:
# [2026-04-05 14:23:45] Compiler path set: g++ = /usr/bin/g++
# [2026-04-05 14:23:46] Starting build for project: MyApp
# [2026-04-05 14:23:47] Compiling: main.cpp
# etc.
```

### Conditional Verbose

```powershell
# Enable based on environment variable
$verbose = [Environment]::GetEnvironmentVariable("VERBOSE") -eq "1"
$build.SetVerbose($verbose)

# Or command line parameter
param([switch]$Verbose)
$build.SetVerbose($Verbose)
```

### Manual Logging

```powershell
$build.SetVerbose($true)

$build.WriteLog("Initializing build system")
$build.WriteLog("Using compiler: $($build.GetCompiler())")
$build.WriteLog("Adding source paths")

$build.Build("./build")

$build.WriteLog("Build completed")
```

---

## Validation Configuration

### Automatic Validation

```powershell
$validation = $build.ValidateSetup()

if ($validation.Valid) {
    Write-Host "✓ Configuration valid"
    $build.Build("./build")
} else {
    Write-Host "✗ Configuration errors:"
    $validation.Errors | ForEach-Object { Write-Host "  - $_" }
    exit 1
}
```

### Pre-Build Checks

```powershell
function Test-BuildSetup {
    param([Parameter(ValueFromPipeline)]$builder)
    
    $validation = $builder.ValidateSetup()
    
    # Check specific conditions
    if (-not (Test-Path "./src")) {
        Write-Host "✗ Source directory missing"
        return $false
    }
    
    if ($validation.Warnings.Count -gt 0) {
        Write-Host "⚠ Warnings found:"
        $validation.Warnings | ForEach-Object { Write-Host "  - $_" }
    }
    
    return $validation.Valid
}

$build | Test-BuildSetup
```

---

## Project Setup Templates

### Template 1: Small Project

```powershell
$build = [PowerBuild]::new()
$build.SetProjectName("SmallApp")
$build.SetLanguage("C++")
$build.SetCompiler("g++")
$build.AddSourcePath("./src")
$build.Build("./build")
```

### Template 2: Medium Project

```powershell
$build = [PowerBuild]::new()
$build.SetVerbose($true)
$build.SetProjectName("MediumApp")
$build.SetLanguage("C++")
$build.SetCompiler("g++")

$build.AddSourcePath("./src")
$build.AddSourcePath("./lib")
$build.AddIncludePath("./include")

$validation = $build.ValidateSetup()
if ($validation.Valid) {
    $build.Build("./build")
}
```

### Template 3: Large Project

```powershell
$build = [PowerBuild]::new()
$build.SetVerbose($false)
$build.SetProjectName("LargeApp")
$build.SetLanguage("C++")
$build.SetCompiler("g++")

# Multiple sources
$build.AddSourcePath("./src/core")
$build.AddSourcePath("./src/utils")
$build.AddSourcePath("./src/io")

# Multiple includes
$build.AddIncludePath("./include")
$build.AddIncludePath("./include/core")
$build.AddIncludePath("./third_party")

# Configure targets
$build.addTargetConfig("Debug", @{ flags = "-g -O0"; output = "./build/debug" })
$build.addTargetConfig("Release", @{ flags = "-O3"; output = "./build/release" })

# Build
$validation = $build.ValidateSetup()
if ($validation.Valid) {
    $build.Build("./build/release")
} else {
    $validation.Errors | ForEach-Object { Write-Host "✗ $_" }
}
```

---

## Configuration Best Practices

1. **Always validate** before building
2. **Use relative paths** for portability
3. **Enable verbose** during development
4. **Create separate targets** for Debug/Release
5. **Check compiler availability** early
6. **Handle errors** gracefully
7. **Test on target platform** before releasing
8. **Document your configuration** in comments
9. **Use meaningful target names**
10. **Keep paths organized** in project structure
