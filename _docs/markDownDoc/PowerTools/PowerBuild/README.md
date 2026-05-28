# PowerBuild - Build System for PowerShell

A professional build system written in PowerShell that supports multiple languages and operating systems.

## Quick Start

```powershell
Import-Module ./PowerBuild.psm1

$build = [PowerBuild]::new()
$build.SetProjectName("MyApp")
$build.SetLanguage("C++")
$build.SetCompiler("g++")
$build.AddSourcePath("./src")
$build.Build("./build")
```

## Documentation Files

- **[OVERVIEW.md](OVERVIEW.md)** - System architecture and components
- **[INSTALLATION.md](INSTALLATION.md)** - Setup and configuration
- **[API.md](API.md)** - All methods and properties
- **[USAGE.md](USAGE.md)** - How to use the system
- **[EXAMPLES.md](EXAMPLES.md)** - Real-world code examples
- **[CONFIGURATION.md](CONFIGURATION.md)** - Advanced configuration
- **[TROUBLESHOOTING.md](TROUBLESHOOTING.md)** - Common issues and solutions

## Features

- ✅ Multiple languages (C++, C, C#, Python)
- ✅ Cross-platform (Windows, Linux, macOS)
- ✅ Error handling and validation
- ✅ Logging system
- ✅ Target-based builds (Debug/Release)

## Supported Languages

- **C++** - Full compilation and linking
- **C** - Full compilation and linking
- **C#** - CSC compiler integration
- **Python** - Environment validation

## Status

✅ Production Ready
