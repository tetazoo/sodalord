
%.c : %.f

%.o : %.f
	$(FC) -c $(ALL_FFLAGS) -o $@ $<

pic/%.o : %.f
	$(FC) -c $(FPICFLAG) $(ALL_FFLAGS) $< -o $@

