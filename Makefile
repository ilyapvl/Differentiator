CC = g++
ASAN = -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,null,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
CFLAGS = -c -std=c++17 -Wall -Weffc++ -Wc++14-compat -Wmissing-declarations -Wcast-align -Wchar-subscripts -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat=2 -Winline -Wnon-virtual-dtor -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-overflow=2 -Wsuggest-override -Wswitch-default -Wundef -Wunreachable-code -Wunused -Wvariadic-macros -Wno-literal-range -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -Wsuggest-override -Wbounds-attributes-redundant -Wlong-long -Wopenmp -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-protector -fPIE -Werror=vla $(ASAN)
LDFLAGS = $(ASAN)
PREF_SOURCES = ./src/
PREF_OBJECTS = ./obj/
SOURCES = $(wildcard $(PREF_SOURCES)*.cpp)
OBJECTS = $(patsubst $(PREF_SOURCES)%.cpp, $(PREF_OBJECTS)%.o, $(SOURCES))
EXECUTABLE = main

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	@$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(PREF_OBJECTS)%.o: $(PREF_SOURCES)%.cpp
	@$(CC) $(CFLAGS) $< -o $@

tex:
	@pdflatex ./data/result.tex  
clean:
	@rm -rf $(wildcard $(PREF_OBJECTS)*.o)
