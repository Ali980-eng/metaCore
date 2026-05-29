# PowerBuild Usage Examples

# Import the module
Import-Module ./PowerBuild.psm1 -Force

# =========== Example 1: C++ Build ===========
Write-Host "=== Example 1: C++ Build ===" -ForegroundColor Cyan

$builder = [PowerBuild]::new()
$builder.SetVerbose($true)
$builder.SetProjectName("MyApp")
$builder.SetLanguage("C++")
$builder.SetCompiler("g++")  # or "clang++" or "cl.exe" (MSVC)

# Set source paths
$builder.AddSourcePath("./src")
$builder.AddIncludePath("./include")

# Setup build directory
$outputDir = "./build"
if (-not (Test-Path $outputDir)) {
    New-Item -ItemType Directory -Path $outputDir | Out-Null
}

# Build
try {
    $builder.Build($outputDir)
} catch {
    Write-Host "Build error: $_" -ForegroundColor Red
}

# =========== Example 2: C Build ===========
Write-Host "`n=== Example 2: C Build ===" -ForegroundColor Cyan

$builder2 = [PowerBuild]::new()
$builder2.SetVerbose($true)
$builder2.SetProjectName("CProject")
$builder2.SetLanguage("C")
$builder2.SetCompiler("gcc")

$builder2.AddSourcePath("./c_src")
$builder2.AddIncludePath("./c_include")

try {
    $builder2.Build($outputDir)
} catch {
    Write-Host "Build error: $_" -ForegroundColor Red
}

# =========== Example 3: C# Build ===========
Write-Host "`n=== Example 3: C# Build ===" -ForegroundColor Cyan

$builder3 = [PowerBuild]::new()
$builder3.SetVerbose($true)
$builder3.SetProjectName("DotNetApp")
$builder3.SetLanguage("CSharp")
$builder3.SetCompiler("csc")

$builder3.AddSourcePath("./csharp_src")

try {
    $builder3.Build($outputDir)
} catch {
    Write-Host "Build error: $_" -ForegroundColor Red
}

# =========== System Information ===========
Write-Host "`n=== System Information ===" -ForegroundColor Cyan
Write-Host "Operating System: $($builder.GetOS())"

# =========== Setup Validation ===========
Write-Host "`n=== Setup Validation ===" -ForegroundColor Cyan
$validation = $builder.ValidateSetup()
if ($validation.Valid) {
    Write-Host "✓ Configuration is valid" -ForegroundColor Green
} else {
    foreach ($err in $validation.Errors) {
        Write-Host "✗ $err" -ForegroundColor Red
    }
}