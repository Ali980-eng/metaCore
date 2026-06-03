# PowerTest.psm1
# Comprehensive test generation module using local AI (Ollama)
# Generates test cases based on documentation and library code

[UInt64] $script:testCounter = 0
[UInt64] $script:unitTestCounter = 0

class MetaTest {
    [String] $name
    [String] $description
    [UInt64] $testNumber
    [bool] $result
    [String] $errorMessage

    MetaTest([String]$testName, [String]$testDesc) {
        $this.name = $testName
        $this.description = $testDesc
        $this.testNumber = 0
        $this.result = $false
        $this.errorMessage = ""
    }

    [void] ValidateValue([object]$realVal, [object]$expVal) {
        $this.result = ($realVal -eq $expVal)
        if (-not $this.result) {
            $this.errorMessage = "Expected: $expVal, Got: $realVal"
        }
    }
}

class MetaUnitTest {
    [String] $name
    [String] $description
    [MetaTest[]] $tests = @()
    [UInt64] $passCount = 0
    [UInt64] $failCount = 0

    MetaUnitTest([String]$testName, [String]$testDesc) {
        $this.name = $testName
        $this.description = $testDesc
    }

    [void] AddTest([MetaTest]$test) {
        $this.tests += $test
        if ($test.result) {
            $this.passCount++
        } else {
            $this.failCount++
        }
    }

    [hashtable] GetSummary() {
        return @{
            Name = $this.name
            Total = $this.tests.Count
            Passed = $this.passCount
            Failed = $this.failCount
            Rate = if ($this.tests.Count -gt 0) { ($this.passCount / $this.tests.Count * 100) } else { 0 }
        }
    }
}

function Get-FrameworkSpecificPrompt {
    param(
        [Parameter(Mandatory = $true)]
        [ValidateSet('CTest', 'GTest', 'Jest', 'Pytest', 'NUnit', 'unittest', 'Pester', 'Mocha')]
        [string]$Framework,

        [Parameter(Mandatory = $true)]
        [ValidateSet('C', 'C++', 'C#', 'Java', 'Python', 'PowerShell', 'JavaScript', 'TypeScript')]
        [string]$Language
    )

    switch ($Framework) {
        'CTest' {
            return @"
FRAMEWORK: CTest (C Testing Framework)
REQUIREMENTS:
- Include all necessary headers at the top
- Use TEST_0, TEST_1, TEST_2, TEST_3 macros for assertions
- Use MAIN_TEST() and EXIT_TEST() for test structure
- Use ASSERT() for condition checking
- Call printSummary() at the end
- Include memory safety checks and cleanup
- Test all edge cases and boundary conditions
- Use clear test names that describe what is tested
- Include comments explaining test logic
SYNTAX EXAMPLE:
  TEST_2(function_call(), expected_value)
  ASSERT(condition)
"@
        }
        'GTest' {
            return @"
FRAMEWORK: Google Test (C++ Testing Framework)
REQUIREMENTS:
- Include gtest/gtest.h header
- Use TEST(TestSuite, TestName) macro for each test
- Use EXPECT_EQ, EXPECT_NE, EXPECT_TRUE, EXPECT_FALSE, EXPECT_THROW
- Use ASSERT_* variants for fatal assertions that stop test
- Setup test fixtures with SetUp/TearDown methods when needed
- Group related tests in test classes (TEST_F with fixtures)
- Use descriptive test names indicating what is tested
- Include comments explaining complex test logic
- Cover both success and error conditions
SYNTAX EXAMPLE:
  TEST(MathTest, Addition) {
    EXPECT_EQ(4, Add(2, 2));
  }
"@
        }
        'Jest' {
            return @"
FRAMEWORK: Jest (JavaScript/TypeScript Testing)
REQUIREMENTS:
- Use describe() to group test suites
- Use test() or it() for individual test cases
- Use expect() with matchers: toBe, toEqual, toThrow, toContain, toMatch
- Use beforeEach/afterEach hooks for setup/cleanup
- Handle async tests with async/await or .resolves/.rejects
- Use descriptive test names explaining what is tested
- Include comments explaining complex logic
- Test both success and error paths
- Cover edge cases and boundary conditions
SYNTAX EXAMPLE:
  describe('Math', () => {
    it('should add two numbers', () => {
      expect(add(2, 2)).toBe(4);
    });
  });
"@
        }
        'Pytest' {
            return @"
FRAMEWORK: Pytest (Python Testing Framework)
REQUIREMENTS:
- Use def test_* naming convention for test functions
- Use assert statements for checks
- Use pytest.raises() for exception testing
- Use @pytest.fixture decorator for fixtures
- Use @pytest.mark.parametrize for parameterized tests
- Include docstrings explaining what each test validates
- Test edge cases and exception handling
- Use descriptive test names
- Include comments explaining test logic
SYNTAX EXAMPLE:
  def test_addition():
      assert add(2, 2) == 4

  def test_division_by_zero():
      with pytest.raises(ZeroDivisionError):
          divide(5, 0)
"@
        }
        'NUnit' {
            return @"
FRAMEWORK: NUnit (C# .NET Testing Framework)
REQUIREMENTS:
- Include using NUnit.Framework;
- Use [TestFixture] attribute for test classes
- Use [Test] attribute for test methods
- Use [TestCase] for parameterized tests
- Use Assert.AreEqual, Assert.IsTrue, Assert.Throws, Assert.Pass, Assert.Fail
- Use [SetUp] and [TearDown] methods for setup/cleanup
- Use [OneTimeSetUp] for expensive setup operations
- Use [Category] attribute to organize tests
- Include clear test names describing what is tested
SYNTAX EXAMPLE:
  [TestFixture]
  public class MathTests {
    [Test]
    public void Addition_WithPositiveNumbers_ReturnsSum() {
      Assert.AreEqual(4, Add(2, 2));
    }
  }
"@
        }
        'unittest' {
            return @"
FRAMEWORK: unittest (Python Standard Library)
REQUIREMENTS:
- Use class TestClassName(unittest.TestCase) pattern
- Use test_* naming convention for test methods
- Use self.assertEqual, self.assertTrue, self.assertRaises, self.assertIn
- Use setUp() and tearDown() methods for setup/cleanup
- Use setUpClass/tearDownClass for class-level setup
- Include assertions with meaningful messages
- Test both positive and negative cases
- Use descriptive test method names
SYNTAX EXAMPLE:
  class TestMath(unittest.TestCase):
    def test_addition(self):
      self.assertEqual(4, add(2, 2))

    def test_division_by_zero(self):
      with self.assertRaises(ZeroDivisionError):
        divide(5, 0)
"@
        }
        'Pester' {
            return @"
FRAMEWORK: Pester (PowerShell Testing Framework)
REQUIREMENTS:
- Use Describe {} for test suites
- Use It {} for individual tests
- Use Should -Be, -Throw, -Contain, -Match, -Exist operators
- Use BeforeEach/AfterEach blocks for setup/cleanup
- Use Mock for mocking function calls
- Test pipeline input/output
- Include error handling tests
- Use clear, descriptive test names
- Include comments explaining test logic
SYNTAX EXAMPLE:
  Describe 'Math Functions' {
    It 'should add two numbers' {
      Add 2 2 | Should -Be 4
    }
  }
"@
        }
        'Mocha' {
            return @"
FRAMEWORK: Mocha (JavaScript/Node.js Testing)
REQUIREMENTS:
- Use describe() to group test suites
- Use it() for individual test cases
- Use assert library (chai) or expect() for assertions
- Use before/beforeEach/after/afterEach hooks
- Use .timeout() for tests needing more time
- Handle asynchronous tests with callbacks or promises
- Use clear, descriptive test names
- Include comments explaining complex logic
- Test both success and error paths
SYNTAX EXAMPLE:
  const assert = require('assert');
  describe('Math', () => {
    it('should add two numbers', () => {
      assert.strictEqual(add(2, 2), 4);
    });
  });
"@
        }
        default {
            return @"
Generate comprehensive test cases that:
- Cover all public functions from the documentation
- Include positive cases (happy path)
- Include negative cases (error handling)
- Test edge cases and boundary conditions
- Use clear, meaningful test names
- Include comments explaining test logic
- Follow the testing framework best practices
"@
        }
    }
}

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
        [ValidateSet('C', 'C++', 'C#', 'Java', 'Python', 'PowerShell', 'JavaScript', 'TypeScript')]
        [string]$Language,

        [Parameter(Mandatory = $true)]
        [ValidateSet('CTest', 'GTest', 'Jest', 'Pytest', 'NUnit', 'unittest', 'Pester', 'Mocha')]
        [string]$Framework,

        [Parameter(Mandatory = $false)]
        [ValidateScript({ Test-Path $_ -PathType Leaf })]
        [string]$Existing,

        [Parameter(Mandatory = $false)]
        [string]$Model = "llama2"
    )

    # Read documentation
    Write-Host "📖 Reading documentation: $Docs" -ForegroundColor Cyan
    try {
        $docText = Get-Content -Path $Docs -Raw -Encoding UTF8
        if (-not $docText) { throw "Documentation file is empty" }
    }
    catch {
        Write-Error "Failed to read documentation: $_"
        return
    }

    # Read library code
    Write-Host "📚 Reading library code: $Lib" -ForegroundColor Cyan
    try {
        $libText = Get-Content -Path $Lib -Raw -Encoding UTF8
        if (-not $libText) { throw "Library file is empty" }
    }
    catch {
        Write-Error "Failed to read library code: $_"
        return
    }

    # Read existing tests if provided
    $existingText = ""
    if ($Existing) {
        Write-Host "📋 Reading existing tests: $Existing" -ForegroundColor Cyan
        try {
            $existingText = Get-Content -Path $Existing -Raw -Encoding UTF8
        }
        catch {
            Write-Warning "Could not read existing tests: $_"
        }
    }

    # Get framework-specific prompt
    $frameworkPrompt = Get-FrameworkSpecificPrompt -Framework $Framework -Language $Language

    # Comprehensive system prompt
    $sysPrompt = @"
You are an expert test engineer specializing in $Language programming language.
Your role is to generate production-quality, comprehensive test cases that thoroughly validate library functionality.

CRITICAL REQUIREMENTS:
1. NEVER modify, comment out, delete, or alter the original library code in any way
2. ONLY output test code - no explanations, markdown, preambles, or extra text
3. Strictly follow the $Framework testing framework syntax and conventions
4. Generate ONLY the test code starting directly with imports/includes
5. Write clear, descriptive test names that explicitly indicate what is being tested
6. Include helpful comments inside test code to explain complex logic
7. Cover edge cases: null/empty values, boundary conditions, invalid inputs, type mismatches
8. Test both positive cases (expected behavior) and negative cases (error handling)
9. Use meaningful assertion messages and error descriptions
10. Each test should verify ONE specific behavior or condition

TESTING PHILOSOPHY:
- Write tests that are clear, maintainable, and easy to understand
- Use descriptive assertion messages that explain what went wrong
- Include at least one positive test per function
- Include at least one edge case test per function
- Test error conditions and exception handling when applicable
"@

    # Build detailed user prompt
    $userPrompt = @"
$frameworkPrompt

=== DOCUMENTATION ===
$docText

=== LIBRARY CODE (DO NOT MODIFY) ===
$libText
"@

    if ($existingText) {
        $userPrompt += @"

=== EXISTING TESTS (follow same style, patterns, and conventions) ===
$existingText
"@
    }

    $userPrompt += @"

=== TASK ===
Generate ONLY complete, executable test code in $Framework for $Language.

RULES FOR OUTPUT:
- Do NOT modify the library code under any circumstances
- Do NOT add explanations or markdown formatting
- Start directly with imports/includes at the top
- Include all necessary headers and dependencies
- Cover ALL functions from the documentation
- Include positive test cases (happy path)
- Include negative test cases (error conditions)
- Add comprehensive edge case testing
- Use clear test names describing what is tested
- Write inline comments explaining test logic
"@

    # Prepare and execute API call
    Write-Host "🔗 Connecting to Ollama: $AI" -ForegroundColor Magenta
    Write-Host "🤖 Model: $Model | 📊 Framework: $Framework | 💻 Language: $Language" -ForegroundColor Magenta
    Write-Host "⏳ Generating tests (this may take a moment)..." -ForegroundColor Yellow

    $body = @{
        model = $Model
        prompt = $userPrompt
        system = $sysPrompt
        stream = $false
    } | ConvertTo-Json -Depth 10

    try {
        $resp = Invoke-RestMethod -Uri $AI -Method Post -Body $body -ContentType "application/json" -ErrorAction Stop -TimeoutSec 300

        $tests = if ($resp.response) { $resp.response } elseif ($resp.choices -and $resp.choices[0].message.content) { $resp.choices[0].message.content } else { throw "Unexpected response format" }

        if (-not $tests -or [string]::IsNullOrWhiteSpace($tests)) {
            throw "AI returned empty response"
        }

        Write-Host "✅ Tests generated successfully!" -ForegroundColor Green
    } 
    catch {
        Write-Error "❌ AI API call failed: $_"
        Write-Host "`n💡 Troubleshooting:" -ForegroundColor Yellow
        Write-Host "  - Make sure Ollama is running: ollama serve" -ForegroundColor Yellow
        Write-Host "  - Pull model if missing: ollama pull $Model" -ForegroundColor Yellow
        Write-Host "  - Verify API endpoint: $AI" -ForegroundColor Yellow
        return
    }

    # Determine output file
    if (-not $Out) {
        $ext = switch ($Language) {
            'C' { '.c' }
            'C++' { '.cpp' }
            'C#' { '.cs' }
            'Java' { '.java' }
            'Python' { '.py' }
            'PowerShell' { '.ps1' }
            'JavaScript' { '.js' }
            'TypeScript' { '.ts' }
            default { '.txt' }
        }
        $Out = "tests_$(Get-Date -Format 'yyyyMMdd_HHmmss')$ext"
        Write-Host "📁 Output: $Out" -ForegroundColor Yellow
    }

    # Save output
    Write-Host "💾 Saving tests..." -ForegroundColor Cyan
    if (Test-Path $Out) {
        Write-Host "⚠️  File exists." -ForegroundColor Yellow
        $opt = Read-Host "[A]ppend, [O]verwrite, [N]ew, or [C]ancel"
        switch ($opt.ToUpper()) {
            "A" { Add-Content -Path $Out -Value "`n`n# === Generated $(Get-Date) ===`n$tests" -Encoding UTF8; Write-Host "✅ Appended to $Out" -ForegroundColor Green }
            "N" { $new = "$([System.IO.Path]::GetFileNameWithoutExtension($Out))_new$(Get-Date -Format 'HHmmss')$([System.IO.Path]::GetExtension($Out))"; Set-Content -Path $new -Value $tests -Encoding UTF8; Write-Host "✅ Saved to $new" -ForegroundColor Green }
            "C" { Write-Host "⏸️  Cancelled" -ForegroundColor Yellow; return }
            default { Set-Content -Path $Out -Value $tests -Encoding UTF8; Write-Host "✅ Overwrote $Out" -ForegroundColor Green }
        }
    }
    else {
        Set-Content -Path $Out -Value $tests -Encoding UTF8
        Write-Host "✅ Created $Out" -ForegroundColor Green
    }

    Write-Host "`n🎉 Complete! Review and run your tests." -ForegroundColor Green
}

Export-ModuleMember -Function @('New-Test', 'Get-FrameworkSpecificPrompt')