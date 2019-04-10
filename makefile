# ===================== COMPILER OPTIONS ======================

CXX=g++
CFLAGS=-std=c++17 -I. -g -rdynamic -Wall -Wextra 

# ===================== PRE-REQUISITES =====================

MKDIR= mkdir -p
OUTPUT_DIR= obj/server/commands obj/client/commands obj/utils bin
RM= rm -rf

# ===================== SERVER =====================

SERVER_SRC_DIR=src/server
SERVER_OBJ_DIR=obj/server
SERVER_BIN_DIR=bin

SERVER_INCLUDE_FILES=$(shell find ./src/server -name "*.hpp")
SERVER_SRC_FILES=$(shell find ./src/server -name "*.cpp")
SERVER_OBJ_FILES=$(shell find ./src/server -name "*.cpp" |  sed -r 's/src/obj/g' | sed -r 's/cpp/o/g')

# ===================== CLIENT =====================

CLIENT_SRC_DIR=src/client
CLIENT_OBJ_DIR=obj/client
CLIENT_BIN_DIR=bin

CLIENT_INCLUDE_FILES=$(shell find ./src/client -name "*.hpp")
CLIENT_SRC_FILES=$(shell find ./src/client -name "*.cpp")
CLIENT_OBJ_FILES=$(shell find ./src/client -name "*.cpp" |  sed -r 's/src/obj/g' | sed -r 's/cpp/o/g')

# ===================== UTILS =====================

UTILS_SRC_DIR=src/utils
UTILS_OBJ_DIR=obj/utils
UTILS_BIN_DIR=bin

UTILS_INCLUDE_FILES=$(shell find ./src/utils -name "*.hpp")
UTILS_SRC_FILES=$(shell find ./src/utils -name "*.cpp")
UTILS_OBJ_FILES=$(shell find ./src/utils -name "*.cpp" |  sed -r 's/src/obj/g' | sed -r 's/cpp/o/g')


# ===================== MAKE RULES =====================


# First Rule : always to be execute by `make` 
all: directories server client
	@echo "Build successful."


# ============= make DIRECTORIES ====================

.PHONY: directories

directories: ${OUTPUT_DIR}
	@echo "Created Output "$@" successfully!"

${OUTPUT_DIR}:
	${MKDIR} ${OUTPUT_DIR}

# =============== make SERVER ========================

server: $(SERVER_OBJ_FILES) $(UTILS_OBJ_FILES) $(SERVER_INCLUDE_FILES)
	$(CXX) $(CFLAGS) -c -o $(SERVER_OBJ_DIR)/main.o $(SERVER_SRC_DIR)/main.cpp
	$(CXX) $(CFLAGS) -o $(SERVER_BIN_DIR)/$@ $(SERVER_OBJ_FILES) $(UTILS_OBJ_FILES)
	@echo "Compiled "$@" successfully!"

$(SERVER_OBJ_DIR)/%.o: $(SERVER_SRC_DIR)/%.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

# =============== make CLIENT ========================

client: $(CLIENT_OBJ_FILES) $(UTILS_OBJ_FILES) $(CLIENT_INCLUDE_FILES)
	$(CXX) $(CFLAGS) -c -o $(CLIENT_OBJ_DIR)/main.o $(CLIENT_SRC_DIR)/main.cpp
	$(CXX) $(CFLAGS) -o $(CLIENT_BIN_DIR)/$@ $(CLIENT_OBJ_FILES) $(UTILS_OBJ_FILES)
	@echo "Compiled "$@" successfully!"

$(CLIENT_OBJ_DIR)/%.o: $(CLIENT_SRC_DIR)/%.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

# =============== make UTILS ========================

$(UTILS_OBJ_DIR)/%.o: $(UTILS_SRC_DIR)/%.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


# ===================== CLEAN UP RULES =====================

.PHONY: clean

clean: clean-server clean-client clean-utils clean-bin
	@echo "Cleanup successful."

clean-server:
	$(RM) $(SERVER_OBJ_FILES)

clean-client:
	$(RM) $(CLIENT_OBJ_FILES)

clean-utils:
	$(RM) $(UTILS_OBJ_FILES)

clean-bin:
	$(RM) ./bin/server ./bin/client

# =========================================================

# GNU Make manual - https://www.gnu.org/software/make/manual/make.html
