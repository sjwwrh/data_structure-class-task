
src_cpp := $(shell find src -name "*.cpp")
obj_o := $(patsubst src/%.cpp,obj/%.o,$(src_cpp))

include_path := include
I_flag := $(include_path:%=-I%)

compile_options := -O3 -g $(I_flag)

obj/%.o : src/%.cpp
	@mkdir -p $(dir $@)
	@g++ -c $^ -o $@ $(compile_options)

workspace/%.exe : obj/%.o
	@mkdir -p $(dir $@)
	@g++ $< -o $@

run1 : workspace/parenthesis_match.exe
	@./$^

run2 : workspace/postfix_notation.exe
	@./$^

run3 : workspace/expression_tree.exe
	@./$^

run_test : workspace/test.exe
	@./$^

debug:
	@printf "%s\n%s\n" $(src_cpp) $(obj_o) 

clean:
	@rm -f obj/*.o
	@rm -f workspace/*.exe

.PHONY : clean debug run_test run1 run2 run3