CC := 					gcc
CCFLAGS := 				-c -Wall -Werror -Wextra
CC_LINKING_FLAGS := 	-Wall -Werror -Wextra
DEBUG_FLAG :=			-g

PROFILING_FLAGS := 		-fprofile-arcs -ftest-coverage -g
CHECK_LIB_FLAGS := 		$(shell pkg-config --libs check)
CHECK_INC_FLAGS := 		$(shell pkg-config --cflags-only-I check)

SRC_DIR := 				.
OBJ_DIR := 				$(SRC_DIR)/objects
OUT_DIR := 				$(SRC_DIR)/build
COVERAGE_DIR := 		$(SRC_DIR)/coverage_report
COVERAGE_FILE := 		$(SRC_DIR)/coverage.info
LOG_DIR := 				$(SRC_DIR)/logs

LIB_NAME := 			s21_string.a
LIB_NAME_PROFILED := 	s21_string_profiled.a
LIB_NAME_DEBUG := 		s21_string_debug.a

SRC := 					$(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/s21_*/*.c)
OBJ := 					$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
OBJ_PROFILED := 		$(OBJ:.o=_profiled.o)
OBJ_DEBUG := 			$(OBJ:.o=_debug.o)

TEST_SRC_DIR := 		$(SRC_DIR)/tests
TEST_OBJ_DIR := 		$(OBJ_DIR)/tests
TEST_OUT_DIR := 		$(OUT_DIR)/tests

TEST_CHECK := 			$(wildcard $(TEST_SRC_DIR)/*.check)
TEST_NAMES := 			$(basename $(notdir $(TEST_CHECK)))

TEST_OBJ := 			$(patsubst %, $(TEST_OBJ_DIR)/%.o, $(TEST_NAMES))
TEST_OBJ_PROFILED := 	$(TEST_OBJ:.o, _profiled.o)
TEST_EXEC := 			$(addprefix $(TEST_OUT_DIR)/, $(TEST_NAMES))
TEST_EXEC_PROFILED := 	$(addsuffix _profiled, $(TEST_EXEC))

DIR_GUARD = 			@mkdir -p $(@D)

.PHONY: 				tests cpplint clean gcov_report tests_profiled
.SILENT: 				gcov_report

t:
	@echo $(CCFLAGS)
	CCFLAGS+=1 


all: $(LIB_NAME)

cpplint:
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extension=c ./*.c ./*/*.c ./*.h ./*/*.h
	rm CPPLINT.cfg

gcov_report: tests_profiled
	lcov --capture --directory $(OBJ_DIR) \
		--exclude *Library/Developer* --exclude *src/tests* \
		--output-file $(COVERAGE_FILE)
	genhtml $(COVERAGE_FILE) --output-directory $(COVERAGE_DIR)
	@echo report created and saved at "$(COVERAGE_DIR)"

test tests: $(TEST_EXEC)
	for test_debug in $(TEST_EXEC); do $$test_debug ; done

tests_profiled: $(TEST_EXEC_PROFILED)
	for tests_profiled in $(TEST_EXEC_PROFILED); do $$tests_profiled ; done

test_%: $(TEST_OUT_DIR)/test_%
	./$^

valgrind_tests: $(TEST_EXEC) | $(LOG_DIR)
	for test in $(TEST_EXEC); do valgrind \
		 --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=$(LOG_DIR)/$$(basename $$test).log \
		$$test ; done

$(LIB_NAME): $(OBJ)
	$(AR) rcs $@ $^

$(LIB_NAME_PROFILED): $(OBJ_PROFILED)
	$(AR) rcs $@ $^

$(LIB_NAME_DEBUG): $(OBJ_DEBUG)
	$(AR) rcs $@ $^	

# Link PROFILED `tests` executables. Neccessery flags for gcov report is ON.
$(TEST_OUT_DIR)/%_profiled: $(TEST_OBJ_DIR)/%.o $(LIB_NAME_PROFILED)
	$(DIR_GUARD)
	$(CC) $(CC_LINKING_FLAGS) $(PROFILING_FLAGS) $^ -o $@ $(CHECK_LIB_FLAGS)

# Link `tests` executables. Debug is on for convenience.
$(TEST_OUT_DIR)/%: $(TEST_OBJ_DIR)/%.o $(LIB_NAME_DEBUG)
	$(DIR_GUARD)
	$(CC) $(CC_LINKING_FLAGS) $(DEBUG_FLAG) $^ -o $@ $(CHECK_LIB_FLAGS)

# Compile tests .C files to objects. Neccessery flags included
$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.c
	$(DIR_GUARD)
	$(CC) $(CCFLAGS) $(DEBUG_FLAG) $(CHECK_INC_FLAGS) $< -o $@

# Generate test .C source file based on .check template
$(TEST_SRC_DIR)/%.c: $(TEST_SRC_DIR)/%.check
	checkmk $^ > $@

# Compile PROFILED SRC .C files (for coverage report)
$(OBJ_DIR)/%_profiled.o: $(SRC_DIR)/%.c
	$(DIR_GUARD)
	$(CC) $(CCFLAGS) $(PROFILING_FLAGS) $(CHECK_INC_FLAGS) $^ -o $@

# Compile SRC .C files with DEBUG=ON
$(OBJ_DIR)/%_debug.o: $(SRC_DIR)/%.c
	$(DIR_GUARD)
	$(CC) $(CCFLAGS) $(DEBUG_FLAG) $(CHECK_INC_FLAGS) $^ -o $@

# Compile ordinary SRC .C files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_GUARD)
	$(CC) $(CCFLAGS) $< -o $@


$(LOG_DIR):
	mkdir -p $(LOG_DIR)

clean:
	rm -rf $(OBJ_DIR) $(OUT_DIR) $(LOG_DIR) \
		   $(COVERAGE_FILE) $(COVERAGE_DIR) \
		   $(LIB_NAME) $(LIB_NAME_PROFILED) $(LIB_NAME_DEBUG)
