TARGET = main.out
HDRS_DIR = project/include

SRCS = \
	project/src/main.c \
	project/src/transaction_write.c \
	project/src/master_write.c \
	project/src/black_record.c \
	project/src/file_methods_check.c

.PHONY: all clean

all: $(SRCS)
	$(CC) -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET) $(CFLAGS) $(SRCS)

clean:
	rm -rf $(TARGET)