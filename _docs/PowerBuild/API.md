# API Reference

Complete list of all methods and properties in PowerBuild.

## Object Creation

### new()

Creates a new PowerBuild instance.

```powershell
$build = [PowerBuild]::new()
```

**Returns**: PowerBuild instance

**Initializes**:

- projectPath to current directory
- osType to detected OS
- configMap as empty hashtable
- includePaths as empty array
- sourcePaths as empty array

---

## Project Configuration

### SetProjectName(string name)

Set the project name.

```powershell
$build.SetProjectName("MyApp")
```

**Parameter**: `name` - Project name (string)

**Returns**: void

**Notes**: Required before building.

---

### GetProjectName()

Get the current project name.

```powershell
$name = $build.GetProjectName()
```

**Returns**: string - Project name

---

### SetLanguage(string language)

Set the programming language.

```powershell
$build.SetLanguage("C++")
```

**Parameter**: `language` - One of: "C++", "C", "CSharp", "Python"

**Returns**: void

**Supported Languages**:

- "C++" - C++ compilation
- "C" - C compilation
- "CSharp" - C# compilation
- "Python" - Python validation

**Notes**: Required before building.

---

### GetLanguage()

Get the current language.

```powershell
$lang = $build.GetLanguage()
```

**Returns**: string - Programming language

---

### SetCompiler(string compiler)

Set the compiler executable name.

```powershell
$build.SetCompiler("g++")
```

**Parameter**: `compiler` - Compiler name: "g++", "gcc", "clang++", "clang", "csc", etc.

**Returns**: void

**Common Values**:

- "g++" - GNU C++ compiler
- "gcc" - GNU C compiler
- "clang++" - Clang C++ compiler
- "clang" - Clang C compiler
- "cl.exe" - MSVC C++ compiler
- "csc.exe" - C# compiler (Windows)
- "csc" - C# compiler (Linux)

**Notes**: Required before building.

---

### GetCompiler()

Get the current compiler name.

```powershell
$compiler = $build.GetCompiler()
```

**Returns**: string - Compiler name

---

## Path Configuration

### AddSourcePath(string path)

Add a source code directory.

```powershell
$build.AddSourcePath("./src")
$build.AddSourcePath("./lib")
```

**Parameter**: `path` - Directory path (string)

**Returns**: void

**Notes**:

- Can be called multiple times
- Paths are searched recursively
- At least one source path required

---

### GetSourcePaths()

Get all source paths.

```powershell
$paths = $build.GetSourcePaths()
```

**Returns**: string[] - Array of source paths

---

### AddIncludePath(string path)

Add a header/include directory.

```powershell
$build.AddIncludePath("./include")
$build.AddIncludePath("./third_party")
```

**Parameter**: `path` - Directory path (string)

**Returns**: void

**Notes**:

- Can be called multiple times
- Passed to compiler with -I flag
- Optional for some languages

---

### GetIncludePaths()

Get all include paths.

```powershell
$paths = $build.GetIncludePaths()
```

**Returns**: string[] - Array of include paths

---

## Version Management

### mini_version(double version)

Set minor version number.

```powershell
$build.mini_version(1.5)
```

**Parameter**: `version` - Version number (double)

**Returns**: void

---

### GetMiniVersion()

Get minor version.

```powershell
$miniVer = $build.GetMiniVersion()
```

**Returns**: double - Minor version

---

### GetVersion()

Get major version.

```powershell
$majorVer = $build.GetVersion()
```

**Returns**: double - Major version (default 1.0)

---

## Target Configuration

### addTargetConfig(string target, hashtable config)

Add configuration for a build target.

```powershell
$config = @{
    flags = "-g -O0"
    output = "./debug"
}
$build.addTargetConfig("Debug", $config)
```

**Parameters**:

- `target` - Target name (string): "Debug", "Release", etc.
- `config` - Configuration hashtable

**Returns**: void

**Example**:

```powershell
$debugConfig = @{
    flags = "-g -O0 -DDEBUG"
    output = "./build/debug"
    opt = "none"
}
$releaseConfig = @{
    flags = "-O3 -DRELEASE"
    output = "./build/release"
    opt = "full"
}
$build.addTargetConfig("Debug", $debugConfig)
$build.addTargetConfig("Release", $releaseConfig)
```

---

### GetTargetConfig(string target)

Get configuration for a target.

```powershell
$config = $build.GetTargetConfig("Debug")
Write-Host $config.flags
```

**Parameter**: `target` - Target name (string)

**Returns**: hashtable - Target configuration

---

### replaceTargetConfig(string target, hashtable config)

Replace entire target configuration.

```powershell
$newConfig = @{ flags = "-O2"; output = "./opt" }
$build.replaceTargetConfig("Debug", $newConfig)
```

**Parameters**:

- `target` - Target name (string)
- `config` - New configuration (hashtable)

**Returns**: void

**Throws**: Exception if target doesn't exist

---

### replaceConfig(string target, string key, value)

Update a single configuration value.

```powershell
$build.replaceConfig("Debug", "flags", "-g -O1")
```

**Parameters**:

- `target` - Target name (string)
- `key` - Configuration key (string)
- `value` - New value (any type)

**Returns**: void

**Throws**: Exception if target doesn't exist

---

### removeTargetConfig(string target)

Remove a target configuration.

```powershell
$build.removeTargetConfig("Debug")
```

**Parameter**: `target` - Target name (string)

**Returns**: void

**Throws**: Exception if target doesn't exist

---

### clearAllConfigs()

Clear all target configurations.

```powershell
$build.clearAllConfigs()
```

**Returns**: void

---

### writeTarget(string target, string key)

Display a configuration value.

```powershell
$build.writeTarget("Debug", "flags")
```

**Parameters**:

- `target` - Target name (string)
- `key` - Configuration key (string)

**Returns**: void

**Effect**: Prints value to console

**Throws**: Exception if target doesn't exist

---

## Build Operations

### SetVerbose(bool verbose)

Enable or disable verbose output.

```powershell
$build.SetVerbose($true)   # Enable detailed logging
$build.SetVerbose($false)  # Disable
```

**Parameter**: `verbose` - Enable verbose mode (bool)

**Returns**: void

**When Enabled**: Shows all compiler commands and timestamps

---

### SetCompilerPath(string compiler, string path)

Manually set compiler path.

```powershell
$build.SetCompilerPath("g++", "C:\MinGW\bin\g++.exe")
```

**Parameters**:

- `compiler` - Compiler name (string)
- `path` - Full path to compiler (string)

**Returns**: void

**Notes**: Overrides automatic detection

---

### GetCompilerPath(string compiler)

Find compiler path in system.

```powershell
$path = $build.GetCompilerPath("g++")
```

**Parameter**: `compiler` - Compiler name (string)

**Returns**: string - Full path to compiler

**Throws**: Exception if compiler not found

**Logic**:

1. Check cached paths
2. Search PATH using Get-Command (Windows) or which (Linux)
3. Return first found

---

### WriteLog(string message)

Write timestamped log message.

```powershell
$build.WriteLog("Starting compilation")
```

**Parameter**: `message` - Log message (string)

**Returns**: void

**Format**: `[YYYY-MM-DD HH:mm:ss] message`

**Notes**: Only outputs if verbose mode enabled

---

### ValidateSetup()

Validate build configuration before building.

```powershell
$validation = $build.ValidateSetup()
if ($validation.Valid) {
    Write-Host "Ready to build"
} else {
    $validation.Errors | ForEach-Object { Write-Host "Error: $_" }
}
```

**Returns**: hashtable with structure:

```powershell
@{
    Valid = $true|$false
    Errors = @("error1", "error2", ...)
    Warnings = @("warning1", "warning2", ...)
}
```

**Checks**:

- Project name is set
- Language is specified
- Compiler is specified
- Compiler is available in system
- At least one source path exists

**Warnings**:

- No source paths added

---

### Build(string outputPath)

Start the build process.

```powershell
$build.Build("./build")
```

**Parameter**: `outputPath` - Directory for output files (string)

**Returns**: void

**Process**:

1. Validate setup
2. Detect language
3. Call appropriate compile method
4. Generate output files

**Throws**: Exception on compilation errors

**Behavior by Language**:

- **C++**: Compiles .cpp files, links to executable
- **C**: Compiles .c files, links to executable
- **C#**: Compiles .cs files directly
- **Python**: Validates .py files exist

---

### Clean()

Clean build artifacts.

```powershell
$build.Clean()
```

**Returns**: void

**Effect**: Clears internal build cache

**Note**: Does not delete output directory

---

### GetOS()

Get detected operating system.

```powershell
$osType = $build.GetOS()
if ($osType -eq "Windows") {
    # Windows-specific code
}
```

**Returns**: string - "Windows" or "Linux"

---

## Special Methods

### replaceTarget(string target, string key, value)

Alias for replaceConfig (updates single value).

```powershell
$build.replaceTarget("Debug", "opt", "O2")
```

Same as `replaceConfig()`.

---

### clearConfigMap()

Clear all configurations (alias for clearAllConfigs).

```powershell
$build.clearConfigMap()
```

---

## Private Methods (Internal Use)

These methods are private and called internally:

- `CompileCpp(string outputPath)` - Compile C++ files
- `CompileC(string outputPath)` - Compile C files
- `CompileCSharp(string outputPath)` - Compile C# files
- `HandlePython(string outputPath)` - Handle Python files

---

## Property Access

Properties are hidden and accessed via methods:

```powershell
# Configuration
$build.SetProjectName($name)
$build.GetProjectName()

# Versions
$build.mini_version($version)
$build.GetMiniVersion()

# Paths
$build.AddSourcePath($path)
$build.GetSourcePaths()
```

Direct property access is not available (enforces encapsulation).
