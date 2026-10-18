param (
    [string]$Directory
)

# a) Verify directory exists
if (-not (Test-Path $Directory -PathType Container)) {
    Write-Warning "The directory '$Directory' does not exist."
    exit 1
}

# Resolve full path (removes trailing backslash issues)
$FullPath = (Resolve-Path $Directory).Path

# b) Get all files (recursively) and store relative paths
$Files = Get-ChildItem -Path $FullPath -Recurse -File | ForEach-Object {
    $_.FullName.Substring($FullPath.Length + 1)
}

# c) Sort file names
$SortedFiles = $Files | Sort-Object

# d) Print one per line
$SortedFiles | ForEach-Object {
    Write-Output $_
}