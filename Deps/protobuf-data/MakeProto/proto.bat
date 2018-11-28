for %%i in (*.proto) do (
    protoc -I=./ --cpp_out=../ %%i
)