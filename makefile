CXXFLAGS=-Wall
OBJS= Main.o HuffmanCoder.o XorCoder.o
target="HuffBmp.out"

${target}: ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o ${@}

HuffmanCoder.o: HuffmanCoder.cpp HuffmanCoder.h BinaryTree.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

XorCoder.o: XorCoder.cpp XorCoder.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

.PHONY: cleanall clean
cleanall: clean
	-rm ${target}
clean:
	-rm *.o
	
