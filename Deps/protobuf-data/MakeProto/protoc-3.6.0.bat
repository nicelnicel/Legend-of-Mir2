for %%i in (*.proto) do (
    protoc-3.6.0 -I=./ --cpp_out=../ %%i
)