TARGET = main.out
HDRS_DIR = project/include

SRCS = \
	project/src/main.c \
	project/src/transactionWrite.c \
	project/src/masterWrite.c \
	project/src/blackRecord.c \
	project/src/file_methods_check.c

.PHONY: all clean

all: $(SRCS)
	$(CC) -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET) $(CFLAGS) $(SRCS)

clean:
	rm -rf $(TARGET)