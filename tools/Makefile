.PHONY: all header done

all: header $(BIN)/fat done

header:
	@echo "Building tools..."

done:
	@echo "Built tools..."
	@echo $0


$(BIN)/fat: fat.c
	echo "Building fat..."
	$(CC) $(CCFLAGS) fat.c -o $(BIN)/fat
