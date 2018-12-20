# "make test" Compiles everything and runs the regression tests

.PHONY : test
test : all testall.sh
	./testall.sh

# "make all" builds the executable as well as the "hello" library designed
# to test linking external code

.PHONY : all
all : textplusplus.native hello.o

# "make textplusplus.native" compiles the compiler
#
# The _tags file controls the operation of ocamlbuild, e.g., by including
# packages, enabling warnings


textplusplus.native :
	opam config exec -- \
	ocamlbuild -use-ocamlfind textplusplus.native

# "make clean" removes all generated files

.PHONY : clean
clean :
	ocamlbuild -clean
	rm -rf testall.log ocamlllvm *.diff test-*.exe test-*.ll test-*.out test-*.s text.pdf

# Testing the "hello" example

hello : hello.c
	 cc -o hello -DBUILD_TEST hello.c

# Building the tarball

TESTS = \
  hello wrap left-wrap right-wrap center-wrap add-page get-cap-height get-low-height \
  get-bytes left-margin right-margin top-margin bot-margin text-out regular italic bold \
  draw-line rect

FAILS = \
  

TESTFILES = $(TESTS:%=test-%.tpp) $(TESTS:%=test-%.out) \
	    $(FAILS:%=fail-%.tpp) $(FAILS:%=fail-%.err)

TARFILES = ast.ml sast.ml codegen.ml Makefile _tags textplusplus.ml parser.mly \
	README scanner.mll semant.ml testall.sh \
	hello.c \
	$(TESTFILES:%=tests/%) 

textPlusPlus.tar.gz : $(TARFILES)
	cd .. && tar czf textPlusPlus/textPlusPlus.tar.gz \
		$(TARFILES:%=textPlusPlus/%)
