computing deps of /home/thierry/git/mto-ml/bin_release/math/ml/mlp/mlp.test.depcomputing deps of /home/thierry/git/mto-ml/bin_release/math/ml/expr/dag.h.dep
computing deps of /home/thierry/git/mto-ml/bin_release/math/ml/mlp/mlp.h.dep
computing deps of /home/thierry/git/mto-ml/bin_release/math/ml/expr/expr.h.dep

computing deps of /home/thierry/git/mto-ml/bin_release/math/ml/model/model.h.dep
computing deps of /home/thierry/git/mto-ml/bin_release/math/ml/model/loss_functions.h.dep
computing deps of /home/thierry/git/mto-ml/bin_release/no_stl/math/functions.h.dep
computing deps of /home/thierry/git/mto-ml/bin_release/math/ml/model/model.test.dep
computing deps of /home/thierry/git/mto-ml/bin_release/cpp_tools/defines.h.dep
computing deps of /home/thierry/git/mto-ml/bin_release/cpp_tools/unittest.h.dep
BIN=bin

TARGET_0=$(BIN)/math/ml/mlp/mlp.test.cpp.exe
TARGETS+=$(TARGET_0)
TARGET_0_OBJS+=$(BIN)/math/ml/model/loss_functions.h.cpp.o
TARGET_0_OBJS+=$(BIN)/math/ml/mlp/mlp.h.cpp.o
TARGET_0_OBJS+=$(BIN)/math/ml/expr/dag.h.cpp.o
TARGET_0_OBJS+=$(BIN)/math/ml/mlp/mlp.test.cpp.o
TARGET_0_OBJS+=$(BIN)/math/ml/model/model.h.cpp.o
TARGET_0_OBJS+=$(BIN)/cpp_tools/unittest.h.cpp.o
TARGET_0_OBJS+=$(BIN)/no_stl/math/functions.h.cpp.o
TARGET_0_OBJS+=$(BIN)/math/ml/expr/expr.h.cpp.o
TARGET_0_OBJS+=$(BIN)/cpp_tools/defines.h.cpp.o
$(TARGET_0): $(TARGET_0_OBJS)
	@mkdir -p $(dir $@)
	$(CXX) -o "$@" $^ $(LDFLAGS)

TARGET_1=$(BIN)/math/ml/model/model.test.cpp.exe
TARGETS+=$(TARGET_1)
TARGET_1_OBJS+=$(BIN)/math/ml/model/loss_functions.h.cpp.o
TARGET_1_OBJS+=$(BIN)/math/ml/expr/dag.h.cpp.o
TARGET_1_OBJS+=$(BIN)/math/ml/model/model.test.cpp.o
TARGET_1_OBJS+=$(BIN)/math/ml/model/model.h.cpp.o
TARGET_1_OBJS+=$(BIN)/cpp_tools/unittest.h.cpp.o
TARGET_1_OBJS+=$(BIN)/no_stl/math/functions.h.cpp.o
TARGET_1_OBJS+=$(BIN)/math/ml/expr/expr.h.cpp.o
TARGET_1_OBJS+=$(BIN)/cpp_tools/defines.h.cpp.o
$(TARGET_1): $(TARGET_1_OBJS)
	@mkdir -p $(dir $@)
	$(CXX) -o "$@" $^ $(LDFLAGS)


CXXFLAGS+=-std=c++20 -I. -O3

include $(shell test -d $(BIN) && find $(BIN) -name "*.dep")

$(BIN)/%.cpp.o: %.cpp 
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o "$@" $<
	$(CXX) $(CXXFLAGS) -MM -MT "$@" -c -o "$(BIN)/$*.dep" $<

all:$(TARGETS)

.DEFAULT_GOAL := all

clean:
	rm -rf $(BIN)

.PHONY: clean all
