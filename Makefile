CXX = g++
CXXFLAGS = -std=c++17 -O0 -g -Wall -Iinclude
TARGET = program
SRC_DIR = src
OBJ_DIR = obj


# 搜索所有 .cpp 文件并替换为 .o 文件
SRC = $(wildcard $(SRC_DIR)/*.cpp)  # 获取 src 目录下所有 .cpp 文件
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC)) # 替换为 .o 文件路径


# 默认目标
all: $(TARGET)

# 链接目标
$(TARGET): $(OBJ)
	$(CXX) -o $@ $^

# 编译 .cpp 文件生成 .o 文件
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR) # 确保目标文件目录存在
	$(CXX) $(CXXFLAGS) -c $< -o $@

clangd: clean
	bear -- make

# 清理生成的文件
clean:
	rm -rf $(OBJ_DIR) $(TARGET)


# 伪目标
.PHONY: all clean
