# Repara conflitos locais comuns em Windows (PowerShell)
$ErrorActionPreference = "Stop"

Write-Host "Restaurando Makefile e src/udpipe_pipeline.cpp a partir de templates limpos..."
Copy-Item -Force tools\templates\Makefile.clean Makefile
Copy-Item -Force tools\templates\udpipe_pipeline.clean.cpp src\udpipe_pipeline.cpp

Write-Host "Verificando marcadores de conflito..."
$conflicts = Select-String -Path Makefile, src\udpipe_pipeline.cpp -Pattern '<<<<<<<|=======|>>>>>>>' -SimpleMatch -ErrorAction SilentlyContinue
if ($conflicts) {
  Write-Host "Ainda existem marcadores de conflito." -ForegroundColor Red
  exit 1
}

Write-Host "Compilando..."
make clean
make
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

Write-Host "Executando teste rápido..."
./parser_cli.exe data/input.txt
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

Write-Host "Reparo concluído com sucesso." -ForegroundColor Green
