OUT ?= build
NAME := huawei-bl-bruteforce

CC ?= clang

CFLAGS := \
	-O3 \
	-Wall 

CFILES=$(shell find src -name *.c -type f)
HFILES=$(shell find src -name *.h -type f)

OBJS := $(patsubst %.c, $(OUT)/%.o, $(CFILES))

$(OUT)/%.o: %.c $(CFILES)
	@mkdir -p $(OUT)/src
	@echo -e "\x1b[1;95m[ CC ]\x1b[0;0m $<"
	@$(CC) -c $(CFLAGS) -I src -o $@ $<

$(OUT): $(OBJS)
	@mkdir -p $(OUT)
	@echo -e "\x1b[1;95m[ BIN ]\x1b[0;0m $(OUT)/$(NAME)"
	@$(CC) $(OBJS) -o $(OUT)/$(NAME)

all: $(OUT)

$(NAME): $(OUT)

clean:
	@echo -e "\x1b[1;95m[ RM ]\x1b[0;0m $(OUT)"
	@rm -rf $(OUT)

strip: $(NAME)
	@echo -e "\x1b[1;95m[ STRIP ]\x1b[0;0m $(OUT)/$(NAME)"
	@strip -s $(OUT)/$(NAME)

run: $(NAME)
	@echo -e "\x1b[1;95m[ RUN ]\x1b[0;0m $(OUT)/$(NAME)"
	@$(OUT)/$(NAME)
