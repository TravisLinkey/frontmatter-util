CXX = clang++
SDKROOT = $(shell xcrun --show-sdk-path)
# Explicit C++ stdlib path (in case -isysroot breaks default search)
CXXFLAGS = -std=c++17 -Wall -I. -isysroot $(SDKROOT) -I$(SDKROOT)/usr/include/c++/v1

SOURCES = main.cpp \
	utils/io.cpp \
	utils/processor.cpp \
	utils/traversal.cpp \
	utils/string_utils.cpp \
	utils/file_utils.cpp

main.o: $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o main.o

.PHONY: clean
clean:
	rm -f main.o
