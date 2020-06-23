all:
	[ -d build ] || mkdir build
	eosio-cpp -o build/addressbook.wasm addressbook.cpp -abigen -I . -R .
