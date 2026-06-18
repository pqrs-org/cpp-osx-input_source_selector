CLANG_FORMAT_FILES = \
	'example/*.cpp' \
	'example-app/*.h' \
	'example-app/*.mm' \
	'include/*.hpp' \
	'tests/*.cpp' \
	'tests/*.hpp'

format: clang-format

clang-format:
	git ls-files -z -- $(CLANG_FORMAT_FILES) | xargs -0 clang-format -i
