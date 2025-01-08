CC		 = gcc
BIN		 = TCC
OBJDIR   = build
SRCDIR   = src
SRCS     = $(wildcard $(SRCDIR)/*.c)
OBJS     = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
CFLAGS   = -g3 -std=c99 -Wall -Wextra -Wpedantic -O0
RM       = rm -rf

$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $(BIN) -lm

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJDIR) $(BIN)