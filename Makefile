#qt
qln = $(QT_HOME)/lib
qin = $(QT_HOME)/include
uic = $(QT_HOME)/libexec/uic
qde = $(QT_HOME)/mkspecs/linux-g++

#compiler
CXX = g++
WARS += -Wall
LIBS += -L $(qln)
INCS += -I .. -I $(qde) -I $(qin)
LIBS += -l GL -l Qt6Core -l Qt6Gui -l Qt6Widgets -l Qt6OpenGL -l Qt6OpenGLWidgets
CXXFLAGS += -std=c++20 -fPIC -pipe -fopenmp -MT $@ -MMD -MP -MF $(subst .o,.d, $@) $(DEFS) $(INCS) $(WARS)

#mode
ifneq ($(m), r)
	mode = debug
	CXXFLAGS += -ggdb3
else
	mode = release
	CXXFLAGS += -Ofast
endif

#ouput
out = dist/$(mode)/stability.out

#interfaces
uif := $(sort $(shell find -path './ui/*.ui'))

#sources
src := $(sort $(shell find -path './src/*.cpp'))

#qt files
uig := $(subst ./ui/, build/uic/, $(patsubst %.ui, %.hpp, $(uif)))

#objects
obj := $(sort $(subst ./src/, build/$(mode)/, $(addsuffix .o, $(basename $(src)))))

#dependencies
dep := $(subst .o,.d, $(obj))

#rules
all : $(out)
	@echo 'build($(mode)): complete!'

run : $(out)
	@./$(out)

uic : $(uig)

debug : 
	@gdb $(out) -x gdb.txt

$(out) : $(uig) $(obj)
	@echo 'executable($(mode)): $@'
	@mkdir -p $(dir $@) && rm -rf $@
	@$(CXX) -fopenmp -o $(out) -Wl,-rpath,$(qln) $(obj) ../Math/dist/$(mode)/libmath.so ../Canvas/dist/$(mode)/libcanvas.so $(LIBS)

build/uic/%.hpp : ui/%.ui
	@echo 'uicing($(mode)): $<'
	@mkdir -p $(dir $@) && rm -rf $@
	@$(uic) $< -o $@

build/$(mode)/%.o : src/%.cpp build/$(mode)/%.d
	@echo 'compiling($(mode)): $<'
	@mkdir -p $(dir $@) && rm -rf $@
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(dep) : ;

-include $(dep)

clean :
	@rm -rf dist/$(mode)
	@rm -rf build/$(mode)
	@echo 'clean($(mode)): complete!'

print-% :
	@echo $* = $($*)

.PHONY : all run gui fea clean print-%