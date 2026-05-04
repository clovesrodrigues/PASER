# -------------------------------
# Toolchain
# -------------------------------
CXX ?= g++

# -------------------------------
# Optional wxWidgets (Windows/MinGW)
# -------------------------------
WX_DIR ?= D:/MING64/wxWidgets-3.3.2
WX_INC ?= -I$(WX_DIR)/include -I$(WX_DIR)/lib/gcc_lib/mswu
WX_LIB_DIR ?= -L$(WX_DIR)/lib/gcc_lib
WX_DLL_DIR ?= $(WX_DIR)/lib/gcc_lib
WX_LIBS ?= -lwxmsw33u_core -lwxbase33u \
           -lwxtiff -lwxjpeg -lwxpng -lwxzlib \
           -luxtheme -lmsimg32 -loleacc -lwinspool \
           -lgdiplus -lgdi32 -lshlwapi -lversion -lcomctl32 -lole32 -loleaut32 -luuid \
           -lrpcrt4 -ladvapi32 -lwsock32 -lwinmm -lcomdlg32 -luser32 -lkernel32

# -------------------------------
# Flags
# -------------------------------
BASE_CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -pedantic -finput-charset=UTF-8 -fexec-charset=UTF-8 -Iinclude
WX_CXXFLAGS   := $(BASE_CXXFLAGS) -Iui $(WX_INC)
LDFLAGS       :=

# -------------------------------
# Targets
# -------------------------------
SRC      := $(wildcard src/*.cpp)
OBJ      := $(SRC:.cpp=.o)
BIN      := parser_cli
WX_BIN   := parser_wx

all: $(BIN)

$(BIN): $(OBJ) app/test_cli.o
	$(CXX) $(BASE_CXXFLAGS) $^ -o $@ $(LDFLAGS)

app/test_cli.o: app/test_cli.cpp
	$(CXX) $(BASE_CXXFLAGS) -c $< -o $@

src/%.o: src/%.cpp
	$(CXX) $(BASE_CXXFLAGS) -c $< -o $@

# wx build using wx-config (Linux/macOS)
wx:
	$(CXX) $(WX_CXXFLAGS) $(SRC) ui/parser_teste.cpp app/wx_parser_app.cpp -o $(WX_BIN) `wx-config --cxxflags --libs`

# wx build using manual WX_DIR/WX_LIBS (Windows/MinGW)
wx_manual:
	$(CXX) $(WX_CXXFLAGS) $(SRC) ui/parser_teste.cpp app/wx_parser_app.cpp -o $(WX_BIN).exe $(WX_LIB_DIR) $(WX_LIBS)

# Runs wx executable (Windows cmd style)
run_wx: wx_manual
	@echo Iniciando $(WX_BIN).exe com PATH de DLLs wxWidgets...
	@set PATH=$(WX_DLL_DIR);%PATH% && $(WX_BIN).exe

help:
	@echo "Targets disponíveis:"
	@echo "  make                -> compila parser_cli"
	@echo "  make wx             -> compila UI usando wx-config"
	@echo "  make wx_manual      -> compila UI para MinGW/Windows com WX_DIR"
	@echo "  make run_wx         -> compila e executa parser_wx.exe com PATH ajustado"
	@echo "  make WX_DIR=D:/MING64/wxWidgets-3.3.2 wx_manual -> exemplo Windows"
	@echo "  make clean          -> remove binários/objetos"

clean:
	rm -f $(OBJ) app/test_cli.o $(BIN) $(BIN).exe $(WX_BIN) $(WX_BIN).exe
