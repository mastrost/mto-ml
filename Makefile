BIN=bin

TARGET_0=$(BIN)/math/ml/mlp/mlp.test.cpp.exe
TARGETS+=$(TARGET_0)
TESTS+=$(TARGET_0)
TARGET_0_OBJS+=$(BIN)/math/ml/mlp/mlp.test.cpp.o
TARGET_0_OBJS+=$(BIN)/math/ml/mlp/mlp.h.cpp.o
TARGET_0_OBJS+=$(BIN)/no_stl/string/string.manip.h.cpp.o
TARGET_0_OBJS+=$(BIN)/cpp_tools/defines.h.cpp.o
TARGET_0_OBJS+=$(BIN)/no_stl/string/string.h.cpp.o
TARGET_0_OBJS+=$(BIN)/no_stl/math/functions.h.cpp.o
TARGET_0_OBJS+=$(BIN)/math/ml/expr/compiler/dag_to_ast.h.cpp.o
TARGET_0_OBJS+=$(BIN)/math/ml/model/model.h.cpp.o
TARGET_0_OBJS+=$(BIN)/math/ml/model/loss_functions.h.cpp.o
TARGET_0_OBJS+=$(BIN)/math/ml/expr/expr.h.cpp.o
TARGET_0_OBJS+=$(BIN)/math/ml/expr/compiler/ast.h.cpp.o
TARGET_0_OBJS+=$(BIN)/no_stl/string/string_view.h.cpp.o
TARGET_0_OBJS+=$(BIN)/no_stl/string/c_str_host.h.cpp.o
TARGET_0_OBJS+=$(BIN)/math/ml/expr/compiler/ast_to_c_source.h.cpp.o
TARGET_0_OBJS+=$(BIN)/cpp_tools/unittest.h.cpp.o
TARGET_0_OBJS+=$(BIN)/math/ml/expr/compiler/jit_compiler.h.cpp.o
TARGET_0_OBJS+=$(BIN)/math/ml/expr/dag.h.cpp.o
$(TARGET_0): $(TARGET_0_OBJS)
	@mkdir -p $(dir $@)
	$(CXX) -o "$@" $^ $(LDFLAGS)

TARGET_1=$(BIN)/math/ml/projects/makemore/mlp.main.cpp.exe
TARGETS+=$(TARGET_1)
TARGET_1_OBJS+=$(BIN)/math/ml/projects/makemore/mlp.main.cpp.o
TARGET_1_OBJS+=$(BIN)/no_stl/result/error.h.cpp.o
TARGET_1_OBJS+=$(BIN)/no_stl/string/c_str_host.h.cpp.o
TARGET_1_OBJS+=$(BIN)/no_stl/string/string.h.cpp.o
TARGET_1_OBJS+=$(BIN)/cpp_tools/defines.h.cpp.o
TARGET_1_OBJS+=$(BIN)/cpp_tools/main.h.cpp.o
TARGET_1_OBJS+=$(BIN)/no_stl/string/string_view.h.cpp.o
$(TARGET_1): $(TARGET_1_OBJS)
	@mkdir -p $(dir $@)
	$(CXX) -o "$@" $^ $(LDFLAGS)

TARGET_2=$(BIN)/math/ml/projects/makemore/bigram.main.cpp.exe
TARGETS+=$(TARGET_2)
TARGET_2_OBJS+=$(BIN)/math/ml/projects/makemore/bigram.main.cpp.o
TARGET_2_OBJS+=$(BIN)/cpp_tools/main.h.cpp.o
TARGET_2_OBJS+=$(BIN)/math/ml/mlp/mlp.h.cpp.o
TARGET_2_OBJS+=$(BIN)/no_stl/math/functions.h.cpp.o
TARGET_2_OBJS+=$(BIN)/no_stl/string/string.manip.h.cpp.o
TARGET_2_OBJS+=$(BIN)/no_stl/string/string.h.cpp.o
TARGET_2_OBJS+=$(BIN)/cpp_tools/defines.h.cpp.o
TARGET_2_OBJS+=$(BIN)/math/ml/model/loss_functions.h.cpp.o
TARGET_2_OBJS+=$(BIN)/math/ml/expr/compiler/ast.h.cpp.o
TARGET_2_OBJS+=$(BIN)/math/ml/expr/expr.h.cpp.o
TARGET_2_OBJS+=$(BIN)/math/ml/model/model.h.cpp.o
TARGET_2_OBJS+=$(BIN)/math/ml/expr/compiler/dag_to_ast.h.cpp.o
TARGET_2_OBJS+=$(BIN)/no_stl/string/c_str_host.h.cpp.o
TARGET_2_OBJS+=$(BIN)/no_stl/string/string_view.h.cpp.o
TARGET_2_OBJS+=$(BIN)/math/ml/expr/compiler/ast_to_c_source.h.cpp.o
TARGET_2_OBJS+=$(BIN)/math/ml/expr/compiler/jit_compiler.h.cpp.o
TARGET_2_OBJS+=$(BIN)/no_stl/system/file/file_utils.h.cpp.o
TARGET_2_OBJS+=$(BIN)/no_stl/result/error.h.cpp.o
TARGET_2_OBJS+=$(BIN)/math/ml/expr/dag.h.cpp.o
$(TARGET_2): $(TARGET_2_OBJS)
	@mkdir -p $(dir $@)
	$(CXX) -o "$@" $^ $(LDFLAGS)

TARGET_3=$(BIN)/math/ml/expr/compiler/ast_to_c_source.h.test.cpp.exe
TARGETS+=$(TARGET_3)
TESTS+=$(TARGET_3)
TARGET_3_OBJS+=$(BIN)/math/ml/expr/compiler/ast_to_c_source.h.cpp.o
TARGET_3_OBJS+=$(BIN)/math/ml/expr/compiler/ast.h.cpp.o
TARGET_3_OBJS+=$(BIN)/no_stl/string/c_str_host.h.cpp.o
TARGET_3_OBJS+=$(BIN)/math/ml/expr/compiler/ast_to_c_source.h.test.cpp.o
TARGET_3_OBJS+=$(BIN)/no_stl/string/string_view.h.cpp.o
TARGET_3_OBJS+=$(BIN)/cpp_tools/unittest.h.cpp.o
TARGET_3_OBJS+=$(BIN)/no_stl/string/string.h.cpp.o
TARGET_3_OBJS+=$(BIN)/cpp_tools/defines.h.cpp.o
$(TARGET_3): $(TARGET_3_OBJS)
	@mkdir -p $(dir $@)
	$(CXX) -o "$@" $^ $(LDFLAGS)

TARGET_4=$(BIN)/math/ml/expr/compiler/dag_to_ast.test.cpp.exe
TARGETS+=$(TARGET_4)
TESTS+=$(TARGET_4)
TARGET_4_OBJS+=$(BIN)/math/ml/expr/compiler/dag_to_ast.h.cpp.o
TARGET_4_OBJS+=$(BIN)/cpp_tools/unittest.h.cpp.o
TARGET_4_OBJS+=$(BIN)/math/ml/expr/dag.h.cpp.o
TARGET_4_OBJS+=$(BIN)/math/ml/expr/compiler/ast_to_c_source.h.cpp.o
TARGET_4_OBJS+=$(BIN)/math/ml/expr/expr.h.cpp.o
TARGET_4_OBJS+=$(BIN)/cpp_tools/defines.h.cpp.o
TARGET_4_OBJS+=$(BIN)/no_stl/string/string.h.cpp.o
TARGET_4_OBJS+=$(BIN)/no_stl/string/string.manip.h.cpp.o
TARGET_4_OBJS+=$(BIN)/no_stl/math/functions.h.cpp.o
TARGET_4_OBJS+=$(BIN)/no_stl/string/string_view.h.cpp.o
TARGET_4_OBJS+=$(BIN)/math/ml/expr/compiler/dag_to_ast.test.cpp.o
TARGET_4_OBJS+=$(BIN)/no_stl/string/c_str_host.h.cpp.o
TARGET_4_OBJS+=$(BIN)/math/ml/expr/compiler/ast.h.cpp.o
$(TARGET_4): $(TARGET_4_OBJS)
	@mkdir -p $(dir $@)
	$(CXX) -o "$@" $^ $(LDFLAGS)

TARGET_5=$(BIN)/math/ml/model/model.test.cpp.exe
TARGETS+=$(TARGET_5)
TESTS+=$(TARGET_5)
TARGET_5_OBJS+=$(BIN)/no_stl/string/string.manip.h.cpp.o
TARGET_5_OBJS+=$(BIN)/cpp_tools/defines.h.cpp.o
TARGET_5_OBJS+=$(BIN)/math/ml/model/model.test.cpp.o
TARGET_5_OBJS+=$(BIN)/no_stl/string/string.h.cpp.o
TARGET_5_OBJS+=$(BIN)/no_stl/math/functions.h.cpp.o
TARGET_5_OBJS+=$(BIN)/math/ml/expr/compiler/dag_to_ast.h.cpp.o
TARGET_5_OBJS+=$(BIN)/math/ml/model/model.h.cpp.o
TARGET_5_OBJS+=$(BIN)/math/ml/model/loss_functions.h.cpp.o
TARGET_5_OBJS+=$(BIN)/math/ml/expr/expr.h.cpp.o
TARGET_5_OBJS+=$(BIN)/math/ml/expr/compiler/ast.h.cpp.o
TARGET_5_OBJS+=$(BIN)/no_stl/string/string_view.h.cpp.o
TARGET_5_OBJS+=$(BIN)/no_stl/string/c_str_host.h.cpp.o
TARGET_5_OBJS+=$(BIN)/math/ml/expr/compiler/ast_to_c_source.h.cpp.o
TARGET_5_OBJS+=$(BIN)/cpp_tools/unittest.h.cpp.o
TARGET_5_OBJS+=$(BIN)/math/ml/expr/compiler/jit_compiler.h.cpp.o
TARGET_5_OBJS+=$(BIN)/math/ml/expr/dag.h.cpp.o
$(TARGET_5): $(TARGET_5_OBJS)
	@mkdir -p $(dir $@)
	$(CXX) -o "$@" $^ $(LDFLAGS)


CXXFLAGS+=-std=c++20 -I. -O3

include $(shell test -d $(BIN) && find $(BIN) -name "*.dep")

$(BIN)/%.cpp.o: %.cpp 
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o "$@" $<
	$(CXX) $(CXXFLAGS) -MM -MT "$@" -c -o "$(BIN)/$*.dep" $<

all:$(TARGETS)

test:$(TESTS)
	@for exe in $(TESTS); do \
		printf "testing $$exe: "; \
		./$$exe > /dev/null 2>&1 && printf "OK\n" || printf "FAILED\n"; \
	done

.DEFAULT_GOAL := all

clean:
	rm -rf $(BIN)

.PHONY: clean all test
