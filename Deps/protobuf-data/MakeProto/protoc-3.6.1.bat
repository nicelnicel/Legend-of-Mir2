for %%i in (*.proto) do (
    protoc-3.6.1 -I=./ --cpp_out=../ %%i
)