# Reset rápido para corrigir conflitos locais de build no Windows.
# Uso (PowerShell):
#   powershell -ExecutionPolicy Bypass -File .\tools\reset_windows_build.ps1

$ErrorActionPreference = "Stop"

Write-Host "[1/4] Limpando artefatos locais..."
Remove-Item -Force -ErrorAction SilentlyContinue parser_cli.exe, parser_wx.exe, parser_cli, parser_wx
Get-ChildItem src -Filter *.o -ErrorAction SilentlyContinue | Remove-Item -Force -ErrorAction SilentlyContinue
Remove-Item -Force -ErrorAction SilentlyContinue app\test_cli.o

Write-Host "[2/4] Verificando marcadores de conflito..."
$conflicts = Select-String -Path Makefile, src\udpipe_pipeline.cpp -Pattern '<<<<<<<|=======|>>>>>>>' -SimpleMatch -ErrorAction SilentlyContinue
if ($conflicts) {
  Write-Host "[ERRO] Marcadores de conflito encontrados em arquivos críticos." -ForegroundColor Red
  $conflicts | ForEach-Object { Write-Host (" - " + $_.Path + ":" + $_.LineNumber) }
  exit 1
}

Write-Host "[3/4] Build CLI..."
make clean
make
if ($LASTEXITCODE -ne 0) {
  Write-Host "[ERRO] Falha no make." -ForegroundColor Red
  exit $LASTEXITCODE
}

Write-Host "[4/4] Teste rápido..."
./parser_cli.exe data/input.txt
if ($LASTEXITCODE -ne 0) {
  Write-Host "[ERRO] parser_cli.exe falhou." -ForegroundColor Red
  exit $LASTEXITCODE
}

Write-Host "Concluído com sucesso." -ForegroundColor Green
