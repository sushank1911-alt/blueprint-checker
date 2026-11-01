CC = clang
# Use MacOSX.sdk sysroot if present on macOS to avoid ld TAPI version mismatch
SYSROOT_FLAG := $(shell [ -d /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk ] && echo "-isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk")

CFLAGS = -Wall -Wextra -std=c99 $(SYSROOT_FLAG)
OBJS = main.o blueprint.o question_paper.o analysis.o checker.o report.o ai_helper.o
TARGET = blueprint_checker

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c models.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) audit_report.txt blueprint.txt question_paper.txt

.PHONY: all run clean
