# PowerBuild PowerShell Class Overview

---------------------------------------

The `PowerBuild` class is a custom PowerShell module that provides a set of functions for building and managing projects. It allows users to specify the project name, language, compiler, include paths, source paths, and version.

## Functions and Their Purposes

* `SetProjectName`: Sets the project name.
* `GetProjectName`: Returns the current project name.
* `SetLanguage`: Sets the programming language.
* `GetLanguage`: Returns the current programming language.
* `AddIncludePath`: Adds an include path to the configuration map.
* `GetIncludePaths`: Returns the include paths in the configuration map.
* `AddSourcePath`: Adds a source path to the configuration map.
* `GetSourcePaths`: Returns the source paths in the configuration map.
* `mini_version`: Sets or gets the minimum version of the project.
* `GetMiniVersion`: Returns the current minimum version of the project.
* `GetVersion`: Returns the current version of the project.
* `AddConfigTarget`: Adds a target to the configuration map with a given configuration hash table.
* `ReplaceConfigTarget`: Replaces a target in the configuration map with a new configuration hash table.
* `ReplaceTargetConfig`: Replaces a config target in the configuration map with a new config key-value pair.
* `RemoveTargetConfig`: Removes a target from the configuration map by key.
* `ClearConfigMap`: Clears the entire configuration map.
* `ClearAllConfigs`: Clears all configurations, including targets and versions.
* `WriteTarget`: Writes a target to the log with its associated key-value pair.
* `SetCompilerPath`: Sets or gets the compiler path for a given language.
* `GetCompilerPath`: Returns the compiler path for a given language.
* `ValidateSetup`: Validates the setup of the project by checking for required configuration values.

## Build Methods

The build method allows users to compile and link their projects using various languages.
It supports C++, C, C#, and Python.

* `CompileCpp`: Compiles source files in C++ and links them into an executable.
* `CompileC`: Compiles source files in C and links them into an executable.
* `CompileCSharp`: Compiles source files in C# and links them into an executable using the `csc.exe` compiler.
* `HandlePython`: Allows users to compile Python code without compiling it first.

## Clean Method

The clean method deletes build files and resets the configuration map.

## Usage Example

To use this class, you can create a new instance of `PowerBuild` and then call its methods as needed. For example:

```powershell
    $build = New-Object PowerBuild

    # Set project name
    $build.SetProjectName "My Project"

    # Compile C++ code
    $build.Build("C:\\Path\\To\\Output")

    # Get compiler path for C++
    $compilerPath = $build.GetCompilerPath("c")
    Write-Host "Using $compilerPath"
```

Note: This is a high-level overview of the class and its methods. The exact 5D K
exact usage may vary depending on your specific requirements and PowerShell 10D K
PowerShell version.
