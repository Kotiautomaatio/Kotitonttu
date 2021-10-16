$project_root=$PSscriptRoot + "\..\..\"
$vcpkg_dir=$project_root + "vcpkg\"

Write-Output $vcpkg_dir

if (-not (Test-Path -Path $vcpkg_dir)) {
    git clone https://github.com/microsoft/vcpkg.git
    Invoke-Expression "$vcpkg_dir\bootstrap-vcpkg.bat"
}

Function Add-PathVariable {
    param (
        [string]$addPath
    )
    if (Test-Path $addPath){
        $regexAddPath = [regex]::Escape($addPath)
        $arrPath = $env:Path -split ';' | Where-Object {$_ -notMatch
                "^$regexAddPath\\?"}
        $env:Path = ($arrPath + $addPath) -join ';'
        Set-ItemProperty -Path 'Registry::HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\Session Manager\Environment' -Name PATH -Value $env:Path
    } else {
        Throw "'$addPath' is not a valid path."
    }
}

function Run-Elevated ($scriptblock)
{
    $sh = new-object -com 'Shell.Application'
    $sh.ShellExecute('powershell', "-NoExit -Command $scriptblock", '', 'runas')
}

$packages= $(
'spdlog'
'fmt'
'corrade'
'magnum'
'boost'
'magnum-plugins[freetypefont]'
'magnum-extras[ui]'
'corrade'
'freetype'
'flatbuffers'
)

Invoke-Expression "$vcpkg_dir\vcpkg.exe --triplet x64-windows-static install $packages"

Add-PathVariable("$vcpkg_dir\installed\x64-windows-static\tools\flatbuffers")