CXX=c++
OUTPUT=app.exe

SFML_DIR=c:/SFML-3.0.0

CXX_FLAGS=-O3 -std=c++20 -Wall -Werror
INCLUDES=-I$(SFML_DIR)/include
LDFLAGS=-L$(SFML_DIR)/lib -s -lsfml-graphics -lsfml-window -lsfml-system

OBJECTS=\
	vector2d.o \
	animation.o \
	component.o \
	entity.o \
	entity_manager.o \
	assets.o \
	action.o \
	game_engine.o \
	scene.o \
	scene_menu.o \
	scene_play.o \
	main.o

all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(info "Link...")
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

%.o: %.cpp %.h
	$(info "Build...")
	$(CXX) -c $(CXX_FLAGS) $(INCLUDES) $< -o $@

main.o: main.cpp
	$(info "Build...")
	$(CXX) -c $(CXX_FLAGS) $(INCLUDES) $< -o $@

run: $(OUTPUT)
	$(OUTPUT)

clean:
	del $(OBJECTS)
	del $(OUTPUT)
