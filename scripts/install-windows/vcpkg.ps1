$project_root=$PSscriptRoot + "\..\..\"
$vcpkg_dir=$project_root + "vcpkg\"

Write-Output $vcpkg_dir

if (-not (Test-Path -Path $vcpkg_dir)) {
    git clone https://github.com/microsoft/vcpkg.git
    Invoke-Expresssion "$vcpkg_dir\bootstrap-vcpkg.bat"
}
Invoke-Expression "$vcpkg_dir\vcpkg.exe --triplet x64-windows-static install spdlog fmt corrade magnum boost magnum-plugins[freetypefont] magnum-extras[ui] corrade freetype"
