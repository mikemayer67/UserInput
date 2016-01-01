OBJ = UIParameter.o UIQualifier.o UIValue.o UserInput.o util.o uitest.o

uitest: $(OBJ)
	g++ -g -o $@ $^

depend:
	@makedepend -Y. *.cc 2> /dev/null

clean:
	rm -f *.o uitest

%.o: %.cc
	g++ -c -g -o $@ $<

# DO NOT DELETE

UIParameter.o: UIParameter.h UIQualifier.h types.h UIValue.h util.h
UIQualifier.o: UIQualifier.h types.h util.h
UIValue.o: UIValue.h types.h util.h
UserInput.o: UserInput.h UIParameter.h UIQualifier.h types.h UIValue.h util.h
uitest.o: UserInput.h UIParameter.h UIQualifier.h types.h UIValue.h util.h
util.o: util.h types.h
