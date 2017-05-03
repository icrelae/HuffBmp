CXXFLAGS=
OBJ= BinaryTree.o HuffmanCoder.o
target="HuffBmp.out"

${target}: ${OBJ}
	${CXX} ${CXXFLAGS} ${OBJ} -o ${@}

BinaryTree.o: BinaryTree.cpp BinaryTree.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

HuffmanCoder.o: HuffmanCoder.cpp HuffmanCoder.h BinaryTree.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

.PHONY: cleanall cleanobj
cleanall: cleanobj
	-rm ${target}
cleanobj:
	-rm *.o
	
