build:
	#!/usr/bin/env bash
	if [[ ! -d target ]]; then mkdir target; fi
	for file in source/*.c; do
		filename=$(basename -- "$file")
		filename="${filename%.*}"
		clang -c "$file" -o "target/$filename.o" -Isource/include -std=c23
	done
	ar r target/libvec.a target/*.o

clean:
	rm -rf target
