CC = g++
SRCDIR = src
BUILDDIR = build
TARGET = $(BUILDDIR)/run_pipeline
SOURCES = $(SRCDIR)/run_pipeline.cpp
CFLAGS = -std=c++1z -g -Wall
LIB =
INC = -I /usr/include -I $(SRCDIR)
LIBRARIES = $(BUILDDIR)/perceptron.so
LIBSOURCES =$(SRCDIR)/transformers/perceptron.cpp

$(TARGET): $(SOURCES) 
	@echo "Building main executor"
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) $^ -o $(TARGET) $(LIB)

$(LIBRARIES): $(LIBSOURCES)
	@echo "Building shared libraries for transformers..."
	$(CC) -fPIC $(CFLAGS) $(INC) $(lib) -shared -o $@ $< -shared; \

.PHONY: transformers $(LIBRARIES)
transformers: $(LIBRARIES)

all : transformers $(TARGET)
.PHONY : all

.PHONY: clean
clean:
	echo " Cleaning..."
	rm -rf $(BUILDDIR) $(TARGET)

