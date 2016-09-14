EXENAME1 = testscene
EXENAME2 = testimage
OBJS = image.o png.o rgbapixel.o scene.o testscene.o 

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread

all : $(EXENAME1) $(EXENAME2)

$(EXENAME1) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME1)
$(EXENAME2) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME2)
testscene.o : testscene.cpp scene.h
	$(CXX) $(CXXFLAGS) testscene.cpp
testimage.o : image.h testimage.cpp
	$(CXX) $(CXXFLAGS) testimage.cpp
scene.o :scene.h scene.cpp
	$(CXX) $(CXXFLAGS) scene.cpp
image.o : png.h image.h image.cpp
	$(CXX) $(CXXFLAGS) image.cpp

png.o : png.cpp png.h 
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

clean :
	-rm -f *.o $(EXENAME1) $(EXENAME2) 
