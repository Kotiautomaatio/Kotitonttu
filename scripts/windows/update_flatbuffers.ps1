$project_root=$PSscriptRoot + "\..\..\"
$currentLocation = Get-Location
$flatBufferLocation = "$project_root\kotitonttu\flatbuffers\"
Set-Location $flatBufferLocation
$flatbufferFiles = Get-ChildItem -Path .\ -Filter *.fbs -Recurse -File -Name

foreach ($flatbufferFile in $flatbufferFiles) {
    flatc --cpp $flatbufferFile;
    $fileName = [io.path]::GetFileNameWithoutExtension($flatbufferFile)
    Rename-Item -Path ($fileName+"_generated.h") -NewName ($fileName+".h")
}
Set-Location $currentLocation