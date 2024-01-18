# Avoid -D_GLIBCXX_DEBUG for libraries; it changes the sizes of STL
# containers.  If main is built without it, trouble ensues.
# Code has to all use this feature, or none.

# Use of -Wall is mandatory EVERY time g++ executes.  You can’t just
# throw it into your Makefile.  It has to actually get USED each time.

# Put opts into the environment so that the echoed compile line just
# says “g++ $opts …” and it doesn’t list all the tedious options.
# However, -Wall DOES appear, so that we know it’s being used.

export opts=-D_FORTIFY_SOURCE=2 -fno-diagnostics-show-option		\
-fstack-protector-all -g -O3 -Walloc-zero -Walloca	\
-Wctor-dtor-privacy -Wduplicated-cond -Wduplicated-branches		\
-Werror -Wextra -Wfatal-errors -Winit-self -Wlogical-op			\
-Wold-style-cast -Wpedantic -Wshadow -Wunused-const-variable=1	\
-Wzero-as-null-pointer-constant
CXXFLAGS=-Wall $$opts

assignment=HW1

$(assignment): 
	g++ $(CXXFLAGS) -o $(assignment) mad_libs.cpp

tar:
	tar -cf $(assignment).tar *.cpp Makefile

checkin: tar
	~ct301/bin/checkin $(assignment) $(assignment).tar

clean:
	rm -f $(assignment) $(assignment).tar *.o *.gch *.gcov a.out
