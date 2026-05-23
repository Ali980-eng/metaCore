# Real-World Examples

Complete, working examples for different scenarios.

## Example 1: Simple C++ Console Application

**Project Structure:**

```none
ConsoleApp/
├── src/
│   └── main.cpp
├── include/
├── PowerBuild.psm1
└── build.ps1
```

**src/main.cpp:**

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
```

**build.ps1:**

```powershell
#!/usr/bin/env pwsh

Import-Module ./PowerBuild.psm1 -Force

$build = [PowerBuild]::new()
$build.SetVerbose($true)
$build.SetProjectName("ConsoleApp")
$build.SetLanguage("C++")
$build.SetCompiler("g++")

$build.AddSourcePath("./src")

if (-not (Test-Path "./build")) {
    New-Item -ItemType Directory -Path "./build" | Out-Null
}

$build.Build("./build")

if ($LASTEXITCODE -eq 0) {
    Write-Host "✓ Build successful - run: ./build/ConsoleApp.exe"
}
```

**Run:**

```powershell
cd ConsoleApp
.\build.ps1
.\build\ConsoleApp.exe
```

---

## Example 2: C with Multiple Source Files

**Project Structure:**

```none
CLibrary/
├── src/
│   ├── main.c
│   ├── math.c
│   └── utils.c
├── include/
│   ├── math.h
│   └── utils.h
└── build.ps1
```

**build.ps1:**

```powershell
#!/usr/bin/env pwsh

Import-Module ./PowerBuild.psm1 -Force

$build = [PowerBuild]::new()
$build.SetVerbose($true)
$build.SetProjectName("CLibrary")
$build.SetLanguage("C")
$build.SetCompiler("gcc")

$build.AddSourcePath("./src")
$build.AddIncludePath("./include")

$buildDir = "./build"
if (-not (Test-Path $buildDir)) {
    New-Item -ItemType Directory -Path $buildDir | Out-Null
}

try {
    $build.Build($buildDir)
    Write-Host "✓ C library built successfully" -ForegroundColor Green
} catch {
    Write-Host "✗ Build failed: $_" -ForegroundColor Red
}
```

---

## Example 3: Debug vs Release Builds

**build.ps1:**

```powershell
#!/usr/bin/env pwsh

Import-Module ./PowerBuild.psm1 -Force

function Build-Target {
    param([string]$target)
    
    $build = [PowerBuild]::new()
    $build.SetVerbose($true)
    $build.SetProjectName("MyApp")
    $build.SetLanguage("C++")
    $build.SetCompiler("g++")
    
    $build.AddSourcePath("./src")
    $build.AddIncludePath("./include")
    
    $outDir = "./build/$target"
    if (-not (Test-Path $outDir)) {
        New-Item -ItemType Directory -Path $outDir -Force | Out-Null
    }
    
    Write-Host "Building $target..."
    
    try {
        $build.Build($outDir)
        Write-Host "✓ $target build successful" -ForegroundColor Green
        return $true
    } catch {
        Write-Host "✗ $target build failed: $_" -ForegroundColor Red
        return $false
    }
}

# Build both
$debugOK = Build-Target "Debug"
$releaseOK = Build-Target "Release"

if ($debugOK -and $releaseOK) {
    Write-Host ""
    Write-Host "Summary:" -ForegroundColor Cyan
    Write-Host "  Debug:   ./build/Debug/MyApp.exe"
    Write-Host "  Release: ./build/Release/MyApp.exe"
}
```

**Run:**

```powershell
.\build.ps1
# Outputs both:
# ./build/Debug/MyApp.exe
# ./build/Release/MyApp.exe
```

---

## Example 4: C# .NET Application

**Project Structure:**

```none
DotNetApp/
├── src/
│   ├── Program.cs
│   ├── Calculator.cs
│   └── Utils.cs
└── build.ps1
```

**build.ps1:**

```powershell
#!/usr/bin/env pwsh

Import-Module ./PowerBuild.psm1 -Force

$build = [PowerBuild]::new()
$build.SetVerbose($true)
$build.SetProjectName("DotNetApp")
$build.SetLanguage("CSharp")
$build.SetCompiler("csc")

$build.AddSourcePath("./src")

$buildDir = "./build"
if (-not (Test-Path $buildDir)) {
    New-Item -ItemType Directory -Path $buildDir | Out-Null
}

$build.Build($buildDir)

if (Test-Path "$buildDir/DotNetApp.exe") {
    Write-Host "✓ .NET app compiled: $buildDir/DotNetApp.exe"
    Write-Host "  Run with: dotnet $buildDir/DotNetApp.exe"
}
```

---

## Example 5: Python Project

**Project Structure:**

```none
PythonApp/
├── src/
│   ├── main.py
│   ├── helpers.py
│   └── config.py
└── build.ps1
```

**build.ps1:**

```powershell
#!/usr/bin/env pwsh

Import-Module ./PowerBuild.psm1 -Force

$build = [PowerBuild]::new()
$build.SetVerbose($true)
$build.SetProjectName("PythonApp")
$build.SetLanguage("Python")
$build.SetCompiler("python")

$build.AddSourcePath("./src")

# Validate Python environment
$validation = $build.ValidateSetup()
if ($validation.Valid) {
    Write-Host "✓ Python environment validated"
    Write-Host ""
    Write-Host "To run your Python app:"
    Write-Host "  python ./src/main.py"
} else {
    Write-Host "✗ Validation failed:"
    $validation.Errors | ForEach-Object { Write-Host "  - $_" }
}
```

**Run:**

```powershell
.\build.ps1
python ./src/main.py
```

---

## Example 6: Mixed Languages Project

**Project Structure:**

```none
MixedProject/
├── cpp/
│   ├── src/
│   └── build.ps1
├── csharp/
│   ├── src/
│   └── build.ps1
└── python/
    └── src/
```

**build.ps1 (Master):**

```powershell
#!/usr/bin/env pwsh

Write-Host "Building mixed language project..." -ForegroundColor Cyan

# Build C++ library
Write-Host ""
Write-Host "Step 1: Building C++ library..." -ForegroundColor Yellow
Push-Location ./cpp
.\build.ps1
if ($LASTEXITCODE -ne 0) {
    Write-Host "C++ build failed!" -ForegroundColor Red
    Pop-Location
    exit 1
}
Pop-Location

# Build C# wrapper
Write-Host ""
Write-Host "Step 2: Building C# wrapper..." -ForegroundColor Yellow
Push-Location ./csharp
.\build.ps1
if ($LASTEXITCODE -ne 0) {
    Write-Host "C# build failed!" -ForegroundColor Red
    Pop-Location
    exit 1
}
Pop-Location

# Validate Python
Write-Host ""
Write-Host "Step 3: Validating Python..." -ForegroundColor Yellow
Import-Module ../PowerBuild.psm1
$py = [PowerBuild]::new()
$py.SetProjectName("MainApp")
$py.SetLanguage("Python")
$py.AddSourcePath("./python/src")

$validation = $py.ValidateSetup()
if ($validation.Valid) {
    Write-Host "✓ Python environment OK"
} else {
    Write-Host "✓ Python validation: $(($validation.Errors -join ", "))"
}

Write-Host ""
Write-Host "✓ All builds completed successfully!" -ForegroundColor Green
```

---

## Example 7: Large Project with Many Files

**Project Structure:**

```none
LargeProject/
├── src/
│   ├── core/
│   │   ├── main.cpp
│   │   ├── engine.cpp
│   │   └── renderer.cpp
│   ├── utils/
│   │   ├── logger.cpp
│   │   ├── config.cpp
│   │   └── math.cpp
│   └── io/
│       ├── file.cpp
│       └── network.cpp
├── include/
│   ├── core/
│   ├── utils/
│   └── io/
└── build.ps1
```

**build.ps1:**

```powershell
#!/usr/bin/env pwsh

Import-Module ./PowerBuild.psm1 -Force

$build = [PowerBuild]::new()
$build.SetVerbose($false)  # Disable for cleaner output with many files
$build.SetProjectName("LargeProject")
$build.SetLanguage("C++")
$build.SetCompiler("g++")

# Add all source subdirectories
Write-Host "Configuring build..."
$build.AddSourcePath("./src/core")
$build.AddSourcePath("./src/utils")
$build.AddSourcePath("./src/io")

# Add all include subdirectories
$build.AddIncludePath("./include")
$build.AddIncludePath("./include/core")
$build.AddIncludePath("./include/utils")
$build.AddIncludePath("./include/io")

$buildDir = "./build"
if (-not (Test-Path $buildDir)) {
    New-Item -ItemType Directory -Path $buildDir | Out-Null
}

Write-Host "Starting build..."
$startTime = Get-Date

try {
    $build.Build($buildDir)
    $endTime = Get-Date
    $duration = ($endTime - $startTime).TotalSeconds
    
    Write-Host ""
    Write-Host "✓ Build successful in $([Math]::Round($duration, 2)) seconds" -ForegroundColor Green
    
    $exePath = "$buildDir/LargeProject.exe"
    $size = (Get-Item $exePath).Length / 1GB
    Write-Host "  Output: $exePath"
    Write-Host "  Size: $([Math]::Round($size, 2)) MB"
    
} catch {
    Write-Host "✗ Build failed: $_" -ForegroundColor Red
    exit 1
}
```

---

## Example 8: Automated Testing After Build

**build.ps1:**

```powershell
#!/usr/bin/env pwsh

Import-Module ./PowerBuild.psm1 -Force

Write-Host "Building and testing..." -ForegroundColor Cyan

$build = [PowerBuild]::new()
$build.SetVerbose($true)
$build.SetProjectName("TestApp")
$build.SetLanguage("C++")
$build.SetCompiler("g++")

$build.AddSourcePath("./src")

$buildDir = "./build"
if (-not (Test-Path $buildDir)) {
    New-Item -ItemType Directory -Path $buildDir | Out-Null
}

# Build
Write-Host ""
Write-Host "Step 1: Building..." -ForegroundColor Yellow
try {
    $build.Build($buildDir)
    Write-Host "✓ Build successful" -ForegroundColor Green
} catch {
    Write-Host "✗ Build failed" -ForegroundColor Red
    exit 1
}

# Test
Write-Host ""
Write-Host "Step 2: Running tests..." -ForegroundColor Yellow

$exePath = "$buildDir/TestApp.exe"
if (Test-Path $exePath) {
    & $exePath
    if ($LASTEXITCODE -eq 0) {
        Write-Host "✓ Tests passed" -ForegroundColor Green
    } else {
        Write-Host "✗ Tests failed with exit code $LASTEXITCODE" -ForegroundColor Red
        exit 1
    }
} else {
    Write-Host "✗ Executable not found" -ForegroundColor Red
    exit 1
}

Write-Host ""
Write-Host "✓ Build and tests completed successfully" -ForegroundColor Green
```

---

## Example 9: Version Management

**build.ps1:**

```powershell
#!/usr/bin/env pwsh

Import-Module ./PowerBuild.psm1 -Force

$build = [PowerBuild]::new()
$build.SetProjectName("VersionedApp")
$build.SetLanguage("C++")
$build.SetCompiler("g++")

# Set version
$build.mini_version(2)  # Version 1.2
Write-Host "Building version $($build.GetVersion()).$($build.GetMiniVersion())"

$build.AddSourcePath("./src")

$buildDir = "./build/v$($build.GetVersion())_$($build.GetMiniVersion())"
if (-not (Test-Path $buildDir)) {
    New-Item -ItemType Directory -Path $buildDir -Force | Out-Null
}

$build.Build($buildDir)
Write-Host "Version $($build.GetVersion()).$($build.GetMiniVersion()) built in $buildDir"
```

---

## Example 10: Custom Validation Script

**build.ps1:**

```powershell
#!/usr/bin/env pwsh

Import-Module ./PowerBuild.psm1 -Force

function Validate-BuildEnvironment {
    Write-Host "Validating build environment..." -ForegroundColor Cyan
    
    $build = [PowerBuild]::new()
    $build.SetProjectName("ValidatedApp")
    $build.SetLanguage("C++")
    $build.SetCompiler("g++")
    $build.AddSourcePath("./src")
    
    $validation = $build.ValidateSetup()
    
    Write-Host "Validation Results:"
    Write-Host "  Valid: $($validation.Valid)"
    
    if ($validation.Errors.Count -gt 0) {
        Write-Host "  Errors:"
        $validation.Errors | ForEach-Object { Write-Host "    ✗ $_" -ForegroundColor Red }
        return $false
    }
    
    if ($validation.Warnings.Count -gt 0) {
        Write-Host "  Warnings:"
        $validation.Warnings | ForEach-Object { Write-Host "    ⚠ $_" -ForegroundColor Yellow }
    }
    
    Write-Host "  ✓ Environment is ready" -ForegroundColor Green
    return $true
}

# Validate first
if (-not (Validate-BuildEnvironment)) {
    exit 1
}

# If valid, build
Write-Host ""
Write-Host "Starting build..." -ForegroundColor Green

$build = [PowerBuild]::new()
$build.SetVerbose($true)
$build.SetProjectName("ValidatedApp")
$build.SetLanguage("C++")
$build.SetCompiler("g++")
$build.AddSourcePath("./src")

$build.Build("./build")
```

---

All these examples are fully functional. Copy the build.ps1 content to your project and adjust paths as needed.
