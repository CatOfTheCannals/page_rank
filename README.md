# page_rank_tp1_metodos
Link del informe en OverLeaf:
https://www.overleaf.com/17618777pywgphbhcbds#/66872127/
## para compilar con cmake desde la terminal:

`cmake .` en la carpeta principal del repo. esto crea los "Makefiles" (necesarios para poder usar `make`)

si tira error, correr `./scripts/cmake_clean.sh` (o mirarlo y borrar los archivos que figuran ahí a mano)

### para compilar nuestro programa

tirar `make` en la carpeta principal del repo

se va a crear el ejecutable "main", correrlo: `./main`

### para compilar los tests

ir a la carpeta "test": `cd test`

tirar `make`, se crea "correrTests", correrlo: `./correrTests`

