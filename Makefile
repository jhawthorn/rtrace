
# Change this for every project
TARGET := rtrace

# Change these as needed
CFLAGS := -O3 -ffast-math -Wall -g -ggdb
LIBS := 

# Don't change the following
SRCFILES := $(wildcard src/*.cc)
OBJFILES := $(SRCFILES:%.cc=%.o)
DEPFILES := $(OBJFILES:%.o=%.d)
CLEANFILES := $(CLEANFILES) $(DEPFILES) $(OBJFILES) $(TARGET)

$(TARGET): $(OBJFILES)
	$(CXX) $(CFLAGS) -o $@ $(OBJFILES) $(LIBS)

-include $(DEPFILES)

%.o: %.cc Makefile
	$(CXX) $(CFLAGS) -MMD -MP -MT "$*.d $*.o" -c -o $@ $<

clean:
	$(RM) $(CLEANFILES)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run

