
# I don't know how to `cmake clean` the same way I do with `make`
# There's probably a better way to do this
# Meanwhile...

rm 	Makefile
rm 	gtest.pc
rm 	gtest_main.pc
rm 	test/Makefile
rm -rf test/googletest-build/
rm -rf test/googletest-download/
rm -rf test/googletest-src/

