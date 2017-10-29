CXXFLAGS += -Wall -O2
LDDFLAGS += -lpthread
OBJSDIR = /tmp/HuffBmp
OBJS = ${patsubst %.cpp, ${OBJSDIR}/%.o, ${wildcard *.cpp}}
target = ${OBJSDIR}/HuffBmp.out

${target}: ${OBJS}
	${CXX} ${CXXFLAGS} ${LDDFLAGS} ${OBJS} -o ${@}

${OBJSDIR}/Main.o: ${OBJSDIR}/%.o:%.cpp
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

${OBJSDIR}/HuffmanCoder.o: ${OBJSDIR}/%.o:%.cpp %.h BinaryTree.h Coder.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

${OBJSDIR}/HuffmanCoderInfoIO.o: ${OBJSDIR}/%.o:%.cpp %.h CoderInfoIO.h HuffmanCoder.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

${OBJSDIR}/XorCoder.o: ${OBJSDIR}/%.o:%.cpp %.h Coder.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

${OBJSDIR}/XorCoderInfoIO.o: ${OBJSDIR}/%.o:%.cpp %.h CoderInfoIO.h XorCoder.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

${OBJSDIR}/BmpCommon.o: ${OBJSDIR}/%.o:%.cpp %.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

${OBJSDIR}/EncodeStrategy.o: ${OBJSDIR}/%.o:%.cpp %.h CoderInfoIO.h Coder.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

${OBJSDIR}/DecodeStrategy.o: ${OBJSDIR}/%.o:%.cpp %.h CoderInfoIO.h Coder.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

${OBJSDIR}/BmpFactory.o: ${OBJSDIR}/%.o:%.cpp %.h FileFactory.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

${OBJSDIR}/Mandelbrot.o: ${OBJSDIR}/%.o:%.cpp %.h
	${CXX} ${CXXFLAGS} -c ${<} -o ${@}

.PHONY: cleanall clean dir
cleanall: clean
	-${RM} ${target}
clean:
	-${RM} ${OBJSDIR}/*.o
dir:
	mkdir -p ${OBJSDIR}
