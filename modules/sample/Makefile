COMPILER  = g++
#CFLAGS    = -g -MMD -MP -Wall -Wextra -Winit-self -Wno-missing-field-initializers
CFLAGS    = -std=c++11 -g -O0 -MMD -MP -Wall -Wextra -Winit-self -Wno-missing-field-initializers #-DWITH_WSL
ifeq "$(shell getconf LONG_BIT)" "64"
  LDFLAGS = `pkg-config opencv --cflags --libs` -pthread -ldlib -llapack -lblas
else
  LDFLAGS = `pkg-config opencv --cflags --libs` -pthread -ldlib -llapack -lblas
endif

LIBS      = 
INCLUDE   = -I./include -I../common/include
TARGET    = ./bin/$(shell basename `readlink -f .`)
SRCDIR    = ./src
COMMONSRCDIR = ../common/src

ifeq "$(strip $(SRCDIR))" ""
  SRCDIR  = .
endif
SOURCES   = $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(COMMONSRCDIR)/*.cpp)
$(warning SOURCES = $(SOURCES)) # 変数のコンソール出力
OBJDIR    = ./obj
ifeq "$(strip $(OBJDIR))" ""
  OBJDIR  = .
endif
$(warning OBJDIR = $(OBJDIR)) # 変数のコンソール出力
OBJECTS   = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))
$(warning OBJECTS = $(OBJECTS)) # 変数のコンソール出力
DEPENDS   = $(OBJECTS:.o=.d)
$(warning DEPENDS = $(DEPENDS)) # 変数のコンソール出力

$(TARGET): $(OBJECTS) $(LIBS)
	$(COMPILER) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	-mkdir -p $(OBJDIR)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(OBJDIR)/%.o: $(COMMONSRCDIR)/%.cpp
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: clean $(TARGET)

clean:
	-rm -f $(OBJECTS) $(DEPENDS) $(TARGET)

-include $(DEPENDS)