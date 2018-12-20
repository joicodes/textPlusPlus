## How to run Tests:

#### Installing Libharu:

Before installation  the following dependecies are required:

```
sudo apt-get install automake autoconf zlib1g-dev libpng-dev libtool
```

Installing libharu

```
tar -xvsf libharu-X.X.X.tar.gz
cd libharu-X.X.X
```

Run the configuration scipt

```
./configure
```

If there is no configuration script
```
./buildconf.sh --force
```
Then try running `./configure` again

Build the Library and install
```
make clean
make
make install
```
If there are errors about not being able to find the `*.so` file or  a missing directory. 
Please execute the following:
```
ldconfig /usr/local/lib
```

#### Installing pdf2txt
pdf2txt is needed in order to run tests
```
sudo apt-get install python-pdfminer
```

#### Run Tests:
Assuming that LLVM, LLI, OPAM, OCAML, Ocamlbuild, etc are installed, run:
```
make
```

A file called `text.pdf` is produced. 

