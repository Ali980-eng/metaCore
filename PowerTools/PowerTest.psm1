# powerTest.psm1
# Full module - copy this entire code into a file named powerTest.psm1

function New-Test {
    [CmdletBinding()]
    param(
        [Parameter(Mandatory = $true)]
        [ValidateScript({ Test-Path $_ -PathType Leaf })]
        [string]$Docs,

        [Parameter(Mandatory = $true)]
        [ValidateScript({ Test-Path $_ -PathType Leaf })]
        [string]$Lib,

        [Parameter(Mandatory = $false)]
        [string]$Out,

        [Parameter(Mandatory = $false)]
        [string]$AI = "http://localhost:11434/api/generate",

        [Parameter(Mandatory = $true)]
        [string]$Model,

        [Parameter(Mandatory = $true)]
        [string]$Framework,

        [Parameter(Mandatory = $false)]
        [ValidateScript({ Test-Path $_ -PathType Leaf })]
        [string]$Existing
    )

    # Read files
    Write-Host "Reading: $Docs" -ForegroundColor Cyan
    $docText = Get-Content -Path $Docs -Raw -Encoding UTF8

    Write-Host "Reading: $Lib" -ForegroundColor Cyan
    $libText = Get-Content -Path $Lib -Raw -Encoding UTF8

    $existingText = ""
    if ($Existing) {
        Write-Host "Reading existing tests: $Existing" -ForegroundColor Cyan
        $existingText = Get-Content -Path $Existing -Raw -Encoding UTF8
    }

    # System prompt - strict rules
    $sysPrompt = @"
You are a test writer.
RULES:
1. NEVER modify the original library code.
2. ONLY output test code (no explanations, no markdown).
3. Use the test framework: $Framework
4. Cover all functions from documentation. Include edge cases.
5. Write comments inside the test code.
"@
    # User prompt
    $userPrompt = @"
DOCUMENTATION:
LIBRARY (DO NOT MODIFY):
"@
    if ($existingText) {
        $userPrompt += @"
EXISTING TESTS (follow same style):
"@
    }

    $userPrompt += "Write ONLY test code for framework '$Framework'. Do not modify library. Do not add extra text."

    # Call AI
    Write-Host "Calling AI ($Model)..." -ForegroundColor Magenta
    $body = @{ model = $Model; prompt = $userPrompt; system = $sysPrompt; stream = $false } | ConvertTo-Json

    try {
        $resp = Invoke-RestMethod -Uri $AI -Method Post -Body $body -ContentType "application/json" -ErrorAction Stop
        $tests = if ($resp.response) { $resp.response } elseif ($resp.choices[0].message.content) { $resp.choices[0].message.content } else { throw "Bad response" }
        Write-Host "Tests generated." -ForegroundColor Green
    } catch {
        Write-Error "AI call failed: $_"
        return
    }

    # Output handling
    if (-not $Out) {
        $Out = "tests_$(Get-Date -Format 'yyyyMMdd_HHmmss').txt"
        Write-Host "No -Out given, using: $Out" -ForegroundColor Yellow
    }

    if (Test-Path $Out) {
        $opt = Read-Host "File $Out exists. Append (A), Overwrite (O), New (N)? [A/O/N]"
        switch ($opt.ToUpper()) {
            "A" { Add-Content -Path $Out -Value "`n`n# === Added $(Get-Date) ===`n$tests" -Encoding UTF8; Write-Host "Appended." -ForegroundColor Green }
            "N" { $new = [System.IO.Path]::GetFileNameWithoutExtension($Out) + "_new" + [System.IO.Path]::GetExtension($Out); Set-Content -Path $new -Value $tests -Encoding UTF8; Write-Host "Saved to $new" -ForegroundColor Green }
            default { Set-Content -Path $Out -Value $tests -Encoding UTF8; Write-Host "Overwritten." -ForegroundColor Green }
        }
    } else {
        Set-Content -Path $Out -Value $tests -Encoding UTF8
        Write-Host "Saved to $Out" -ForegroundColor Green
    }
}

Export-ModuleMember -Function New-Test