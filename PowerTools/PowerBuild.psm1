class PowerBuild {

  hidden [string]$projectName

  hidden [string]$projectPath

  hidden [string]$language

  hidden [string]$compiler

  hidden [string[]]$includePaths

  hidden [string[]]$sourcePaths

  hidden [double]$version = 1.0

  hidden [double]$mini_version = 1.0

  hidden [hashtable]$configMap

  hidden [hashtable]$buildCache = @{}

  hidden [bool]$verbose = $false

  hidden [string]$osType

  hidden [hashtable]$compilerPaths = @{}

  PowerBuild() {
    $this.projectPath = Get-Location
    $this.osType = [System.Runtime.InteropServices.RuntimeInformation]::IsOSPlatform([System.Runtime.InteropServices.OSPlatform]::Windows) ? "Windows" : "Linux"
    $this.configMap = @{}
    $this.includePaths = @()
    $this.sourcePaths = @()
  }

  [void] SetProjectName([string]$name) { $this.projectName = $name }

  [string] GetProjectName() { return $this.projectName }

  [void] SetLanguage([string]$lang) { $this.language = $lang }

  [string] GetLanguage() { return $this.language }

  [void] SetCompiler([string]$compiler) { $this.compiler = $compiler }

  [string] GetCompiler() { return $this.compiler }

  [void] AddIncludePath([string]$path) { $this.includePaths += $path }

  [string[]] GetIncludePaths() { return $this.includePaths }

  [void] AddSourcePath([string]$path) { $this.sourcePaths += $path }

  [string[]] GetSourcePaths() { return $this.sourcePaths }

  [void] mini_version([double]$version) { $this.mini_version = $version }

  [double] GetMiniVersion() { return $this.mini_version }

  [double] GetVersion() { return $this.version }

  [string] GetOS() { return $this.osType }

  [void] addTargetConfig([string]$target, [hashtable]$config) { $this.configMap[$target] = $config }

  [hashtable] GetTargetConfig([string]$target) { return $this.configMap[$target] }

  [void] clearConfigMap() { $this.configMap.Clear() }

  [void] clearAllConfigs() { $this.configMap.Clear() }

  [void] SetVerbose([bool]$verbose) { $this.verbose = $verbose }

  [void] replaceTargetConfig([string]$target, [hashtable]$config) {
    if ($this.configMap.ContainsKey($target)) {
      $this.configMap[$target] = $config
    } else {
      throw "Target '$target' does not exist in the configuration map."
    }
  }

  [void] replaceConfig([string]$target, [string]$key, $value) {
    if ($this.configMap.ContainsKey($target)) {
      $this.configMap[$target][$key] = $value
    } else {
      throw "Target '$target' does not exist in the configuration map."
    }
  }

  [void] replaceTarget([string]$target, [string]$key, $value) {
    if ($this.configMap.ContainsKey($target)) {
      $this.configMap[$target][$key] = $value
    } else {
      throw "Target '$target' does not exist in the configuration map."
    }
  }

  [void] removeTargetConfig([string]$target) {
    if ($this.configMap.ContainsKey($target)) {
      $this.configMap.Remove($target)
    } else {
      throw "Target '$target' does not exist in the configuration map."
    }
  }

  [void] writeTarget([string]$target, [string]$key, $value) {
    if ($this.configMap.ContainsKey($target)) {
        Write-Host $this.configMap[$target][$key]
    } else {
      throw "Target '$target' does not exist in the configuration map."
    }
  }

  [void] SetCompilerPath([string]$compiler, [string]$path) {
    $this.compilerPaths[$compiler] = $path
    $this.WriteLog("Compiler path set: $compiler = $path")
  }

  [string] GetCompilerPath([string]$compiler) {
    if ($this.compilerPaths.ContainsKey($compiler)) {
      return $this.compilerPaths[$compiler]
    }
    # Auto-detect compiler in PATH
    $found = $null
    if ($this.osType -eq "Windows") {
      $found = Get-Command $compiler -ErrorAction SilentlyContinue
    } else {
      $found = which $compiler -ErrorAction SilentlyContinue
    }
    if ($found) {
      $path = $found.Source
      $this.compilerPaths[$compiler] = $path
      return $path
    }
    throw "Compiler not found: $compiler"
  }

  [void] WriteLog([string]$message) {
    $timestamp = Get-Date -Format "yyyy-MM-dd HH:mm:ss"
    if ($this.verbose) {
      Write-Host "[$timestamp] $message" -ForegroundColor Green
    }
  }

  [hashtable] ValidateSetup() {
    $result = @{
      Valid = $true
      Errors = @()
      Warnings = @()
    }
    if ([string]::IsNullOrEmpty($this.projectName)) {
      $result.Errors += "Project name not set"
      $result.Valid = $false
    }
    if ([string]::IsNullOrEmpty($this.language)) {
      $result.Errors += "Programming language not specified"
      $result.Valid = $false
    }
    if ([string]::IsNullOrEmpty($this.compiler)) {
      $result.Errors += "Compiler not set"
      $result.Valid = $false
    }
    if ($this.sourcePaths.Count -eq 0) {
      $result.Warnings += "No source paths added"
    }
    try {
      $null = $this.GetCompilerPath($this.compiler)
    } catch {
      $result.Errors += "Error finding compiler: $_"
      $result.Valid = $false
    }
    return $result
  }

  [void] Build([string]$outputPath) {
    $validation = $this.ValidateSetup()
    if (-not $validation.Valid) {
      foreach ($err in $validation.Errors) {
        Write-Host "Error: $err" -ForegroundColor Red
      }
      throw "Setup validation failed"
    }
    foreach ($warning in $validation.Warnings) {
      Write-Host "Warning: $warning" -ForegroundColor Yellow
    }
    $this.WriteLog("Starting build for project: $($this.projectName)")
    $this.WriteLog("Language: $($this.language), Compiler: $($this.compiler)")
    try {
      switch ($this.language.ToLower()) {
        "c++" {
          $this.CompileCpp($outputPath)
        }
        "c" {
          $this.CompileC($outputPath)
        }
        "csharp" {
          $this.CompileCSharp($outputPath)
        }
        "python" {
          $this.HandlePython($outputPath)
        }
        default {
          throw "Unsupported language: $($this.language)"
        }
      }
      $this.WriteLog("Build completed successfully")
      Write-Host "✓ Build completed successfully" -ForegroundColor Green
    } catch {
      Write-Host "✗ Build failed: $_" -ForegroundColor Red
      throw
    }
  }

  [void] CompileCpp([string]$outputPath) {
    $compilerPath = $this.GetCompilerPath($this.compiler)
    $this.WriteLog("Using compiler: $compilerPath")
    $objects = @()
    # Compile source files
    foreach ($sourcePath in $this.sourcePaths) {
      $sourceFiles = Get-ChildItem -Path $sourcePath -Filter "*.cpp" -Recurse

      foreach ($file in $sourceFiles) {
        $objectFile = [IO.Path]::Combine($outputPath, [IO.Path]::GetFileNameWithoutExtension($file)) + ".o"
        $includeArgs = $this.includePaths | ForEach-Object { "-I $_" }
        $cmd = "$compilerPath -c $($file.FullName) -o $objectFile $includeArgs"
        $this.WriteLog("Compiling: $($file.Name)")
        if ($this.verbose) {
          Write-Host $cmd -ForegroundColor Cyan
        }
        Invoke-Expression $cmd | Out-Host
        if ($LASTEXITCODE -ne 0) {
          throw "Failed to compile file: $($file.Name)"
        }
        $objects += $objectFile
      }
    }
    # Link objects
    if ($objects.Count -gt 0) {
      $outputFile = [IO.Path]::Combine($outputPath, "$($this.projectName).exe")
      $linkCmd = "$compilerPath $($objects -join ' ') -o $outputFile"
      $this.WriteLog("Linking files...")
      if ($this.verbose) {
        Write-Host $linkCmd -ForegroundColor Cyan
      }
      Invoke-Expression $linkCmd | Out-Host
      if ($LASTEXITCODE -ne 0) {
        throw "Linking failed"
      }
    }
  }

  [void] CompileC([string]$outputPath) {
    $compilerPath = $this.GetCompilerPath($this.compiler)
    $this.WriteLog("Using C compiler: $compilerPath")
    $objects = @()
    foreach ($sourcePath in $this.sourcePaths) {
      $sourceFiles = Get-ChildItem -Path $sourcePath -Filter "*.c" -Recurse
      foreach ($file in $sourceFiles) {
        $objectFile = [IO.Path]::Combine($outputPath, [IO.Path]::GetFileNameWithoutExtension($file)) + ".o"
        $includeArgs = $this.includePaths | ForEach-Object { "-I $_" }
        $cmd = "$compilerPath -c $($file.FullName) -o $objectFile $includeArgs"
        $this.WriteLog("Compiling: $($file.Name)")
        Invoke-Expression $cmd | Out-Host
        if ($LASTEXITCODE -ne 0) {
          throw "Failed to compile file: $($file.Name)"
        }
        $objects += $objectFile
      }
    }
    if ($objects.Count -gt 0) {
      $outputFile = [IO.Path]::Combine($outputPath, "$($this.projectName).exe")
      $linkCmd = "$compilerPath $($objects -join ' ') -o $outputFile"

      $this.WriteLog("Linking files...")
      Invoke-Expression $linkCmd | Out-Host
    }
  }

  [void] CompileCSharp([string]$outputPath) {
    $this.WriteLog("Starting C# compilation...")
    $sourceFiles = @()
    foreach ($sourcePath in $this.sourcePaths) {
      $sourceFiles += (Get-ChildItem -Path $sourcePath -Filter "*.cs" -Recurse).FullName
    }
    if ($sourceFiles.Count -eq 0) {
      throw "No .cs files found"
    }
    $outputFile = [IO.Path]::Combine($outputPath, "$($this.projectName).exe")
    $cscPath = "csc.exe"
    if ($this.osType -eq "Linux") {
      $cscPath = "csc"
    }
    $cmd = "$cscPath -out:$outputFile $($sourceFiles -join ' ')"
    $this.WriteLog("Command: $cmd")
    Invoke-Expression $cmd | Out-Host
    if ($LASTEXITCODE -ne 0) {
      throw "C# compilation failed"
    }
  }

  [void] HandlePython([string]$outputPath) {
    $this.WriteLog("Python does not require compilation. Setting up environment only...")
    $sourceFiles = @()
    foreach ($sourcePath in $this.sourcePaths) {
      $sourceFiles += (Get-ChildItem -Path $sourcePath -Filter "*.py" -Recurse).FullName
    }
    if ($sourceFiles.Count -eq 0) {
      throw "No .py files found"
    }
    $this.WriteLog("Found $($sourceFiles.Count) Python files")
    Write-Host "Note: Python files found. Use 'python main.py' to run" -ForegroundColor Yellow
  }

  [void] Clean() {
    $this.WriteLog("Cleaning build files...")
    $this.buildCache.Clear()
    Write-Host "✓ Cleanup completed" -ForegroundColor Green
  }
}