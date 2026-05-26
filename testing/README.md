# Required .dll
- gdi32 (for GetStockObject)
- winmm (for PlaySound)

## Note
When compiling the C program, add `-lgdi32`, `-lwinmm`, ... (other required .dll, if any)