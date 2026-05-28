# PowerShell Code Summary

The provided PowerShell code is a collection of functions and modules that to count the number of lines of code (LOC) in libraries, files, or multiple paths. The code also provides features for counting files by extension, calculating total file sizes, and exporting the results.

## Functions and Modules

1. **Count-CodeLines**: Counts the number of lines of code in a library or multiple libraries, filters by extensions, and displays the results.

	* Parameters: `Paths` (array of absolute or relative paths) and `Extensions` (array of file extensions to include)

2. **Measure-FilesByExtension**: Measures the total size of files with specified extensions in a directory.

	* Parameters: `Path` (absolute path), `Extensions` (array of file extensions to include)

3. **Get-FileSizeTotal**: Retrieves the total size of all files or directories in a given path, optionally filtered by extension.

	* Parameters: `Path` (absolute path) and `Extensions` (array of file extensions to include)

4. **Resolve-TargetPath**: Resolves relative paths to absolute paths.

5. **New-Alias -Name Quick-CountLines -Value Measure-CodeLines**: Creates a new alias for the `Measure-CodeLines` function

6. **New-Alias -Name Count-FilesByExtension -Value Measure-FilesByExtension Measure-FilesByExtension**: Creates a new alias for the `Measure-FilesByExtension` function

## Usage Example

```powershell
# Count code lines in the 'lite' library
Count-CodeLines -Paths 'C:\Project\lib'
# Count files by extension in the 'C:\Project' directory and its subdirectories
Measure-FilesByExtension -Path 'C:\Project'
```

Note: The `Resolve-TargetPath` function is not part of the standard PowerShell module, but rather a custom implementation for resolving relative paths to absolute paths.
