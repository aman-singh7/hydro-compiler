generate:
	@cmake -S . -B build/ && cmake --build build/

run: generate
	@./build/hydro