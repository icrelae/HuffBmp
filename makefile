CXXFLAGS=-Wall -g
OBJS= Main.o EncodeStrategy.o DecodeStrategy.o XorCoder.o XorCoderInfoIO.o \
	  HuffmanCoder.o HuffmanCoderInfoIO.o BmpCommon.o BmpCoder.o BmpCoderInfoIO.o
target="HuffBmp.out"

${target}: ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o ${@}

HuffmanCoder.o: HuffmanCoder.cpp HuffmanCoder.h BinaryTree.h Coder.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

HuffmanCoderInfoIO.o: HuffmanCoderInfoIO.cpp HuffmanCoderInfoIO.h CoderInfoIO.h HuffmanCoder.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

XorCoder.o: XorCoder.cpp XorCoder.h Coder.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

XorCoderInfoIO.o: XorCoderInfoIO.cpp XorCoderInfoIO.h CoderInfoIO.h XorCoder.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

BmpCommon.o: BmpCommon.cpp BmpCommon.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

BmpCoder.o: BmpCoder.cpp BmpCoder.h Coder.h BmpCommon.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

BmpCoderInfoIO.o: BmpCoderInfoIO.cpp BmpCoderInfoIO.h CoderInfoIO.h BmpCoder.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

EncodeStrategy.o: EncodeStrategy.cpp EncodeStrategy.h CoderInfoIO.h Coder.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

DecodeStrategy.o: DecodeStrategy.cpp DecodeStrategy.h CoderInfoIO.h Coder.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

.PHONY: cleanall clean
cleanall: clean
	-rm ${target}
clean:
	-rm *.o
