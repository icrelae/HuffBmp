CXXFLAGS=-Wall -g
OBJS= Main.o HuffmanCoder.o XorCoder.o XorCoderInfoIO.o HuffmanCoderInfoIO.o EncodeStrategy.o DecodeStrategy.o
target="HuffBmp.out"

${target}: ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o ${@}

HuffmanCoder.o: HuffmanCoder.cpp HuffmanCoder.h BinaryTree.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

XorCoder.o: XorCoder.cpp XorCoder.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

XorCoderInfoIO.o: XorCoderInfoIO.cpp XorCoderInfoIO.h XorCoder.h CoderInfoIO.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

HuffmanCoderInfoIO.o: HuffmanCoderInfoIO.cpp HuffmanCoderInfoIO.h HuffmanCoder.h CoderInfoIO.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

EncodeStrategy.o: EncodeStrategy.cpp EncodeStrategy.h CoderInfoIO.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

DecodeStrategy.o: DecodeStrategy.cpp DecodeStrategy.h CoderInfoIO.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

.PHONY: cleanall clean
cleanall: clean
	-rm ${target}
clean:
	-rm *.o
	
