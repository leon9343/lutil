#!/usr/bin/env pwsh
param(
    [string]$InstallPrefix = "C:\Program Files\lutil"
)

$ErrorActionPreference = "Stop"

if (!(Test-Path -Path "build")) {
    New-Item -ItemType Directory -Path "build" | Out-Null
}
Set-Location build

cmake .. -DCMAKE_INSTALL_PREFIX="$InstallPrefix" -DCMAKE_BUILD_TYPE=Release

cmake --build . --config Release

cmake --install . --config Release

Write-Host "lutil installed to $InstallPrefix"
Write-Host "Include headers in $InstallPrefix/include"
Write-Host "Library in $InstallPrefix/lib"

