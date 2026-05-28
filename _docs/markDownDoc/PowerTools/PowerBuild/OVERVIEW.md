# System Overview

## What is PowerBuild?

PowerBuild is a build system that compiles and links multiple programming languages using PowerShell. It handles the complexity of different compilers, paths, and configurations.

## Core Components

### Properties

Every PowerBuild instance has these hidden properties:

```none
projectName      - Name of your project
projectPath      - Path to project directory
language         - Programming language (C++, C, C#, Python)
compiler         - Compiler executable name (g++, gcc, csc, etc)
includePaths[]   - Array of header/include directories
sourcePaths[]    - Array of source code directories
version          - Project version number
mini_version     - Minor version number
configMap        - Dictionary of target configurations
osType           - Detected OS (Windows or Linux)
verbose          - Enable detailed logging
compilerPaths    - Cached compiler paths
```

### Main Methods

**Configuration:**

- `SetProjectName()` - Set project name
- `SetLanguage()` - Set programming language
- `SetCompiler()` - Set compiler name
- `AddSourcePath()` - Add source directory
- `AddIncludePath()` - Add header directory

**Building:**

- `Build()` - Start compilation process
- `ValidateSetup()` - Check configuration validity
- `Clean()` - Clean build artifacts

**Utilities:**

- `SetVerbose()` - Enable detailed output
- `SetCompilerPath()` - Override compiler path
- `GetCompilerPath()` - Find compiler in system
- `WriteLog()` - Write timestamped logs
- `GetOS()` - Get operating system type

**Target Configuration:**

- `addTargetConfig()` - Add target settings
- `GetTargetConfig()` - Get target settings
- `replaceTargetConfig()` - Replace target settings
- `replaceConfig()` - Update single target value
- `removeTargetConfig()` - Remove target
- `clearAllConfigs()` - Clear all targets

## How It Works

### Build Flow

```none
1. Create instance
   ↓
2. Configure (project name, language, compiler)
   ↓
3. Add paths (sources, includes)
   ↓
4. Validate setup
   ↓
5. Execute build
   ├─ Compile source files → .o objects
   └─ Link objects → executable
   ↓
6. Output results
```

### Compilation Process

For each supported language:

**C++**

1. Find all .cpp files in source paths
2. Compile each to .o object files
3. Link all objects into executable

**C**

1. Find all .c files in source paths
2. Compile each to .o object files
3. Link all objects into executable

**C#**

1. Find all .cs files in source paths
2. Compile all with CSC compiler
3. Create .exe directly

**Python**

1. Find all .py files
2. Verify presence (no compilation)
3. Show usage instructions

## Operating Systems

### Windows Support

- Detects via system APIs
- Supports MSVC, MinGW, Clang
- Uses Get-Command for compiler detection

### Linux Support

- Detects via system APIs
- Supports GCC, Clang
- Uses `which` command for compiler detection

## Configuration Types

### Basic Configuration

```powershell
$build = [PowerBuild]::new()
$build.SetProjectName("App")
$build.SetLanguage("C++")
$build.SetCompiler("g++")
```

### Multi-Target Configuration

```powershell
$debug = @{ flags = "-g -O0"; output = "./debug" }
$release = @{ flags = "-O3"; output = "./release" }
$build.addTargetConfig("Debug", $debug)
$build.addTargetConfig("Release", $release)
```

### Path Configuration

```powershell
$build.AddSourcePath("./src")
$build.AddSourcePath("./lib")
$build.AddIncludePath("./include")
$build.AddIncludePath("./third_party")
```

## Error Handling

System validates:

- Project name is set
- Language is specified
- Compiler is available
- Source paths exist
- Include paths exist

If validation fails, errors are reported before build starts.

## Logging System

When verbose mode enabled:

- All compiler commands shown
- Compilation progress displayed
- Errors with timestamps logged
- Success messages colored green

## Return Values

Methods return:

- `GetProjectName()` → string
- `GetLanguage()` → string
- `GetCompiler()` → string
- `GetSourcePaths()` → string[]
- `GetIncludePaths()` → string[]
- `GetVersion()` → double
- `GetMiniVersion()` → double
- `GetTargetConfig()` → hashtable
- `ValidateSetup()` → hashtable (Valid, Errors[], Warnings[])
- `GetOS()` → string (Windows or Linux)

## Typical Workflow

1. **Initialize**: Create new PowerBuild instance
2. **Configure**: Set name, language, compiler
3. **Add Paths**: Add source and include directories
4. **Validate**: Check setup with ValidateSetup()
5. **Build**: Execute Build() with output path
6. **Handle Results**: Check for errors or success

## Constraints

- Can only build one language per instance
- Requires actual compiler installed
- Source files must be in specified paths
- Single output file per build
- All sources compiled together (no selective compilation)
