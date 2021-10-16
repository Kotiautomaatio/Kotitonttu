
Start-Process -Verb RunAs powershell.exe -Args "-executionpolicy bypass -command Set-Location \`"$PWD\`"; .\install-windows\vcpkg.ps1"