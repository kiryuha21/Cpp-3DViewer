CC = g++ -std=c++17 -Wall -Werror -Wextra -Wuninitialized
GTK_FLAGS = `pkg-config gtkmm-3.0 --cflags --libs`
GTEST_LIBS = -lgtest
BOOST_LIBS = -lboost_iostreams
DELETE = rm -rf

FIND_VALGRIND_ERRORS = grep --color=always -n "ERROR SUMMARY" $(VALGRIND_OUTPUT) | grep -v "0 errors from 0 contexts" || true
FIND_VALGRIND_LEAKS = grep --color=always -n "definitely lost:" $(VALGRIND_OUTPUT) | grep -v "0 bytes in 0 blocks" || true
VALGRIND = valgrind --log-file="$(VALGRIND_OUTPUT)" --track-origins=yes --trace-children=yes --leak-check=full --leak-resolution=med

VALGRIND_OUTPUT = valgrind.txt
PROGRAM_OUTPUTS = plot.png points.txt

TARGET_PATH = build
TEST_TARGET  = 3DViewerTests
BUILD_TARGET = 3DViewer

SRC_FILES = controller/*.cc \
			model/*.cc \
			view/*.cc \
			main.cc
TEST_FILES = controller/*.cc \
			 model/*.cc \
			 tests/*.cc
BUILD_PATH = build

CLANG_FORMAT = clang-format

.PHONY: all install uninstall tests clean style valgrind $(CLANG_FORMAT)

all: tests run dvi dist

install: build
	install ./$(TARGET_PATH)/$(BUILD_TARGET) /usr/local/bin
	mkdir -p /usr/local/bin/ui
	cp ui/* /usr/local/bin/ui

uninstall:
	$(DELETE) /usr/local/bin/ui
	$(DELETE) /usr/local/bin/$(BUILD_TARGET)

dvi: clean_dvi
	doxygen Doxyfile
	open docs/html/index.html

dist: build
	mv $(TARGET_PATH)/$(BUILD_TARGET) .
	tar -czvf $(BUILD_TARGET).tgz $(BUILD_TARGET) ui/*
	$(DELETE) $(BUILD_TARGET)

build_path:
	mkdir -p $(TARGET_PATH)

build: style build_path
	$(CC) $(SRC_FILES) -o $(TARGET_PATH)/$(BUILD_TARGET) $(GTK_FLAGS) $(BOOST_LIBS)

run: build
	./$(TARGET_PATH)/$(BUILD_TARGET)

tests: style build_path
	$(CC) $(TEST_FILES) -o $(TARGET_PATH)/$(TEST_TARGET) $(GTEST_LIBS) $(BOOST_LIBS)
	./$(TARGET_PATH)/$(TEST_TARGET)

clean_dvi:
	$(DELETE) docs/*

clean_dist:
	$(DELETE) $(BUILD_TARGET).tgz

clean: clean_dvi clean_dist
	$(DELETE) $(TARGET_PATH)/$(TEST_TARGET) $(TARGET_PATH)/$(BUILD_TARGET) $(VALGRIND_OUTPUT) $(PROGRAM_OUTPUTS)

style: $(CLANG_FORMAT)

$(CLANG_FORMAT):
	$(CLANG_FORMAT) --style=Google -i $(wildcard */*.cc *.cc */*.h *.h) || true

valgrind: tests
	$(VALGRIND) ./$(TARGET_PATH)/$(TEST_TARGET) || true
	$(FIND_VALGRIND_ERRORS)
	$(FIND_VALGRIND_LEAKS)
