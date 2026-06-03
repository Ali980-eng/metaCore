# PowerCount Module - Count Lines of Code in Libraries
# Counts the number of lines of code in libraries and files

# Helper function to resolve relative paths to absolute paths
function Resolve-TargetPath {
    param([string]$Path)

    if ([System.IO.Path]::IsPathRooted($Path)) {
        return $Path
    }

    $currentLocation = Get-Location
    return Join-Path -Path $currentLocation -ChildPath $Path
}

<#
.SYNOPSIS
    Count lines of code in a library or multiple libraries

.DESCRIPTION
    Function that calculates the total number of lines of code in a file, folder, or multiple paths
    Prints the name of each file with the number of lines and calculates the final total
    Supports both absolute and relative paths

.PARAMETER Paths
    The path or paths (single file, folder, or array of paths) - can be relative or absolute

.PARAMETER Extensions
    File extensions to count (example: @('.cpp', '.h', '.ps1'))

.EXAMPLE
    Count-CodeLines -Paths 'lite'
    Count-CodeLines -Paths 'C:\Project\lib'
    Count-CodeLines -Paths @('lite', 'clite')
    Count-CodeLines -Paths @('C:\Project\lib1', 'C:\Project\lib2')
#>
function CountCodeLines {
    param(
        [Parameter(Mandatory=$true, ValueFromPipeline=$true)]
        [string[]]$Paths,

        [string[]]$Extensions = @('.cpp', '.c', '.h', '.hpp', '.ps1', '.psm1', '.py', '.cs', '.java', '.js', '.ts')
    )

    begin {
        $totalLines = 0
        $fileCount = 0
        $results = @()

        # Clean up paths and resolve relative paths
        $pathList = @()
        foreach ($path in $Paths) {
            $resolvedPath = Resolve-TargetPath $path
            $pathList += $resolvedPath
        }
    }

    process {
        foreach ($targetPath in $pathList) {
            # Verify that the path exists
            if (-not (Test-Path $targetPath)) {
                Write-Warning "Path not found: $targetPath"
                continue
            }

            # Handle single file
            if ((Get-Item $targetPath) -is [System.IO.FileInfo]) {
                $file = Get-Item $targetPath
                if ($Extensions.Contains($file.Extension)) {
                    $lineCount = (Get-Content $targetPath | Measure-Object -Line).Lines
                    if ($null -eq $lineCount) { $lineCount = 0 }

                    $results += [PSCustomObject]@{
                        Name = $file.Name
                        Path = $file.FullName
                        Lines = $lineCount
                        Type = 'File'
                    }

                    $totalLines += $lineCount
                    $fileCount++
                }
            }
            # Handle folder
            elseif ((Get-Item $targetPath) -is [System.IO.DirectoryInfo]) {
                $directory = Get-Item $targetPath
                $files = Get-ChildItem -Path $targetPath -Recurse -File | Where-Object { $Extensions.Contains($_.Extension) }

                foreach ($file in $files) {
                    $lineCount = (Get-Content $file.FullName | Measure-Object -Line).Lines
                    if ($null -eq $lineCount) { $lineCount = 0 }

                    $results += [PSCustomObject]@{
                        Name = $file.Name
                        Path = $file.FullName
                        Lines = $lineCount
                        Type = 'File'
                    }

                    $totalLines += $lineCount
                    $fileCount++
                }
            }
        }
    }

    end {
        # Print results
        if ($results.Count -gt 0) {
            Write-Host "`n╔════════════════════════════════════════════════════════╗" -ForegroundColor Cyan
            Write-Host "║              Lines of Code (LOC) Report               ║" -ForegroundColor Cyan
            Write-Host "╠════════════════════════════════════════════════════════╣" -ForegroundColor Cyan

            foreach ($result in $results) {
                $displayPath = if ($result.Path.Length -gt 45) {
                    "..." + $result.Path.Substring($result.Path.Length - 42)
                } else {
                    $result.Path
                }
                Write-Host ("║ {0,-43} {1,8} ║" -f $displayPath, $result.Lines) -ForegroundColor Green
            }

            Write-Host "╠════════════════════════════════════════════════════════╣" -ForegroundColor Cyan
            Write-Host ("║ Total Files: {0,-39} {1,8} ║" -f $fileCount, " ") -ForegroundColor Yellow
            Write-Host ("║ Total Lines: {0,-39} {1,8} ║" -f " ", $totalLines) -ForegroundColor Yellow
            Write-Host "╚════════════════════════════════════════════════════════╝" -ForegroundColor Cyan

            return @{
                TotalLines = $totalLines
                FileCount = $fileCount
                Details = $results
            }
        }
        else {
            Write-Warning "No source files found in the specified path."
        }
    }
}

# Fast and simple line counting
<#
.SYNOPSIS
    Measure lines of code quickly (simplified version)

.DESCRIPTION
    Fast version that counts lines without detailed reporting
    Supports both absolute and relative paths

.EXAMPLE
    Measure-CodeLines 'lite'
    Measure-CodeLines 'C:\Project'
#>
function Measure-CodeLines {
    param(
        [Parameter(Mandatory=$true)]
        [string]$Path,

        [string[]]$Extensions = @('.cpp', '.c', '.h', '.hpp', '.ps1', '.psm1', '.py')
    )

    $resolvedPath = Resolve-TargetPath $Path

    if (-not (Test-Path $resolvedPath)) {
        Write-Error "Path not found: $resolvedPath"
        return
    }

    $totalLines = 0

    if ((Get-Item $resolvedPath) -is [System.IO.FileInfo]) {
        $content = Get-Content $resolvedPath -Raw -ErrorAction SilentlyContinue
        $totalLines = if ($null -eq $content) { 0 } else { @($content -split "`n").Count }
        Write-Host "File: $(Split-Path $resolvedPath -Leaf) - $totalLines lines" -ForegroundColor Green
    }
    else {
        $files = Get-ChildItem -Path $resolvedPath -Recurse -File | Where-Object { $Extensions.Contains($_.Extension) }

        foreach ($file in $files) {
            $content = Get-Content $file.FullName -Raw -ErrorAction SilentlyContinue
            $lines = if ($null -eq $content) { 0 } else { @($content -split "`n").Count }
            $totalLines += $lines
            if ($lines -gt 0) {
                Write-Host ("$(Split-Path $file.FullName -Leaf)").PadRight(30) " - $lines lines" -ForegroundColor Green
            }
        }

        Write-Host "`nTotal: $totalLines lines" -ForegroundColor Yellow
    }

    return $totalLines
}

# Count files by type or extension
<#
.SYNOPSIS
    Count files by extension in a directory

.DESCRIPTION
    Counts the number of files for each extension separately
    Displays file statistics in a formatted table with totals
    Supports both absolute and relative paths

.PARAMETER Path
    The directory path to analyze (can be relative or absolute)

.PARAMETER Extensions
    Specific extensions to count (optional, if not specified, counts all extensions)

.EXAMPLE
    Measure-FilesByExtension -Path 'lite'
    Measure-FilesByExtension -Path 'C:\Project'
    Measure-FilesByExtension -Path 'C:\Project' -Extensions @('.cpp', '.h', '.hpp')
#>
function Measure-FilesByExtension {
    param(
        [Parameter(Mandatory=$true)]
        [string]$Path,

        [string[]]$Extensions = $null
    )

    $resolvedPath = Resolve-TargetPath $Path

    if (-not (Test-Path $resolvedPath)) {
        Write-Error "Path not found: $resolvedPath"
        return
    }

    if (-not ((Get-Item $resolvedPath) -is [System.IO.DirectoryInfo])) {
        Write-Error "Path must be a directory"
        return
    }

    # Get all files recursively
    $allFiles = Get-ChildItem -Path $resolvedPath -Recurse -File

    # Filter by extensions if specified
    if ($Extensions) {
        $allFiles = $allFiles | Where-Object { $Extensions.Contains($_.Extension) }
    }

    # Group files by extension
    $filesByExtension = $allFiles | Group-Object -Property Extension | Sort-Object -Property Count -Descending

    $totalFiles = $allFiles.Count

    # Display results
    if ($filesByExtension.Count -gt 0) {
        Write-Host "`n╔════════════════════════════════════════════════════════╗" -ForegroundColor Cyan
        Write-Host "║            File Count by Extension Report             ║" -ForegroundColor Cyan
        Write-Host "╠════════════════════════════════════════════════════════╣" -ForegroundColor Cyan

        foreach ($group in $filesByExtension) {
            $ext = if ([string]::IsNullOrWhiteSpace($group.Name)) { "(no extension)" } else { $group.Name }
            Write-Host ("║ {0,-40} {1,10} ║" -f $ext, $group.Count) -ForegroundColor Green
        }

        Write-Host "╠════════════════════════════════════════════════════════╣" -ForegroundColor Cyan
        Write-Host ("║ {0,-40} {1,10} ║" -f "Total Files", $totalFiles) -ForegroundColor Yellow
        Write-Host "╚════════════════════════════════════════════════════════╝" -ForegroundColor Cyan

        return @{
            TotalFiles = $totalFiles
            ByExtension = $filesByExtension | Select-Object -Property Name, Count
        }
    }
    else {
        Write-Warning "No files found in the specified path."
    }
}

# Calculate total file size
<#
.SYNOPSIS
    Get the total size of files in a directory

.DESCRIPTION
    Calculates the total size of files, optionally filtered by extension
    Displays file size statistics with human-readable format (B, KB, MB, GB)
    Supports both absolute and relative paths

.PARAMETER Path
    The file or directory path to analyze (can be relative or absolute)

.PARAMETER Extensions
    File extensions to include (optional)

.EXAMPLE
    Get-FileSizeTotal -Path 'lite'
    Get-FileSizeTotal -Path 'C:\Project\lib'
    Get-FileSizeTotal -Path 'C:\Project' -Extensions @('.cpp', '.h')
#>
function Get-FileSizeTotal {
    param(
        [Parameter(Mandatory=$true)]
        [string]$Path,

        [string[]]$Extensions = $null
    )

    $resolvedPath = Resolve-TargetPath $Path

    if (-not (Test-Path $resolvedPath)) {
        Write-Error "Path not found: $resolvedPath"
        return
    }

    # Helper function to format bytes to human-readable format
    function Format-ByteSize {
        param($bytes)

        if ($bytes -eq 0) { return "0 B" }

        $sizes = @('B', 'KB', 'MB', 'GB', 'TB')
        $order = 0

        while ($bytes -ge 1024 -and $order -lt $sizes.Length - 1) {
            $order++
            $bytes = $bytes / 1024
        }

        return "{0:N2} {1}" -f $bytes, $sizes[$order]
    }

    $item = Get-Item $resolvedPath

    # Handle single file
    if ($item -is [System.IO.FileInfo]) {
        $fileSize = $item.Length
        $formattedSize = Format-ByteSize $fileSize

        Write-Host "`n╔════════════════════════════════════════════════════════╗" -ForegroundColor Cyan
        Write-Host "║                File Size Information                 ║" -ForegroundColor Cyan
        Write-Host "╠════════════════════════════════════════════════════════╣" -ForegroundColor Cyan
        Write-Host ("║ File: {0,-47} ║" -f $item.Name) -ForegroundColor Green
        Write-Host ("║ Size: {0,-47} ║" -f $formattedSize) -ForegroundColor Yellow
        Write-Host "╚════════════════════════════════════════════════════════╝" -ForegroundColor Cyan

        return @{
            TotalSize = $fileSize
            FormattedSize = $formattedSize
        }
    }

    # Handle directory
    elseif ($item -is [System.IO.DirectoryInfo]) {
        $files = Get-ChildItem -Path $resolvedPath -Recurse -File

        # Filter by extensions if specified
        if ($Extensions) {
            $files = $files | Where-Object { $Extensions.Contains($_.Extension) }
        }

        $totalSize = 0
        $fileSizes = @()

        foreach ($file in $files) {
            $totalSize += $file.Length
            $fileSizes += [PSCustomObject]@{
                Name = $file.Name
                Extension = $file.Extension
                Size = $file.Length
                FormattedSize = Format-ByteSize $file.Length
            }
        }

        # Sort by size descending
        $fileSizes = $fileSizes | Sort-Object -Property Size -Descending

        $formattedTotalSize = Format-ByteSize $totalSize
        $averageSize = if ($files.Count -gt 0) { Format-ByteSize ($totalSize / $files.Count) } else { "0 B" }

        # Display results
        Write-Host "`n╔════════════════════════════════════════════════════════╗" -ForegroundColor Cyan
        Write-Host "║              Directory Size Report (Top 10)          ║" -ForegroundColor Cyan
        Write-Host "╠════════════════════════════════════════════════════════╣" -ForegroundColor Cyan

        $displayCount = [Math]::Min(10, $fileSizes.Count)
        for ($i = 0; $i -lt $displayCount; $i++) {
            $fs = $fileSizes[$i]
            $displayName = if ($fs.Name.Length -gt 35) {
                $fs.Name.Substring(0, 32) + "..."
            } else {
                $fs.Name
            }
            Write-Host ("║ {0,-35} {1,15} ║" -f $displayName, $fs.FormattedSize) -ForegroundColor Green
        }

        if ($fileSizes.Count -gt 10) {
            Write-Host ("║ ... and {0} more files" -f ($fileSizes.Count - 10)).PadRight(54) "║" -ForegroundColor DarkGray
        }

        Write-Host "╠════════════════════════════════════════════════════════╣" -ForegroundColor Cyan
        Write-Host ("║ Total Files: {0,-42} {1,8} ║" -f $files.Count, " ") -ForegroundColor Yellow
        Write-Host ("║ Total Size:  {0,-42} ║" -f $formattedTotalSize) -ForegroundColor Yellow
        Write-Host ("║ Average Size:{0,-42} ║" -f $averageSize) -ForegroundColor Yellow
        Write-Host "╚════════════════════════════════════════════════════════╝" -ForegroundColor Cyan

        return @{
            TotalSize = $totalSize
            FormattedSize = $formattedTotalSize
            AverageSize = $averageSize
            FileCount = $files.Count
            Details = $fileSizes
        }
    }
}

<#
.SYNOPSIS
    Count effective lines of code (excluding comments and blank lines)

.DESCRIPTION
    Intelligent line counter that excludes:
    - Empty lines
    - Single-line comments (// # )
    - Multi-line comments /* */ <# #> """"""
    Supports C, C++, C#, Java, JavaScript, TypeScript, Python, PowerShell

.PARAMETER Paths
    The path or paths (single file, folder, or array of paths) - can be relative or absolute

.PARAMETER Extensions
    File extensions to count (example: @('.cpp', '.h', '.ps1'))

.EXAMPLE
    Count-SmartLines -Paths 'lite'
    Count-SmartLines -Paths @('lite', 'clite')
#>
function Count-SmartLines {
    param(
        [Parameter(Mandatory=$true, ValueFromPipeline=$true)]
        [string[]]$Paths,
        
        [string[]]$Extensions = @('.cpp', '.c', '.h', '.hpp', '.ps1', '.py', '.cs', '.java', '.js', '.ts')
    )

    begin {
        $totalLines = 0
        $fileCount = 0
        $results = @()

        $pathList = @()
        foreach ($path in $Paths) {
            $resolvedPath = Resolve-TargetPath $path
            $pathList += $resolvedPath
        }

        # Helper function to detect comment style based on file extension
        function Get-CommentStyle {
            param([string]$Extension)
            switch ($Extension) {
                {$_ -in @('.cpp', '.c', '.h', '.hpp', '.cs', '.java', '.js', '.ts')} {
                    return @{
                        'SingleLine' = '//'
                        'MultiLineStart' = '/*'
                        'MultiLineEnd' = '*/'
                        'StringDelimiters' = @('"', "'")
                    }
                }
                {$_ -in @('.ps1', '.psm1')} {
                    return @{
                        'SingleLine' = '#'
                        'MultiLineStart' = '<#'
                        'MultiLineEnd' = '#>'
                        'StringDelimiters' = @('"', "'")
                    }
                }
                {$_ -in @('.py')} {
                    return @{
                        'SingleLine' = '#'
                        'MultiLineStart' = '"""'
                        'MultiLineEnd' = '"""'
                        'StringDelimiters' = @('"', "'")
                    }
                }
                default {
                    return @{
                        'SingleLine' = '//'
                        'MultiLineStart' = '/*'
                        'MultiLineEnd' = '*/'
                        'StringDelimiters' = @('"', "'")
                    }
                }
            }
        }

        # Count effective lines (excluding comments and blank lines)
        function Count-EffectiveLines {
            param([string]$FilePath)

            try {
                $content = Get-Content $FilePath -Raw -ErrorAction SilentlyContinue
                if ($null -eq $content) { return 0 }

                $lines = $content -split "`n"
                $effectiveCount = 0
                $inMultilineComment = $false
                $commentStyle = Get-CommentStyle ([System.IO.Path]::GetExtension($FilePath))
                $singleComment = $commentStyle['SingleLine']
                $multiStart = $commentStyle['MultiLineStart']
                $multiEnd = $commentStyle['MultiLineEnd']

                foreach ($line in $lines) {
                    $trimmed = $line.Trim()

                    # Skip empty lines
                    if ([string]::IsNullOrWhiteSpace($trimmed)) {
                        continue
                    }

                    # Handle multiline comment end
                    if ($inMultilineComment) {
                        if ($trimmed.Contains($multiEnd)) {
                            $inMultilineComment = $false
                        }
                        continue
                    }

                    # Check for multiline comment start
                    if ($trimmed.Contains($multiStart)) {
                        if ($trimmed.Contains($multiEnd)) {
                            # Start and end on same line
                            $beforeComment = $trimmed.Substring(0, $trimmed.IndexOf($multiStart))
                            if (-not [string]::IsNullOrWhiteSpace($beforeComment)) {
                                $effectiveCount++
                            }
                            continue
                        } else {
                            # Multiline comment starts
                            $beforeComment = $trimmed.Substring(0, $trimmed.IndexOf($multiStart))
                            if (-not [string]::IsNullOrWhiteSpace($beforeComment)) {
                                $effectiveCount++
                            }
                            $inMultilineComment = $true
                            continue
                        }
                    }

                    # Check for single line comment
                    $commentIndex = $trimmed.IndexOf($singleComment)
                    if ($commentIndex -eq 0) {
                        # Entire line is a comment
                        continue
                    } elseif ($commentIndex -gt 0) {
                        # Check if comment is inside string (simple check)
                        $beforeComment = $trimmed.Substring(0, $commentIndex)
                        $effectiveCount++
                    } else {
                        # This is actual code
                        $effectiveCount++
                    }
                }

                return $effectiveCount
            }
            catch {
                return 0
            }
        }
    }

    process {
        foreach ($targetPath in $pathList) {
            if (-not (Test-Path $targetPath)) {
                Write-Warning "Path not found: $targetPath"
                continue
            }

            if ((Get-Item $targetPath) -is [System.IO.FileInfo]) {
                $file = Get-Item $targetPath
                if ($Extensions.Contains($file.Extension)) {
                    $lineCount = Count-EffectiveLines $file.FullName

                    $results += [PSCustomObject]@{
                        Name = $file.Name
                        Path = $file.FullName
                        Lines = $lineCount
                        Type = 'File'
                    }

                    $totalLines += $lineCount
                    $fileCount++
                }
            }
            elseif ((Get-Item $targetPath) -is [System.IO.DirectoryInfo]) {
                $directory = Get-Item $targetPath
                $files = Get-ChildItem -Path $targetPath -Recurse -File | 
                         Where-Object { $Extensions.Contains($_.Extension) }

                foreach ($file in $files) {
                    $lineCount = Count-EffectiveLines $file.FullName

                    $results += [PSCustomObject]@{
                        Name = $file.Name
                        Path = $file.FullName
                        Lines = $lineCount
                        Type = 'File'
                    }

                    $totalLines += $lineCount
                    $fileCount++
                }
            }
        }
    }

    end {
        if ($results.Count -gt 0) {
            Write-Host "`n╔════════════════════════════════════════════════════════╗" -ForegroundColor Cyan
            Write-Host "║         Smart Lines of Code Report                 ║" -ForegroundColor Cyan
            Write-Host "║     (Comments & Blank Lines Excluded)              ║" -ForegroundColor Cyan
            Write-Host "╠════════════════════════════════════════════════════════╣" -ForegroundColor Cyan

            foreach ($result in $results) {
                $displayPath = if ($result.Path.Length -gt 45) {
                    "..." + $result.Path.Substring($result.Path.Length - 42)
                } else {
                    $result.Path
                }
                Write-Host ("║ {0,-43} {1,8} ║" -f $displayPath, $result.Lines) -ForegroundColor Green
            }

            Write-Host "╠════════════════════════════════════════════════════════╣" -ForegroundColor Cyan
            Write-Host ("║ Total Files: {0,-39} {1,8} ║" -f $fileCount, " ") -ForegroundColor Yellow
            Write-Host ("║ Total Lines: {0,-39} {1,8} ║" -f " ", $totalLines) -ForegroundColor Yellow
            Write-Host "╚════════════════════════════════════════════════════════╝" -ForegroundColor Cyan

            return @{
                TotalLines = $totalLines
                FileCount = $fileCount
                Details = $results
            }
        }
        else {
            Write-Warning "No source files found in the specified path."
        }
    }
}

# Create aliases for backward compatibility
New-Alias -Name Quick-CountLines -Value Measure-CodeLines -Force
New-Alias -Name Count-FilesByExtension -Value Measure-FilesByExtension -Force
New-Alias -Name Smart-Count -Value Count-SmartLines -Force

# Export functions
Export-ModuleMember -Function @('CountCodeLines', 'Measure-CodeLines', 'Measure-FilesByExtension', 'Get-FileSizeTotal', 'Count-SmartLines', 'Resolve-TargetPath') -Alias @('Quick-CountLines', 'Count-FilesByExtension', 'Smart-Count')